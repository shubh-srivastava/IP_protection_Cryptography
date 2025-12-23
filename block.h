#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <ctime>

struct Block {
    int index;
    unsigned long prevHash;
    unsigned long ipHash;
    unsigned long blockHash;
    std::string creatorID;
    time_t timestamp;

    Block(int idx,
          unsigned long prev,
          unsigned long ip,
          const std::string &creator,
          unsigned long hash)
        : index(idx),
          prevHash(prev),
          ipHash(ip),
          creatorID(creator),
          blockHash(hash),
          timestamp(time(nullptr)) {}
};

#endif
