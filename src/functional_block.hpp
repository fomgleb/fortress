#ifndef FORTRESS_FUNCTIONAL_BLOCK_HPP_
#define FORTRESS_FUNCTIONAL_BLOCK_HPP_

#include <string>
#include <vector>
#include <memory>

class FunctionalBlock {
private:
    std::string name;
    uint64_t counter;
    std::vector<std::shared_ptr<FunctionalBlock>> nextBlocks;
    std::vector<std::string> nextOuts;

public:
    FunctionalBlock(const std::string& name) : name(name), counter(0) {}
    virtual ~FunctionalBlock() {}
    void add_process() { counter++; }
    void addNextBlock(std::shared_ptr<FunctionalBlock> block, const std::string& out) {
        nextBlocks.push_back(block);
        nextOuts.push_back(out);
    }
    virtual void process() = 0;
    std::string getName() const { return name; }
};

class STRING2STRING : public FunctionalBlock {
private:
    std::string IN;
    std::string OUT;

public:
    STRING2STRING(const std::string& name) : FunctionalBlock(name) {}
    void setValue(const std::string& value) { IN = value; }
    void process() override {
        OUT = IN;
        add_process();
    }
};

class APPEND_STRING : public FunctionalBlock {
private:
    std::string IN_1;
    std::string IN_2;
    std::string OUT;

public:
    APPEND_STRING(const std::string& name) : FunctionalBlock(name) {}
    void process() override {
        OUT = IN_1 + IN_2;
        add_process();
    }
};

#endif /* FORTRESS_FUNCTIONAL_BLOCK_HPP_ */
