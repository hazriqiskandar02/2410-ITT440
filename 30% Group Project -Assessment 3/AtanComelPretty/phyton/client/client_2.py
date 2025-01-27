import socket

def send_request(message):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_address = ("127.0.0.1", 1027)  # Host IP updated to 192.168.32.2

    # Send the message to the server
    client_socket.sendto(message.encode(), server_address)

    # Receive response from the server
    response, _ = client_socket.recvfrom(1024)
    print(f"Server: {response.decode()}")

    client_socket.close()

def main():
    print("Choose an option:")
    print("1. Update points for Atan_Pretty2")
    print("2. Get points for Atan_Pretty2")
    option = input("Enter option: ")

    username = "Atan_Pretty2"  # Hardcoded username

    if option == '1':
        # Update points
        send_request(f"UPDATE:{username}")
    elif option == '2':
        # Get points
        send_request(f"GET_POINTS:{username}")
    else:
        print("Invalid option")

if __name__ == "__main__":
    main()

