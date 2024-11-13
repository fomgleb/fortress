#ifndef FORTRESS_SOCKETS_HPP_
#define FORTRESS_SOCKETS_HPP_

#include <string>

class Server {
  public:
    Server(uint16_t port, std::string& error_message);
    ~Server();

    void WaitForConnection(std::string& error_message);
    std::string Receive(std::string& error_message);

  private:
    int connection_socket_;
    int client_socket_;
};

#endif // FORTRESS_SOCKETS_HPP_
