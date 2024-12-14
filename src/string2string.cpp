#include "string2string.hpp"

STRING2STRING::STRING2STRING(const std::string& blockName) : FunctionalBlock(blockName) {}

void STRING2STRING::setValue(const std::string& value)
{
    IN = value;
}

void STRING2STRING::process()
{
    OUT = IN;
    add_process();
    for (size_t i = 0; i < nextBlocks.size(); i++) {
        nextBlocks[i].get()->hand_over_in(nextOuts[i], OUT);
    }
}

void STRING2STRING::hand_over_in(std::string in, std::string out)
{
    if (in == "IN") {
        IN = out;
    }
}
std::string STRING2STRING::show()
{
    return IN;
}
