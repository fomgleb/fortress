#include "parser.hpp"
#include <iostream>
#include <pugixml.hpp>

std::unordered_map<std::string, std::shared_ptr<FunctionalBlock>> blockMap;
std::queue<std::string> cnfReqQueue;

void processRequest(const std::string& xml) {
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
            
            if (type == "EMB_RES"){
                blockMap["START"] = std::make_shared<START>("START");
            }
            else if (type == "STRING2STRING") {
                blockMap[name] = std::make_shared<STRING2STRING>(name);
            }
            else if (type == "APPEND_STRING_2") {
                blockMap[name] = std::make_shared<APPEND_STRING>(name);
            }
        }
        else {
            std::cerr << "FB element not found" << std::endl;
        }
    }
    else if (action == "WRITE" || action == "CREATE") {
        pugi::xml_node connection = request.child("Conection");
        if (connection) {
            std::string source = connection.attribute("Source").as_string();
            std::string destination = connection.attribute("Destination").as_string();
            std::cout << "Connection Source: " << source << ", Destination: " << destination << std::endl;

            size_t pos = destination.find('.');
            if (pos != std::string::npos) {
                std::string blockName = destination.substr(0, pos);
                std::string out = destination.substr(pos + 1);

                if (blockMap.find(blockName) != blockMap.end() && blockMap.find(source) != blockMap.end()) {
                    blockMap[blockName]->addNextBlock(blockMap[source], out);
                    if (out == "CNF") {
                        cnfReqQueue.push(blockName);
                    }
                }
                else {
                    std::cerr << "Source or destination block not found in blockMap" << std::endl;
                }
            }
        }
        else {
            std::cerr << "Connection element not found" << std::endl;
        }
    }
    else if (action == "START") {
        std::cout << "Action: START" << std::endl;
        // Process the CNF REQ queue
        while (!cnfReqQueue.empty()) {
            std::string blockName = cnfReqQueue.front();
            cnfReqQueue.pop();
            if (blockMap.find(blockName) != blockMap.end()) {
                blockMap[blockName]->process();
            }
        }
    }
    else {
        std::cerr << "Unknown action: " << action << std::endl;
    }
}
