#!/usr/bin/env python3
import socket
import sys

def main():
    if len(sys.argv) != 3:
        print("Usage: python simple_client.py <host> <port>")
        return
    
    host = sys.argv[1]
    port = int(sys.argv[2])

    try:
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        
        client_socket.connect((host, port))
        print(f"Connected to {host}:{port}")

        command_queue = ['Forward', 'Right']

        while True:
            for command in command_queue:
                client_socket.sendall(command.encode())

                data = client_socket.recv(1024)
                if not data:
                    print("Server closed the connection")
                    break

                print(f"Sent: {command}, Received: {data.decode()}")

    except KeyboardInterrupt:
        print("\nUser interrupted. Exiting...")
    except Exception as e:
        print(f"Error: {e}")
    finally:
        client_socket.close()
        print("Connection closed.")

if __name__ == "__main__":
    main()
