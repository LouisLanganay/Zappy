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

"""
[ ][  ][  ][0 ][  ][  ][  ]
[ ][  ][1 ][2 ][3 ][  ][  ] # level 1
[ ][4 ][5 ][6 ][7 ][8 ][  ] # level 2
[9][10][11][12][13][14][15] # level 3

"""

class AI:
    def __init__(self):
        self.level = 1
        self.inventory = inventory
        self.vision = []
        self.direction = 0
        self.team = ''
        self.x = 0
        self.y = 0

    def make_decision(self):
        actions = ['Forward', 'Right', 'Left', 'Inventory', 'Look']
        action = random.choice(actions)
        return f'{action}\n'

    def update_state(self, response):
        if response.startswith('message'):
            print("Received a broadcast message")
        elif response.startswith('Inventory'):
            items = response.split(', ')
            for item in items:
                key, value = item.split()
                self.inventory[key] = int(value)
        elif response.startswith('Look'):
            print("Received vision")
            self.vision = self.parse_vision(response)
            self.print_vision()
        elif response.startswith('elevation'):
            self.level += 1
            print(f"Leveled up! New level: {self.level}")

    def parse_vision(self, input_message):
        input_message = input_message.strip('[]')
        list_of_tiles = input_message.split(', ')
        vision = [self.convert_list_to_tile(tile.split(' ')) for tile in list_of_tiles]
        return vision

    def convert_list_to_tile(self, tile_list):
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

    def print_vision(self):
        print("Vision:")
        for idx, tile in enumerate(self.vision):
            print(f"Tile {idx}: {tile}")

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

        self.ai = AI()

    def send(self, data):
        self.socket.send(data.encode())

    def receive(self, sock):
        data = sock.recv(1024).decode().strip()
        if not data:
            print("Server closed the connection")
            sys.exit(0)
        self.ai.update_state(data)
        return data

    def close(self):
        self.selector.unregister(self.socket)
        self.socket.close()

    def connect(self):
        self.send(self.name + '\n')

    def detect_type_of_response(self, response):
        if response.startswith('ok'):
            return 'ok'
        elif response.startswith('ko'):
            return 'ko'
        elif response.startswith('['):
            if len(response.strip('[]').split(', ')) == 7:
                return 'inventory'
            else:
                return 'look'
            
    def parse_inventory(self, response):
        inventory = {}
        response = response.strip('[]')
        list_of_items = response.split(', ')
        for item in list_of_items:
            key, value = item.split()
            inventory[key] = int(value)
        return inventory
    
    def parse_vision(self, response):
        response = response.strip('[]')
        list_of_tiles = response.split(', ')
        vision = [self.convert_list_to_tile(tile.split(' ')) for tile in list_of_tiles]
        return vision

    def run(self):
        self.connect()
        self.receive(self.socket)  # Read "WELCOME"
        self.receive(self.socket)  # Read initial server response
        while True:
            events = self.selector.select(timeout=1)
            for key, _ in events:
                callback = key.data
                data = callback(key.fileobj)
            
            # Send Look command and parse the vision
            self.send('Look\n')
            data = self.receive(self.socket)
            self.ai.update_state(data)
            
            # Make a decision and send the action
            decision = self.ai.make_decision()
            self.send(decision)
            response = self.receive(self.socket)
            # print(response)
            type_of_response = self.detect_type_of_response(response)
            if type_of_response == 'inventory':
                self.ai.inventory = self.parse_inventory(response)                
            if type_of_response == 'look':
                self.ai.vision = self.ai.parse_vision(response)

            # elif type_of_response == 'look':
            #     print(response)
            #     print("Received vision")

            # if resonse is an look, parse it

            
            time.sleep(1)  # Delay to avoid flooding the server with commands

if __name__ == '__main__':
    args = ParseArgs()
    host, port, name = args.parse(sys.argv[1:])

    client = Client(host, port, name)
    client.run()
    client.close()
    sys.exit(0)
