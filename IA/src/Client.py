#!/usr/bin/env python3
import socket
import sys
import selectors
import random
import time
from ParseArgs import ParseArgs
import subprocess

levels = [
    {"linemate": 1, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0},
    {"linemate": 1, "deraumere": 1, "sibur": 1, "mendiane": 0, "phiras": 0, "thystame": 0},
    {"linemate": 2, "deraumere": 0, "sibur": 1, "mendiane": 0, "phiras": 2, "thystame": 0},
    {"linemate": 1, "deraumere": 1, "sibur": 2, "mendiane": 0, "phiras": 1, "thystame": 0},
    {"linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3, "phiras": 0, "thystame": 0},
    {"linemate": 1, "deraumere": 2, "sibur": 3, "mendiane": 0, "phiras": 1, "thystame": 0},
    {"linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1}
]

"""
Rarity (based on resources needed to get)
    Linemate: 0.0333
    Deraumere: 0.01875
    Sibur: 0.01
    Mendiane: 0.02​
    Phiras: 0.0133
    Thystame: 0.05​
"""

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
        self.start = time.time()
        self.mode = 'Normal'
        self.broadcaster_direction = -1 # default value (no broadcaster)
        self.count_incanter = 0

    def parse_inventory(self, response):
        if self.detect_type_of_response(response) != 'inventory':
            return None
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
    
    def get_type_inventory_look(self, response):
        try:
            inventory_string = response.strip("[] ")
            items = inventory_string.split(", ")
            inventory_dict = {}

            for item in items:
                key, value = item.split(" ")
                inventory_dict[key] = int(value)

            return 'inventory'
        except:
            return 'look'
        
    
    def detect_type_of_response(self, response):
        if response.startswith('ok'):
            return 'ok'
        if response.startswith('ko'):
            return 'ko'
        if response.startswith('['):
            return self.get_type_inventory_look(response)
        if response.startswith('message'):
            return 'broadcast'
        if response.startswith('dead'):
            return 'dead'
        if response.startswith('Elevation underway'):
            return 'elevation'
        if response.startswith('Current level:'):
            return 'level up'
        
        return 'unknown'
    
    def update_state(self, response):
        type_of_response = self.detect_type_of_response(response)
        if type_of_response == 'inventory':
            self.inventory = self.parse_inventory(response)
        if type_of_response == 'look':
            self.vision = self.parse_vision(response)
        if type_of_response == 'level up':
            self.level = int(response.split()[-1])
            print(f"Level up! New level: {self.level}")
        if type_of_response == 'broadcast':
            print(response)
    
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
            if resource == 'food':
                continue
            if self.inventory[resource] < amount_needed:
                return False
        return True

    def take_resources_to_get(self):
        state = False

        if self.has_all_resources():
            self.take_resources('food')
            return True
        
        resources_to_get['food'] = 1000
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

    def linemate_level1(self):
        state = False
        for i, row in enumerate(self.vision):
            for j, cell in enumerate(row):
                try:
                    if cell['linemate'] > 0:
                        self.move_to(j, i)
                        self.queue.append('Incantation')
                        state = True
                        return state
                except:
                    print(f"linemate doesn't exist")
        return state

    def drop_resources(self):
        for resource, amount in self.inventory.items():
            if resource == 'food':
                continue
            for _ in range(amount):
                self.queue.append(f'Set {resource}')
        self.inventory = inventory
        return self.queue

    def algorithm(self):
        # Set initial position and direction of the player in the vision grid
        self.y = 0
        self.x = len(self.vision[0]) // 2
        self.reset_direction()

        # Prioritize taking food first
        if self.inventory['food'] < 50:
            if not self.take_resources('food'):
                self.queue.append(random.choice(['Left', 'Right', 'Forward']))
                self.queue.append('Forward')
                self.queue.append('Forward')
            return self.queue
        
        if self.level == 1:
            if not self.linemate_level1():
                self.take_resources('food')
            return self.queue
        
        if not self.take_resources_to_get():
            self.queue.append(random.choice(['Left', 'Right', 'Forward']))
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
        self.queue = []

        self.selector = selectors.DefaultSelector()
        self.selector.register(self.socket, selectors.EVENT_READ, self.receive)

        self.ai = AI()
        self.command_queue = []
        self.has_all_resources = False

    def send(self, data):
        try:
            self.socket.send(data.encode() + b'\n')
        except Exception as e:
            print(f"An unexpected error occurred: {e}")
            return 84
        return 0

    def receive(self):
        buffer = ""
        while True:
            data = self.socket.recv(4096).decode().strip()
            if not data:
                print("Server closed the connection")
                sys.exit(84)
            buffer += data
            while '\n' in buffer:
                message, buffer = buffer.split('\n', 1)
                if message.startswith('message'):
                    self.handle_broadcast(message)
                else:
                    self.ai.update_state(message)
            if '\n' not in buffer:
                break

        count = 0
        while buffer.startswith('message'): #FIXME add this additionnal condition if needed and count < 3:
            self.handle_broadcast(buffer)
            buffer = self.socket.recv(2048).decode().strip()
            count += 1

        return buffer

    def update_inventory(self):
        if (self.send('Inventory') == 84):
            return 84
        data = self.receive()
        self.ai.update_state(data)

    def update_vision(self):
        if (self.send('Look') == 84):
            return 84
        data = self.receive()
        self.ai.update_state(data)

    def send_queue(self):
        for elt in self.queue:
            if (self.send(elt) == 84):
                return 84
            data = self.receive()
            if data.startswith('dead'):
                print("Dead")
                sys.exit(0)
            self.ai.update_state(data)
        self.queue.clear()

    def send_broadcast(self, message):
        if (self.send(f"Broadcast {message}") == 84):
            return 84
        data = self.receive()

    def receive_no_data_check(self):
        data = self.socket.recv(1024).decode().strip()
        return data

    def handle_broadcast(self, message):
        temp = message[8:]
        temp = temp.split(', ')

        direction = int(temp[0])
        data = temp[1]

        if data == 'Incantation':
            self.ai.count_incanter += 1
            if self.ai.count_incanter == 6:
                self.ai.mode = 'Incantation'
                self.run()

        if data == 'Group' and self.ai.mode == 'Broadcaster':
            self.ai.mode = 'Normal'
            self.ai.broadcaster_direction = direction

        if data == 'Group' and self.ai.mode == 'Normal':
            self.ai.mode = 'Group'
            self.ai.count_incanter = 1

        if data == 'Group' and self.ai.mode == 'Group':
            self.ai.broadcaster_direction = direction

        if self.ai.broadcaster_direction == 0 and self.ai.mode == 'Group':
            self.ai.broadcaster_direction = -1
            print("Group is over")

            # self.send_broadcast('Ready')
            self.ai.mode = 'Incantation'
            self.ai.count_incanter += 1
            self.send_broadcast('Incantation')
            return

        if self.ai.mode == 'Group':
            if self.ai.broadcaster_direction == 1 or self.ai.broadcaster_direction == 2 or self.ai.broadcaster_direction == 8:
                if (self.send('Forward') == 84):
                    return 84

            if self.ai.broadcaster_direction == 3 or self.ai.broadcaster_direction == 4 or self.ai.broadcaster_direction == 5:
                if (self.send('Left') == 84):
                    return 84

            if self.ai.broadcaster_direction == 6 or self.ai.broadcaster_direction == 7:
                if (self.send('Right') == 84):
                    return 84

            data = self.receive()

            while True:
                print(self.ai.mode)
                data = self.receive()
                print(data)
                if data.startswith('dead'):
                    print("Dead")
                    sys.exit(0)
                if data.startswith('message'):
                    self.handle_broadcast(data)
                    break


    def close(self):
        self.selector.unregister(self.socket)
        self.socket.close()

    def connect(self):
        data = self.receive()  # Initial connection response (welcome message)
        if (data != "WELCOME"):
            return 84
        print(data)
        if (self.send(self.name) == 84):
            return 84
        data = self.receive()  # Additional server response (map size)
        if (data == None):
            return 84
        print(data)
        return 0

    def run(self):
        # self.send('Fork')
        # data = self.receive()
        while True:
            if self.ai.count_incanter == 6 and (self.ai.mode == 'Incantation' or self.ai.mode == 'Broadcaster'): 
                self.queue = self.ai.drop_resources()
                self.ai.mode = 'Incantation'
                self.send('Look')
                data = self.receive()
                vision = self.ai._parse_input_list(data.strip('[]'))
                if vision[0].count('player') == 6:
                    self.queue = ['Incantation']
                    self.send_queue()
                continue

            if self.ai.mode == 'Normal':
                self.queue = ['Look', 'Inventory']
                self.send_queue()

            if self.ai.mode == 'Broadcaster':
                self.queue = self.ai.drop_resources()
                self.send_queue()
                self.send_broadcast('Group')
                time.sleep(0.5)
                continue

            if self.ai.has_all_resources() and self.ai.mode == 'Normal' and self.ai.inventory['food'] > 100:
                self.ai.mode = 'Broadcaster'
                self.ai.count_incanter += 1
                self.ai.drop_resources()
                self.send_queue()
                continue

            if self.ai.mode == 'Normal':
                self.queue = self.ai.algorithm()
                self.send_queue()

def main():
    args = sys.argv[1:]
    parser = ParseArgs()
    host, port, name = parser.parse(args)
    client = Client(host, port, name)
    if (client.connect() == 84):
        return 84
    client.run()
    client.close()

if __name__ == "__main__":
    if (main() == 84):
        sys.exit(84)

