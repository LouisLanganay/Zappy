import socket

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
    client = Client('localhost', 12345)
    try:
        while True:
            message = input("Enter message to send (type 'exit' to close): ")
            if message.lower() == 'exit':
                break
            client.send(message)
            print("Received:", client.receive())
    finally:
        client.close()