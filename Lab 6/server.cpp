#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <vector>

#define PORT 8080

// Sum of two numbers
int sum(char buffer[1024])
{
    int num1, num2;
    sscanf(buffer, "%d%d", &num1, &num2);
    printf("<Client> %d + %d\n", num1, num2);

    int sum = num1 + num2;
    printf("<Server> Sum: %d\n\n", sum);

    return sum;
}

// Accept and send back to client
void client(int new_socket)
{
    int valread;
    char buffer[1024] = {0};
    valread = read(new_socket, buffer, 1024);

    char result[1024];
    sprintf(result, "%d", sum(buffer));

    send(new_socket, result, strlen(result), 0);
    close(new_socket);

    printf("<Client> A client left.\n\n");
}

int main(int argc, char const *argv[])
{
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("<Server> Socket failed.");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt)))
    {
        perror("<Server> setsockopt() failed.");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        perror("<Server> bind() failed.");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("<Server> listen() failed.");
        exit(EXIT_FAILURE);
    }

    printf("<Server> Waiting for client...\n");

    // Launch acceptClient() as an asynchronous thread
    std::vector<std::thread> threads;
    while (true)
    {
        int new_socket;
        struct sockaddr_in client_address;
        int addrlen = sizeof(client_address);

        if ((new_socket = accept(server_fd, (struct sockaddr *)&client_address, (socklen_t *)&addrlen)) < 0)
        {
            perror("<Server> accept() failed.");
            exit(EXIT_FAILURE);
        }

        threads.emplace_back(client, new_socket);
        for (auto it = threads.begin(); it != threads.end();)
        {
            if (it->joinable())
            {
                printf("<Client> A client joined.\n\n");
                it->join();
                it = threads.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    // Close socket
    shutdown(server_fd, SHUT_RDWR);

    return 0;
}