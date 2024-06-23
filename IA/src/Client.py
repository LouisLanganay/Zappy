#!/usr/bin/env python3
import socket
import sys
import selectors
import time
from ParseArgs import ParseArgs
from AI import AI

class Client:
    def __init__(self, host, port, name, id):
        self.host = host
        self.port = int(port)
        self.name = name
        self.id = id
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((self.host, self.port))
        self.queue = []

        self.selector = selectors.DefaultSelector()
        self.selector.register(self.socket, selectors.EVENT_READ, self.receive)

        self.ai = AI(self.id)
        self.has_all_resources = False

    def send(self, data):
        self.socket.send(data.encode() + b'\n')

    def receive(self):
        buffer = ""
        while True:
            data = self.socket.recv(512).decode().strip()
            
            if not data:
                print("Server closed the connection")
                sys.exit(0)
            
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
            buffer = self.socket.recv(512).decode().strip()
            count += 1
        
        return buffer

    def update_inventory(self):
        self.send('Inventory')
        data = self.receive()
        self.ai.update_state(data)

    def update_vision(self):
        self.send('Look')
        data = self.receive()
        self.ai.update_state(data)

    def send_queue(self):
        for elt in self.queue:
            self.send(elt)
            data = self.receive()
            if data.startswith('dead'):
                self.revive_client()
            self.ai.update_state(data)
        self.queue.clear()

    def send_broadcast(self, message):
        self.send(f"Broadcast {message}")
        data = self.receive()

    def revive_client(self):
        self.socket.close()
        self.ai = AI(self.id)
        self.queue = []
        self.has_all_resources = False
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((self.host, self.port))
        self.selector.register(self.socket, selectors.EVENT_READ, self.receive)
        print(f"Client {self.id} reconnected to server.")

    def handle_broadcast(self, message):
        temp = message[8:]
        temp = temp.split(', ')

        direction = int(temp[0])
        data = temp[1]

        if self.ai.mode == 'STOP':
            self.ai.count_incanter += 1
            if self.ai.count_incanter == 6:
                self.ai.mode = 'Incantation'
                return
            
        if data.startswith('Ready'):
            #data -> f'Ready:{self.id}'
            data = data.split(':')[1]
            id = int(data)
            self.ai.has_all_resources_dict[self.ai.map_resource(id)] = True
        
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
            self.ai.mode = 'STOP'
            self.ai.count_incanter += 1
            # self.send_broadcast('Incantation')
            self.queue.clear()
            print("Group is over")
            self.run()
            return

        if self.ai.mode == 'Group':
            action = self.ai.action_to_broadcaster()
            if action != None:
                self.send(action)

            data = self.receive()
            while True:
                data = self.receive()
                if data.startswith('dead'):
                    self.revive_client()
                if data.startswith('message'):
                    self.handle_broadcast(data)
                    break

    def close(self):
        self.selector.unregister(self.socket)
        self.socket.close()

    def connect(self):
        data = self.receive()  # Initial connection response (welcome message)
        self.send(self.name)
        data = self.receive()  # Additional server response (map size)
        if data == 'ko':
            sys.exit(84)
        return 0

    def run(self):
        if self.ai.id == 0:
            self.send('Fork')
            data = self.receive()
        while True:
            if self.ai.mode == 'STOP':
                self.queue = self.ai.drop_resources()
                self.send_queue()
                continue

            if self.ai.count_incanter == 6 and (self.ai.mode == 'Incantation' or self.ai.mode == 'Group' or self.ai.mode == 'STOP'):
                self.ai.mode = 'Incantation'
                self.send('Look')
                data = self.receive()
                vision = self.ai._parse_input_list(data.strip('[]'))
                if vision[0].count('player') == 6:
                    self.queue = self.ai.drop_resources()
                    self.send_queue()
                    self.queue = ['Incantation']
                    self.send_queue()
                continue

            if self.ai.mode == 'Normal':
                self.queue = ['Look', 'Inventory']
                self.send_queue()
                self.queue = self.ai.algorithm()
                self.send_queue()

            if self.ai.mode == 'Broadcaster':
                self.queue = self.ai.drop_resources()
                self.send_queue()
                self.send_broadcast('Group')
                time.sleep(0.1)
                continue

            if self.ai.has_all_resources() and self.ai.has_all_resources_dict[self.ai.map_resource(self.id)] == False and self.ai.mode == 'Normal' and self.ai.inventory['food'] > 30:
                self.send_broadcast(f'Ready:{self.id}')
                self.ai.has_all_resources_dict[self.ai.map_resource(self.id)] = True
                continue

            if self.ai.has_all_resources_dict_func() and self.ai.mode == 'Normal' and self.ai.id == 0:
                self.ai.mode = 'Broadcaster'
                self.ai.count_incanter += 1
                continue

def main():
    args = sys.argv[1:]
    parser = ParseArgs()
    host, port, name, id = parser.parse(args)
    client = Client(host, port, name, id)
    client.connect()
    client.run()
    client.close()

if __name__ == "__main__":
    main()
