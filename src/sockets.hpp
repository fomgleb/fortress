#ifndef FORTRESS_SOCKETS_HPP_
#define FORTRESS_SOCKETS_HPP_

#include <string>
#include <system_error>

class Server {
  public:
    Server(uint16_t port, std::string& error_message);
    ~Server();

    void WaitForConnection(std::string& error_message);
    template <typename T>
    T Receive() const;
    std::string ReceiveString(size_t length) const;

  private:
    int connection_socket_;
    int client_socket_;

    ssize_t ReceiveBytes(char* buffer, size_t length) const;
};

#include "sockets_impl.hpp"

#endif // FORTRESS_SOCKETS_HPP_
