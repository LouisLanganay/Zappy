import sys
import socket

class ParseArgs:
    def __init__(self):
        self.host = 'localhost'
        self.port = -1
        self.name = ''
        self.id = -1  # Initialize the ID attribute

    def check_type(self):
        try:
            self.port = int(self.port)
            self.id = int(self.id)  # Check if ID is an integer
        except ValueError:
            self.print_invalid_argument()
            sys.exit(84)
        
        if self.port == -1 or self.name == '' or self.id == -1:  # Check if ID is provided
            self.print_usage()
            sys.exit(84)

        self.check_host()
        self.check_port()
        self.check_name()
        self.check_id()  # Check ID

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

    def check_id(self):
        if self.id < 0:
            print("Error: ID must be a non-negative integer")
            sys.exit(84)

    def parse(self, args):
        for i in range(0, len(args), 2):
            if args[i] == '-p':
                self.port = args[i + 1]
            elif args[i] == '-n':
                self.name = args[i + 1]
            elif args[i] == '-h':
                self.host = args[i + 1]
            elif args[i] == '-id':
                self.id = args[i + 1]
            else:
                self.print_invalid_argument()
                sys.exit(84)

        self.check_type()
        return self.host, self.port, self.name, self.id

    def print_usage(self):
        print("USAGE: ./zappy_ai -p port -n name -h machine -id id")
        sys.exit(84)

    def print_invalid_argument(self):
        print("Invalid argument")
        sys.exit(84)

# Example usage
if __name__ == "__main__":
    args = ParseArgs()
    host, port, name, id = args.parse(sys.argv[1:])
    print(f"Host: {host}, Port: {port}, Name: {name}, ID: {id}")
