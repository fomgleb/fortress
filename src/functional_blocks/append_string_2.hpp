#ifndef FORTRESS_APPEND_STRING_2_HPP_
#define FORTRESS_APPEND_STRING_2_HPP_

#include "functional_block.hpp"

class APPEND_STRING : public FunctionalBlock {
  private:
    std::string IN_1;
    std::string IN_2;
    std::string OUT;

  public:
    APPEND_STRING(const std::string& blockName);
    void process();
    void hand_over_in(std::string in, std::string out);
};

#endif /* FORTRESS_APPEND_STRING_2_HPP_ */
