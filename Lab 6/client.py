import socket

try:
    # Connect to the server
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect(("localhost", 8080))

    # Get the numbers from the user
    while True:
        try:
            num1 = int(input("<Client> Enter the first number: "))
            break
        except ValueError:
            print("<Client> Invalid input.")
    while True:
        try:
            num2 = int(input("<Client> Enter the second number: "))
            break
        except ValueError:
            print("<Client> Invalid input.")

    # Send the numbers to the server
    sock.sendall(f"{num1} {num2}".encode())

    # Receive the result from the server
    result = sock.recv(1024).decode().strip()
    print(f"<Server> The sum of two numbers: {result}\n")

except ConnectionRefusedError:
    print("<Client> Failed to connect to the server.")
except OSError:
    print("<Client> Error communicating with the server.")
finally:
    if "sock" in locals():
        sock.close()
