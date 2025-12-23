#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include <unordered_map>
#include "block.h"
#include "user.h"

class Blockchain {
private:
    std::vector<Block> chain;
    std::unordered_map<unsigned long, std::string> ipRegistry;

    unsigned long computeBlockHash(const Block &b);

public:
    Blockchain();

    bool registerUser(const std::string &userID);
    bool createBlock(const std::string &creatorID, const std::string &content);
    bool verifyOwnership(const std::string &creatorID, const std::string &content);

    void viewChain();

    std::unordered_map<std::string, User> users;
};

#endif
