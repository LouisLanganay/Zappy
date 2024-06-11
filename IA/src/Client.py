#!/usr/bin/env python3
import socket
import sys
import selectors
import random
import time

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
    def __init__(self, client):
        self.client = client
        self.level = 1
        self.inventory = inventory
        self.vision = []
        self.direction = 0
        self.team = ''
        self.x = 0
        self.y = 0

    def detect_type_of_response(self, response):
        if response.startswith('ok'):
            return 'ok'
        if response.startswith('ko'):
            return 'ko'
        if response.startswith('['):
            if len(response.strip('[]').split(', ')) == 7:
                return 'inventory'
            else:
                return 'look'
        return 'unknown'

    def take_resources(self, resource):
        for i, row in enumerate(self.vision):
            for j, cell in enumerate(row):
                if resource in cell:
                    self.move_to(i, j)
                    self.client.send(f'Take {resource}\n')
                    return True
        return False

    def move_to(self, target_x, target_y):
        current_x, current_y = 0, 0
        while (current_x, current_y) != (target_x, target_y):
            if target_x > current_x:
                self.client.send('Forward\n')
                current_x += 1
            elif target_x < current_x:
                self.client.send('Left\n')
                self.client.send('Forward\n')
                self.client.send('Right\n')
                current_x -= 1
            elif target_y > current_y:
                self.client.send('Right\n')
                self.client.send('Forward\n')
                self.client.send('Left\n')
                current_y += 1
            elif target_y < current_y:
                self.client.send('Left\n')
                self.client.send('Forward\n')
                self.client.send('Right\n')
                current_y -= 1

    def make_decision(self):
        # Prioritize collecting resources
        if self.inventory["food"] < 5:
            if self.take_resources("food"):
                return f'Take food\n'
        if self.level == 1:
            if self.inventory["linemate"] < 1:
                if self.take_resources("linemate"):
                    return f'Take linemate\n'
        
        # Default action if no resources need to be collected
        actions = ['Forward', 'Left', 'Right']
        action = random.choice(actions)
        return f'{action}\n'

    def update_state(self, response):
        type_of_response = self.detect_type_of_response(response)
        if type_of_response == 'inventory':
            self.inventory = self.parse_inventory(response)
        if type_of_response == 'look':
            self.vision = self.parse_vision(response)

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

    def parse_vision(self, input_message):
        vision = self._parse_input_list(input_message.strip('[]'))
        list_of_dicts = self._create_list_of_dicts(vision)
        self._fill_empty_elements(list_of_dicts)
        padded_list = self._pad_rows(list_of_dicts)
        final_list = self._convert_elements_to_dicts(padded_list)
        return final_list

    def print_vision(self):
        print("Vision:")
        for row in self.vision:
            print(row)

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

    def _convert_elements_to_dicts(self, padded_list):
        for i in range(len(padded_list)):
            for j in range(len(padded_list[i])):
                padded_list[i][j] = self._list_to_dict(padded_list[i][j])
        return padded_list

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
            else:
                self.print_invalid_argument()
                sys.exit(84)

        self.check_type()
        return self.host, self.port, self.name

    def print_usage(self):
        print("USAGE: ./zappy_ai -p port -n name -h machine")
        sys.exit(84)

    def print_invalid_argument(self):
        print("Invalid argument")
        sys.exit(84)

class Client:
    def __init__(self, host, port, name):
        self.host = host
        self.port = int(port)
        self.name = name
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((self.host, self.port))

        self.selector = selectors.DefaultSelector()
        self.selector.register(self.socket, selectors.EVENT_READ, self.receive)

        self.ai = AI(self)
        self.command_queue = []
        self.max_queue_size = 10

    def send(self, data):
        if len(self.command_queue) < self.max_queue_size:
            self.socket.send(data.encode())
            self.command_queue.append(data)
            return True
        else:
            return False

    def receive(self, sock):
        data = sock.recv(1024).decode().strip()
        if not data:
            print("Server closed the connection")
            sys.exit(0)
        self.ai.update_state(data)
        if self.command_queue and (data == 'ok' or data == 'ko'):
            self.command_queue.pop(0)
        return data

    def close(self):
        self.selector.unregister(self.socket)
        self.socket.close()

    def connect(self):
        self.send(self.name + '\n')
    
    def run(self):
        self.connect()
        self.receive(self.socket)
        self.receive(self.socket)
        
        while True:
            self.send('Look\n')
            data = self.receive(self.socket)
            self.ai.update_state(data)

            decision = self.ai.make_decision()
            self.send(decision)

            max_retries = 5
            retries = 0
            while not self.send('Forward\n'):
                retries += 1
                if retries >= max_retries:
                    time.sleep(2)
                    self.command_queue = []
                time.sleep(0.1)

def main():
    args = sys.argv[1:]
    parser = ParseArgs()
    host, port, name = parser.parse(args)
    client = Client(host, port, name)
    client.run()

if __name__ == "__main__":
    main()
