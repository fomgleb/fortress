#ifndef FORTRESS_FUNCTIONAL_BLOCK_HPP_
#define FORTRESS_FUNCTIONAL_BLOCK_HPP_

#include <string>
#include <vector>
#include <memory>
#include <queue>
#include <iostream>

class FunctionalBlock {
protected:
    std::string name;
    uint64_t counter;
    std::vector<std::shared_ptr<FunctionalBlock>> nextBlocks;
    std::vector<std::string> nextOuts;
    std::vector<std::string> cnfReqQueue;
public:
    FunctionalBlock(const std::string& blockName) : name(blockName), counter(0) {}
    virtual ~FunctionalBlock() {}
    void add_process() { counter++; }
    void addNextBlock(std::shared_ptr<FunctionalBlock> block, const std::string& out) {
        nextBlocks.push_back(block);
        nextOuts.push_back(out);
    }
    void addReq(std::string cnfreq){
        cnfReqQueue.push_back(cnfreq);
    }
    std::vector<std::string> returnReq(){
        return cnfReqQueue;
    }
    virtual void process() = 0;
    virtual void hand_over_in(std::string in, std::string out) = 0;
    std::string getName() const { return name; }
};

class STRING2STRING : public FunctionalBlock {
private:
    std::string IN;
    std::string OUT;

public:
    STRING2STRING(const std::string& blockName) : FunctionalBlock(blockName) {}
    void setValue(const std::string& value) { IN = value; }
    void process() override {
        OUT = IN;
        add_process();
        for (size_t i = 0; i < nextBlocks.size(); i++) {
            nextBlocks[i].get()->hand_over_in(nextOuts[i], OUT);
        }
    }
    void hand_over_in(std::string in, std::string out) override {
        if (in == "IN"){
            IN = out;
        }
    }
    std::string show() {return IN;}
};

class APPEND_STRING : public FunctionalBlock {
private:
    std::string IN_1;
    std::string IN_2;
    std::string OUT;

public:
    APPEND_STRING(const std::string& blockName) : FunctionalBlock(blockName) {}
    void process() override {
        OUT = IN_1 + IN_2;
        std::cout << "String: " << OUT << '\n';
        add_process();
    }
        void hand_over_in(std::string in, std::string out) override {
        if (in == "IN_1"){
            IN_1 = out;
        }
        else if(in == "IN_2"){
            IN_2 = out;
        }
    }
};

class START : public FunctionalBlock {
private:
    std::string COLD;
    std::string WARM;
    std::string STOP;

public:
    START(const std::string& blockName) : FunctionalBlock(blockName) {}
    void process() override {
        WARM = "";
    }
    void hand_over_in(std::string in, std::string out) override {
        WARM = "";
    }
};

#endif /* FORTRESS_FUNCTIONAL_BLOCK_HPP_ */
