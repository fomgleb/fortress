#include <iostream>
#include "pugixml.hpp"
#include "request_receiver.hpp"
#include "sockets.hpp"

int main()
{
    std::string erorr_message;

    Server server(61499, erorr_message);
    std::cout << erorr_message << std::endl;
    server.WaitForConnection(erorr_message);
    std::cout << erorr_message << std::endl;

    ErrorCode error;
    RawRequest received_request = ReceiveRequest(server, error).value();

    std::cout << "Received request: " << received_request.xml_string << std::endl;;

    return 0;
}
