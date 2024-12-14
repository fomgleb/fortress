#ifndef FORTRESS_FUNCTIONAL_BLOCK_HPP_
#define FORTRESS_FUNCTIONAL_BLOCK_HPP_

#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <vector>

class FunctionalBlock {
  protected:
    std::string name;
    uint64_t counter;
    std::vector<std::shared_ptr<FunctionalBlock>> nextBlocks;
    std::vector<std::string> nextOuts;
    std::vector<std::string> cnfReqQueue;

  public:
    FunctionalBlock(const std::string& blockName);
    virtual ~FunctionalBlock() {}
    void add_process();
    void addNextBlock(std::shared_ptr<FunctionalBlock> block, const std::string& out);
    void addReq(std::string cnfreq);
    std::vector<std::string> returnReq();
    virtual void process() = 0;
    virtual void hand_over_in(std::string in, std::string out) = 0;
    std::string getName() const;
};

class START : public FunctionalBlock {
  private:
    std::string COLD;
    std::string WARM;
    std::string STOP;

  public:
    START(const std::string& blockName);
    void process() override;
    void hand_over_in(std::string in, std::string out) override;
};

#endif /* FORTRESS_FUNCTIONAL_BLOCK_HPP_ */
