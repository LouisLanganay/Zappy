#!/usr/bin/env python3
import socket
import sys
import selectors
import random
import time
from ParseArgs import ParseArgs

levels = [
    {"linemate": 1, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0},
    {"linemate": 1, "deraumere": 1, "sibur": 1, "mendiane": 0, "phiras": 0, "thystame": 0},
    {"linemate": 2, "deraumere": 0, "sibur": 1, "mendiane": 0, "phiras": 2, "thystame": 0},
    {"linemate": 1, "deraumere": 1, "sibur": 2, "mendiane": 0, "phiras": 1, "thystame": 0},
    {"linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3, "phiras": 0, "thystame": 0},
    {"linemate": 1, "deraumere": 2, "sibur": 3, "mendiane": 0, "phiras": 1, "thystame": 0},
    {"linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1}
]

resources_to_get = {"linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}

for level in levels:
    for resource, amount in level.items():
        resources_to_get[resource] += amount

inventory = {
    "food": 0,
    "linemate": 0,
    "deraumere": 0,
    "sibur": 0,
    "mendiane": 0,
    "phiras": 0,
    "thystame": 0
}

class AI:
    def __init__(self):
        self.level = 1
        self.inventory = inventory
        self.vision = []
        self.direction = 'Down'
        self.team = ''
        self.x = 0
        self.y = 0
        self.queue = []

    def parse_inventory(self, response):
        inventory = {}
        response = response.strip('[]')
        list_of_items = response.split(', ')
        for item in list_of_items:
            parts = item.split()
            if len(parts) == 2:
                key, value = parts
                inventory[key] = int(value)
            else:
                print(f"Unexpected inventory item format: {item}")
        return inventory
    
    def _parse_input_list(self, row_list):
        removed_brackets = row_list.replace('[', '').replace(']', '')
        converted_list = []
        list_of_tiles = removed_brackets.split(',')
        for elt in list_of_tiles:
            converted_list.append(elt.split())
        return converted_list
    
    def _create_list_of_dicts(self, vision):
        list_of_dicts = []
        i = 0
        while len(vision) > 0:
            width = 1 + 2 * i
            list_of_dicts.append(vision[:width])
            vision = vision[width:]
            i += 1
        return list_of_dicts
    
    def _fill_empty_elements(self, list_of_dicts):
        for row in list_of_dicts:
            for i, cell in enumerate(row):
                if cell == []:
                    row[i] = [None]

    def _pad_rows(self, list_of_dicts):
        len_last_row = len(list_of_dicts[-1])
        new_list = []
        for row in list_of_dicts:
            nb_spaces = (len_last_row - len(row)) // 2
            new_row = [[None]] * nb_spaces + row + [[None]] * nb_spaces
            new_list.append(new_row)
        return new_list
    
    def _list_to_dict(self, tile_list):
        tile = {
            "player": 0,
            "food": 0,
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0,
            "egg": 0
        }
        for elt in tile_list:
            if elt in tile:
                tile[elt] += 1
        return tile

    def find_food(self):
        if self.take_resources('food'):
            return
        else:
            self.client.send('Forward\n')

class ParseArgs:
    def __init__(self):
        self.host = 'localhost'
        self.port = -1
        self.name = ''

    def check_type(self):
        try:
            self.port = int(self.port)
        except ValueError:
            self.print_invalid_argument()
            sys.exit(84)

        if self.port == -1 or self.name == '':
            self.print_usage()
            sys.exit(84)

        self.check_host()
        self.check_port()
        self.check_name()

    def check_host(self):
        try:
            socket.gethostbyname(self.host)
        except socket.gaierror:
            print("Error: Invalid host")
            sys.exit(84)

    def check_port(self):
        if self.port < 0 or self.port > 65535:
            print("Error: Port out of range")
            sys.exit(84)

    def check_name(self):
        if len(self.name) > 32:
            print("Error: Name too long")
            sys.exit(84)

    def parse(self, args):
        for i in range(0, len(args), 2):
            if args[i] == '-p':
                self.port = args[i + 1]
            elif args[i] == '-n':
                self.name = args[i + 1]
            elif args[i] == '-h':
                self.host = args[i + 1]
    
    def _convert_elements_to_dicts(self, padded_list):
        for i in range(len(padded_list)):
            for j in range(len(padded_list[i])):
                padded_list[i][j] = self._list_to_dict(padded_list[i][j])
        return padded_list
    
    def parse_vision(self, input_message):
        vision = self._parse_input_list(input_message.strip('[]'))
        list_of_dicts = self._create_list_of_dicts(vision)
        self._fill_empty_elements(list_of_dicts)
        padded_list = self._pad_rows(list_of_dicts)
        final_list = self._convert_elements_to_dicts(padded_list)
        return final_list
    
    def detect_type_of_response(self, response):
        if response.startswith('ok'):
            return 'ok'
        if response.startswith('ko'):
            return 'ko'
        if response.startswith('['):
            if len(response.strip('[]').split(', ')) == 7: # there is 7 key in an inventory
                return 'inventory'
            else:
                return 'look'
        return 'unknown'
    
    def update_state(self, response):
        type_of_response = self.detect_type_of_response(response)
        if type_of_response == 'inventory':
            self.inventory = self.parse_inventory(response)
        if type_of_response == 'look':
            self.vision = self.parse_vision(response)
    
    def set_direction(self, goal_direction):
        if self.direction == goal_direction:
            return
        
        idx_directions = ['Left', 'Up', 'Right', 'Down']
        idx_goal = idx_directions.index(goal_direction)
        idx_current = idx_directions.index(self.direction)
        diff = idx_goal - idx_current
        if diff == 1 or diff == -3:
            self.queue.append('Left')
        elif diff == 2 or diff == -2:
            self.queue.append('Right')
            self.queue.append('Right')
        elif diff == 3 or diff == -1:
            self.queue.append('Right')
        self.direction = goal_direction

    def move_direction(self, goal_direction):
        self.set_direction(goal_direction)
        self.queue.append('Forward')

    def move_to(self, goal_x, goal_y):
        
        vertical_direction = 'Down' if goal_y > self.y else 'Up'
        horizontal_direction = 'Right' if goal_x > self.x else 'Left'

        while self.y != goal_y:
            self.move_direction(vertical_direction)
            if vertical_direction == 'Down':
                self.y += 1
            else:
                self.y -= 1

        while self.x != goal_x:
            self.move_direction(horizontal_direction)
            if horizontal_direction == 'Right':
                self.x += 1
            else:
                self.x -= 1

    def take_resources(self, resource):
        state = False
        for i, row in enumerate(self.vision):
            for j, cell in enumerate(row):
                try:
                    if cell[resource] > 0:
                        self.move_to(j, i)
                        for _ in range(cell[resource]):
                            self.queue.append(f'Take {resource}')
                        state = True
                except:
                    print(f"{resource} doesn't exist")
        return state
    
    def has_all_resources(self):
        for resource, amount_needed in resources_to_get.items():
            if self.inventory[resource] < amount_needed:
                return False
        return True

    def take_resources_to_get(self):
        state = False

        if self.has_all_resources():
            return True
        for resource, amount_needed in resources_to_get.items():
            if self.inventory[resource] < amount_needed:
                amount_to_collect = amount_needed - self.inventory[resource]
                for i, row in enumerate(self.vision):
                    for j, cell in enumerate(row):
                        if cell[resource] > 0:
                            self.move_to(j, i)
                            for _ in range(min(amount_to_collect, cell[resource])):
                                self.queue.append(f'Take {resource}')
                                amount_to_collect -= 1
                            if amount_to_collect == 0:
                                state = True
                                break
                    if amount_to_collect == 0:
                        break
        
        return state

    def reset_direction(self):
        self.direction = 'Down'

    def algorithm(self):
        # Set initial position and direction of the player in the vision grid
        self.y = 0
        self.x = len(self.vision[0]) // 2
        self.reset_direction()

        # Prioritize taking food first
        if not self.take_resources('food'):
            self.queue.append('Forward')
            self.queue.append('Forward')
            self.queue.append('Forward')

        if self.inventory['food'] > 20:
            if not self.take_resources_to_get():
                self.queue.append('Forward')
                self.queue.append('Forward')
                self.queue.append('Forward')

        return self.queue


class Client:
    def __init__(self, host, port, name):
        self.host = host
        self.port = int(port)
        self.name = name
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((self.host, self.port))
        self.size_map = (0,0)
        self.selector = selectors.DefaultSelector()
        self.selector.register(self.socket, selectors.EVENT_READ, self.receive)


        self.ai = AI(self)
        self.command_queue = []
        self.has_all_resources = False


    def connect_and_get_slots(self):
        if (self.receive(self.socket) == "WELCOME"):
            print("WELCOME")
            self.send(self.name + '\n')
            available_slots_msg = self.receive(self.socket)
            print(available_slots_msg)
            available_slots = int(available_slots_msg.split('\n')[0].strip())
            chaine = available_slots_msg.splitlines()
            list_nbr = chaine[1].split()
            self.size_map = tuple(int(nombre) for nombre in list_nbr)
            return available_slots + 1
        return 0

    def send(self, data):
        self.socket.send(data.encode() + b'\n')

    def receive(self, sock):
        data = sock.recv(1024).decode().strip()
        if not data:
            print("Server closed the connection")
            sys.exit(0)
        return data

    def send_queue(self):
        for elt in self.queue:
            self.send(elt)
            data = self.receive(self.socket)
        self.queue.clear()

    def update_vision(self):
        self.send('Look')
        data = self.receive(self.socket)
        self.ai.update_state(data)
    
    def update_inventory(self):
        self.send('Inventory')
        data = self.receive(self.socket)
        self.ai.update_state(data)

    def close(self):
        self.selector.unregister(self.socket)
        self.socket.close()

    def connect(self):
        self.send(self.name + '\n')

    def check_broadcast(self, msg_serv):
        msg_serv_parse = msg_serv.split()
        if (msg_serv_parse[0] == "message"):
            return "ok"
        return msg_serv

    def handle_broadcast(self):
        pass


    def handleCommand():
        pass


    def run(self):
        self.connect()
        msg_serv = self.receive(self.socket)
        if (self.check_broadcast(msg_serv) == "ok"):
            self.handle_broadcast()
        while True:
            self.update_vision()
            self.update_inventory()
            if self.has_all_resources == False and self.ai.has_all_resources() == True:
                self.has_all_resources = True
                print("Got every resources!")
                # self.send("Broadcast Group")
                # data = self.receive(self.socket)
                # if data == "ok":
                #     print("Broadcasted Group")
                time.sleep(0.5)
                continue
            self.queue = self.ai.algorithm()
            self.send_queue()


def main():
    args = sys.argv[1:]
    parser = ParseArgs()
    host, port, name = parser.parse(args)
    client = Client(host, port, name)
    available_slots = client.connect_and_get_slots()
    if (available_slots == 0):
        return "ko"
    client.run()

if __name__ == "__main__":
    main()