#include <iostream>
#include "pugixml.hpp"
#include "sockets.hpp"

int main()
{
    std::string erorr_message;

    Server server(61499, erorr_message);
    std::cout << erorr_message << std::endl;
    server.WaitForConnection(erorr_message);
    std::cout << erorr_message << std::endl;
    std::string message = server.Receive(erorr_message);
    std::cout << erorr_message << std::endl;
    std::cout << "message = \"" << message << "\"" << std::endl;

    return 0;
}
