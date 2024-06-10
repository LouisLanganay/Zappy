#!/usr/bin/env python3
import socket
import sys


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
        self.port = port
        self.inventaire = {"food": 0,
                            "linemate" : 0,
                            "deraumere": 0,
                            "sibur" : 0,
                            "mendiane" : 0,
                            "phiras" : 0,
                            "thystame" : 0}

        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((self.host, self.port))
    def send(self, data):
        self.socket.send(data.encode())

    def receive(self):
        return self.socket.recv(1024).decode()

    def close(self):
        self.socket.close()



    def command_rcv(self, msg_rcv, input):
        if(input == "Inventory"):
            print("test:", msg_rcv)

            msg_rcv = msg_rcv.strip('[]').strip()
            items = msg_rcv.split(',')
            for item in items:
                parts = item.strip().split()
                key = parts[0]
                value = int(parts[1])
                self.inventaire[key] = value
        print("mon dico:", self.inventaire)
# Lancer le Zappy si inventory pas vide au lancement le remplir sinon remplir l'inventaire une fois rammaser object
# faire le systeme de vision
# faire le systeme d'évolution
# attention décalage lorsque -n remplis




if __name__ == '__main__':
    args = ParseArgs()
    host, port, name = args.parse(sys.argv[1:])
    client = Client(host, port, name)
    try:
        print("Connected to server")
        client.send(name + '\n')
        print("Received:", client.receive())
        while True:
            msg_receive = client.receive()
            print("Received: ", msg_receive)
            message = input("Enter message to send (type 'exit' to close): ")
            client.command_rcv(msg_receive, message)
            print(message)
            if message.lower() == 'exit':
                message += '\n'
                client.send(message)
                break
            message += "\n"
            client.send(message)
    except KeyboardInterrupt:
        print("\nKeyboard interrupt")
    finally:
        client.close()