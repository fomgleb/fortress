#include <iostream>
#include "pugixml.hpp"
#include "request_receiver.hpp"
#include "server.hpp"
#include "parser.hpp"

/*
void processRequest(const std::string& xml)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(xml.c_str());

    if (!result) {
        std::cerr << "Failed to parse XML: " << result.description() << std::endl;
        return;
    }

    pugi::xml_node request = doc.child("Request");
    if (!request) {
        std::cerr << "Request element not found" << std::endl;
        return;
    }

    std::string action = request.attribute("Action").as_string();
    std::cout << "Action: " << action << std::endl;

    if (action == "QUERY" || action == "CREATE") {
        pugi::xml_node fb = request.child("FB");
        if (fb) {
            std::string name = fb.attribute("Name").as_string();
            std::string type = fb.attribute("Type").as_string();
            std::cout << "FB Name: " << name << ", Type: " << type << std::endl;
        } else {
            std::cerr << "FB element not found" << std::endl;
        }
    } else if (action == "WRITE" || action == "CREATE") {
        pugi::xml_node connection = request.child("Connection");
        if (connection) {
            std::string source = connection.attribute("Source").as_string();
            std::string destination = connection.attribute("Destination").as_string();
            std::cout << "Connection Source: " << source << ", Destination: " << destination << std::endl;
        } else {
            std::cerr << "Connection element not found" << std::endl;
        }
    } else if (action == "START") {
        std::cout << "Action: START" << std::endl;
    } else {
        std::cerr << "Unknown action: " << action << std::endl;
    }
}
*/

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
        processRequest(received_request.xml_string);
        
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_string(received_request.xml_string.c_str());

        pugi::xml_node root = doc.document_element();

        if (std::string(root.attribute("Action").as_string()) == "CREATE") {
            pugi::xml_node child = root.first_child();
            std::cout << std::string(child.name()) << std::endl;
        }

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
