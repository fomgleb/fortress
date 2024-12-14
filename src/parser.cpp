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

    if (action == "CREATE") {
        pugi::xml_node child = request.first_child();
        if (std::string(child.name()) == "FB") {
            std::string name = child.attribute("Name").as_string();
            std::string type = child.attribute("Type").as_string();
            std::cout << "FB Name: " << name << ", Type: " << type << std::endl;
            
            if (type == "EMB_RES"){
                blockMap["START"] = std::make_shared<START>("START");
                cnfReqQueue.push("START");
            }
            else if (type == "STRING2STRING") {
                blockMap[name] = std::make_shared<STRING2STRING>(name);
            }
            else if (type == "APPEND_STRING_2") {
                blockMap[name] = std::make_shared<APPEND_STRING>(name);
            }
        }
        else if (std::string(child.name()) == "Connection") {
            std::string source = child.attribute("Source").as_string();
            std::string destination = child.attribute("Destination").as_string();
            std::cout << "Connection Source: " << source << ", Destination: " << destination << std::endl;

            size_t destinationDotIndex = destination.find('.');
            std::string destinationBlockName = destination.substr(0, destinationDotIndex);
            std::string destinationOut = destination.substr(destinationDotIndex + 1);

            size_t sourceDotIndex = source.find('.');
            std::string sourceBlockName = source.substr(0, sourceDotIndex);
            std::string sourceOut = source.substr(sourceDotIndex + 1);

            if (destinationOut == "REQ") {
                blockMap[sourceBlockName].get()->addReq(destinationBlockName);
            } else {
                blockMap[sourceBlockName].get()->addNextBlock(blockMap[destinationBlockName], destinationOut);
            }
        }
        else {
            std::cerr << "FB or Connection element not found" << std::endl;
        }
    }
    else if (action == "WRITE") {
        pugi::xml_node connection = request.child("Connection");
        if (connection) {
            std::string source = connection.attribute("Source").as_string();
            source = source.substr(1, source.size() - 2);
            std::string destination = connection.attribute("Destination").as_string();
            std::cout << "Connection Source: " << source << ", Destination: " << destination << std::endl;

            size_t pos = destination.find('.');
            if (pos != std::string::npos) {
                std::string blockName = destination.substr(0, pos);
                std::string out = destination.substr(pos + 1);
                
                static_cast<STRING2STRING*>(blockMap[blockName].get())->setValue(source);
                std::cout << static_cast<STRING2STRING*>(blockMap[blockName].get())->show() << '\n';
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
                std::vector<std::string> req = blockMap[blockName].get()->returnReq();
                for (size_t i = 0; i < req.size(); i++) {
                    cnfReqQueue.push(req[i]);
                }
                blockMap[blockName]->process();
            }
        }
    }
    else {
        std::cerr << "Unknown action: " << action << std::endl;
    }
}
