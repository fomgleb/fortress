#include "request_receiver.hpp"

#include <array>
#include <bitset>

// static std::string ReceiveResourceNameStart(const Server& server)
// {

//     return received_resource_name_start;
// }

std::optional<RawRequest> ReceiveRequest(const Server& server, ErrorCode& error)
{
    error = ErrorCode::NO_ERRORS;

    RawRequest received_request;

    const size_t REQUEST_START_PATTERN_SIZE = 3;
    const std::array<char, REQUEST_START_PATTERN_SIZE> REQUEST_START_PATTERN{'P', '\0', '\0'};
    std::array<char, REQUEST_START_PATTERN_SIZE> request_start;
    for (size_t i = 0; i < REQUEST_START_PATTERN_SIZE; i++) {
        request_start[i] = server.Receive<char>();
    }
    if (request_start != REQUEST_START_PATTERN) {
        error = ErrorCode::WRONG_START_OF_RESOURCE_NAME;
        return std::nullopt;
    }

    char received_byte = server.Receive<char>();
    while (received_byte != 'P') {
        received_request.resource_name.push_back(received_byte);
        received_byte = server.Receive<char>();
    }

    uint16_t xml_string_len = server.Receive<uint16_t>();
    received_request.xml_string = server.ReceiveString(xml_string_len);

    return received_request;
}
