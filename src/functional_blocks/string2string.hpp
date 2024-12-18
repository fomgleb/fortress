#ifndef FORTRESS_STRING2STRING_HPP_
#define FORTRESS_STRING2STRING_HPP_

#include "functional_block.hpp"

class STRING2STRING : public FunctionalBlock {
  private:
    std::string IN;
    std::string OUT;

  public:
    STRING2STRING(const std::string& blockName);
    void setValue(const std::string& value);
    void process() override;
    void hand_over_in(std::string in, std::string out);
    std::string show();
};

#endif /* FORTRESS_STRING2STRING_HPP_ */
