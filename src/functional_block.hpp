#ifndef FORTRESS_FUNCTIONAL_BLOCK_HPP_
#define FORTRESS_FUNCTIONAL_BLOCK_HPP_

#include <string>
#include <vector>

class FunctionalBlock {
  private:
    std::string name;
    uint64_t counter;

    std::vector<FunctionalBlock&> nextBlocks;
    std::vector<std::string> nextOuts;

    // std::vector<FunctionalBlock&>

  public:
    FunctionalBlock(/* args */);
    ~FunctionalBlock();
};

class String2String : FunctionalBlock {
  private:
    std::string value;

  public:
    void setValue(std::string value);
    void process();
};

#endif /* FORTRESS_FUNCTIONAL_BLOCK_HPP_ */
