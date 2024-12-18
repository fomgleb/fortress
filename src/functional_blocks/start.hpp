#ifndef FORTRESS_START_HPP_
#define FORTRESS_START_HPP_

#include "functional_block.hpp"

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

#endif /* FORTRESS_START_HPP_ */
