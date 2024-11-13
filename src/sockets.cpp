#include "sockets.hpp"

#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

Server::Server(uint16_t port, std::string& error_message)
{
    // Create socket
    connection_socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (connection_socket_ == -1) {
        error_message = strerror(errno);
        return;
    }

    // Bind socket
    sockaddr_in address = {};
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if (bind(connection_socket_, reinterpret_cast<sockaddr*>(&address), sizeof(address)) == -1) {
        error_message = strerror(errno);
        return;
    }

    // Listen socket
    if (listen(connection_socket_, 5) == -1) {
        error_message = strerror(errno);
        return;
    }
}

Server::~Server()
{
    close(connection_socket_);
    close(client_socket_);
}

void Server::WaitForConnection(std::string& error_message)
{
    client_socket_ = accept(connection_socket_, NULL, NULL);
    if (client_socket_ == -1) {
        error_message = strerror(errno);
        return;
    }
}

std::string Server::Receive(std::string& error_message)
{
    static const int buffer_len = 500;
    char buffer[buffer_len];
    recv(client_socket_, buffer, buffer_len, 0);
    return std::string(buffer);
}
