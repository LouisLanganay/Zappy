#!/usr/bin/env python3
import socket
import sys
import selectors
from ParseArgs import ParseArgs

class Client:
    def __init__(self, host, port, name):
        self.host = host
        self.port = int(port)
        self.name = name
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((self.host, self.port))

        self.selector = selectors.DefaultSelector()
        self.selector.register(self.socket, selectors.EVENT_READ, self.receive)

        self.command_queue = []
        self.max_queue_size = 10

    def send(self, data):
        self.socket.send(data.encode())

    def send_queue(self):
        for elt in self.command_queue:
            self.send(elt)
            data = self.receive(self.socket)

    def receive(self, sock):
        data = sock.recv(1024).decode().strip()
        if not data:
            print("Server closed the connection")
            sys.exit(0)
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
            self.command_queue = ['Look\n', 'Forward\n', 'Forward\n', 'Right\n']
            self.send_queue()

def main():
    args = sys.argv[1:]
    parser = ParseArgs()
    host, port, name = parser.parse(args)
    client = Client(host, port, name)
    client.run()

if __name__ == "__main__":
    main()
