#include "functional_block.hpp"

FunctionalBlock::FunctionalBlock(const std::string& blockName) : name(blockName), counter(0) {}

void FunctionalBlock::add_process()
{
    counter++;
}

void FunctionalBlock::addNextBlock(std::shared_ptr<FunctionalBlock> block, const std::string& out)
{
    nextBlocks.push_back(block);
    nextOuts.push_back(out);
}

void FunctionalBlock::addReq(std::string cnfreq)
{
    cnfReqQueue.push_back(cnfreq);
}

std::vector<std::string> FunctionalBlock::returnReq()
{
    return cnfReqQueue;
}

std::string FunctionalBlock::getName() const
{
    return name;
}

START::START(const std::string& blockName) : FunctionalBlock(blockName) {}

void START::process() {}

void START::hand_over_in(std::string in, std::string out) {}
