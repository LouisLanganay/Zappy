import socket
import sys

class Client:
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((self.host, self.port))

    def send(self, data):
        self.socket.send(data.encode())

    def receive(self):
        return self.socket.recv(1024).decode()

    def close(self):
        self.socket.close()

if __name__ == '__main__':
    port = 4242
    if len(sys.argv) > 1:
        if sys.argv[1] == "-p":
            port = sys.argv[2]
    client = Client('localhost', int(port))
    try:
        while True:
            print("Received:", client.receive())
            message = input("Enter message to send (type 'exit' to close): ")
            message[:-1]
            message += "\r\n"
            if message.lower() == 'exit':
                break
            client.send(message)
    except ConnectionError:
        print("\Message not received")
    except KeyboardInterrupt:
        print("\nKeyboard interrupt")
    finally:
        client.close()