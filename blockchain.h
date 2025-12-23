#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include <unordered_map>
#include "block.h"
#include "user.h"

using namespace std;

class Blockchain {
private:
    vector<Block> chain;
    unordered_map<unsigned long, string> ipRegistry;

    unsigned long computeBlockHash(const Block &b);

public:
    Blockchain();

    bool registerUser(const string &userID);
    bool createBlock(const string &creatorID, const string &content);
    bool verifyOwnership(const string &creatorID, const string &content);

    void viewChain();

    unordered_map<string, User> users;
};

#endif
