#!/usr/bin/env python3
import socket
import sys
import selectors
import time
from ParseArgs import ParseArgs

class Client:
    def __init__(self, host, port, name):
        self.host = host
        self.port = int(port)
        self.name = name
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.selector = selectors.DefaultSelector()
        self.command_queue = []
        self.max_queue_size = 10

    def connect(self):
        while True:
            try:
                self.socket.connect((self.host, self.port))
                self.selector.register(self.socket, selectors.EVENT_READ, self.receive)
                self.send(self.name + '\n')
                return True
            except socket.error as e:
                print(f"Connection error: {e}. Retrying in 5 seconds...")
                time.sleep(5)

    def send(self, data):
        self.socket.send(data.encode())

    def send_queue(self):
        for elt in self.command_queue:
            self.send(elt)
            data = self.receive(self.socket)
            if not data:
                break

    def receive(self, sock):
        try:
            data = sock.recv(1024).decode().strip()
            if not data:
                raise ConnectionResetError("Server closed the connection")
            return data
        except (ConnectionResetError, socket.error) as e:
            print(f"Connection lost: {e}. Reconnecting...")
            self.selector.unregister(self.socket)
            self.socket.close()
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.connect()
            self.send(self.name + '\n')
            return None

    def close(self):
        self.selector.unregister(self.socket)
        self.socket.close()

    def run(self):
        self.connect()
        self.receive(self.socket)
        self.receive(self.socket)
        
        while True:
            for i in range(10):
                self.command_queue.append('Set food\n')
            self.send_queue()
            self.command_queue.clear()  # Clear the queue after sending all commands
            self.selector.unregister(self.socket)
            self.socket.close()
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.connect()
            self.receive(self.socket)
            self.receive(self.socket)
            
def main():
    args = sys.argv[1:]
    parser = ParseArgs()
    host, port, name = parser.parse(args)
    client = Client(host, port, name)
    client.run()

if __name__ == "__main__":
    main()
