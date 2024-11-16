#include <iostream>
#include "pugixml.hpp"
#include "request_receiver.hpp"
#include "server.hpp"

int main()
{
    std::string erorr_message;

    Server server(61499, erorr_message);
    std::cout << erorr_message << std::endl;
    server.WaitForConnection(erorr_message);
    std::cout << erorr_message << std::endl;

    ErrorCode error;

    while (true) {
        RawRequest received_request = ReceiveRequest(server, error).value();
        if (received_request.xml_string.length() == 1) {
            std::cout << "CONNECTION CLOSED" << '\n';   
            break;
        }

        std::cout << "Received request: " << received_request.xml_string << '\n';

        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_string(received_request.xml_string.c_str());

        pugi::xml_node root = doc.document_element();

        

        pugi::xml_attribute id_attribute = root.attribute("ID");
        uint response_index = id_attribute.as_uint();

        std::string respose = "<Response ID=\"" + std::to_string(response_index) + "\" />";
        server.Send<char>('P');
        server.Send<uint16_t>(respose.size());
        server.SendString(respose);
        std::cout << "Sent response: " << respose << '\n';
    }

    return 0;
}
