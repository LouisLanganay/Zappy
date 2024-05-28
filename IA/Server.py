import socket

class Server:
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.bind((self.host, self.port))
        self.socket.listen(5)
        print(f'Server listening on {self.host}:{self.port}')

    def start(self):
        while True:
            client_socket, client_address = self.socket.accept()
            print(f'Connection from {client_address}')
            while True:
                data = client_socket.recv(1024).decode()
                if not data:
                    break
                print(f'Received: {data}')
                client_socket.send(f'Echo: {data}'.encode())
            client_socket.close()

    def stop(self):
        self.socket.close()

if __name__ == '__main__':
    server = Server('localhost', 12345)
    try:
        server.start()
    except KeyboardInterrupt:
        server.stop()
        print('Server stopped.')