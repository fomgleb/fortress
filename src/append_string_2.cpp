#include "append_string_2.hpp"

APPEND_STRING::APPEND_STRING(const std::string& blockName) : FunctionalBlock(blockName) {}

void APPEND_STRING::process()
{
    OUT = IN_1 + IN_2;
    std::cout << "String: " << OUT << '\n';
    add_process();
}

void APPEND_STRING::hand_over_in(std::string in, std::string out)
{
    if (in == "IN_1") {
        IN_1 = out;
    } else if (in == "IN_2") {
        IN_2 = out;
    }
}
