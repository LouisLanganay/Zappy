#!/usr/bin/env python3
import socket
import sys
import selectors
import random
import time

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
