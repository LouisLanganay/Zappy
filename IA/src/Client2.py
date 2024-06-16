#!/usr/bin/env python3
import socket
import sys
import selectors
import random
import time
from ParseArgs import ParseArgs

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
    
    def move_left(self):
        if self.direction == 'Up':
            self.direction = 'Left'
            self.queue.append('Right')
            self.queue.append('Forward')
        elif self.direction == 'Down':
            self.direction = 'Left'
            self.queue.append('Left')
            self.queue.append('Forward')
        elif self.direction == 'Left':
            self.direction = 'Left'
            self.queue.append('Forward')
        elif self.direction == 'Right':
            self.direction = 'Left'
            self.queue.append('Left')
            self.queue.append('Left')
            self.queue.append('Forward')

    # def move_right(self):


    # def move_right(self):


    
    # def move_left(self):
    #     self.queue.append('Left')
    #     self.queue.append('Forward')

    # def move_right(self):
    #     self.queue.append('Right')
    #     self.queue.append('Forward')

    # def move_up(self):
    #     self.queue.append('Forward')

    # def move_down(self):
    #     self.queue.append('Right')
    #     self.queue.append('Right')
    #     self.queue.append('Forward')

    # def move_to(self, target_x, target_y):
    #     while x < target_x:
    #         self.
    # def turn_left(self):
    #     directions = ['Up', 'Left', 'Down', 'Right']
    #     self.direction = directions[(directions.index(self.direction) + 1) % 4]
    #     self.queue.append('Left')

    # def turn_right(self):
    #     directions = ['Up', 'Right', 'Down', 'Left']
    #     self.direction = directions[(directions.index(self.direction) + 1) % 4]
    #     self.queue.append('Right')

    # def move_forward(self):
    #     self.queue.append('Forward')
    #     if self.direction == 'Up':
    #         self.y -= 1
    #     elif self.direction == 'Down':
    #         self.y += 1
    #     elif self.direction == 'Left':
    #         self.x -= 1
    #     elif self.direction == 'Right':
    #         self.x += 1

    # def move_to(self, target_x, target_y):
    #     print(f"Player position: ({self.x}, {self.y})")
    #     print(f"Player direction: {self.direction}")
    #     print(f"Player target position: ({target_x}, {target_y})")

    #     while self.x != target_x or self.y != target_y:
    #         if self.y < target_y:
    #             if self.direction != 'Down':
    #                 self.turn_right()
    #                 if self.direction != 'Down':
    #                     self.turn_right()
    #             self.move_forward()
    #         elif self.y > target_y:
    #             if self.direction != 'Up':
    #                 self.turn_right()
    #                 if self.direction != 'Up':
    #                     self.turn_right()
    #             self.move_forward()
    #         elif self.x < target_x:
    #             if self.direction != 'Right':
    #                 self.turn_right()
    #                 if self.direction != 'Right':
    #                     self.turn_right()
    #             self.move_forward()
    #         elif self.x > target_x:
    #             if self.direction != 'Left':
    #                 self.turn_right()
    #                 if self.direction != 'Left':
    #                     self.turn_right()
    #             self.move_forward()

    def take_resources(self, resource):
        state = False
        for i, row in enumerate(self.vision):
            for j, cell in enumerate(row):
                if cell[resource] > 0:
                    self.move_to(j, i)  # Adjusted for row-column order
                    for _ in range(cell[resource]):
                        self.queue.append(f'Take {resource}')
                    state = True
        return state

    def algorithm(self):
        # Set initial position and direction of the player in the vision grid
        self.y = 0
        self.x = len(self.vision[0]) // 2

        self.move_left()
        # self.direction = 'Down'
        # Check if there is food in the vision
        # if self.inventory['food'] < 10:
        #     if self.take_resources('food'):
        #         return self.queue
        
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
        self.max_queue_size = 10

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
        self.send(self.name)
    
    def run(self):
        self.connect()
        self.receive(self.socket)
        self.receive(self.socket)
        
        while True:
            self.update_vision()
            self.update_inventory()
            self.queue = self.ai.algorithm()       
            print(self.queue) 
            self.send_queue()

def main():
    args = sys.argv[1:]
    parser = ParseArgs()
    host, port, name = parser.parse(args)
    client = Client(host, port, name)
    client.run()

if __name__ == "__main__":
    main()
