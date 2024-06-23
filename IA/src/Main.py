#!/usr/bin/env python3
import socket
import sys
import selectors
import time
import subprocess

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
            elif args[i] == '-help':
                self.print_usage()
                sys.exit(0)
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

class MainClient:
    def __init__(self, host, port, name):
        self.host = host
        self.port = port
        self.name = name
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((self.host, self.port))

    def send(self, data):
        self.socket.send(data.encode())

    def receive(self):
        data = self.socket.recv(1024).decode().strip()
        if not data:
            print("Server closed the connection")
            sys.exit(84)
        return data

    def connect_and_get_slots(self):
        self.send(self.name + '\n')
        welcome_msg = self.receive()
        available_slots_msg = self.receive()
        if available_slots_msg == 'ko':
            print("Server refused the connection")
            sys.exit(84)
        available_slots = int(available_slots_msg.split('\n')[0].strip())
        return available_slots + 1

    def close(self):
        self.socket.close()

if __name__ == '__main__':
    args = ParseArgs()
    host, port, name = args.parse(sys.argv[1:])

    mainClient = MainClient(host, port, name)

    available_slots = mainClient.connect_and_get_slots()

    print(f"Available Clients : {available_slots}")

    mainClient.close()

    for i in range(available_slots):
        subprocess.Popen(['./IA/src/Client.py', '-p', str(port), '-n', name, '-id', str(i), '-h', host])


    time.sleep(10)
    subprocess.Popen(['./IA/src/Client.py', '-p', str(port), '-n', name, '-id', str(5), '-h', host])

    while True:
        pass


