#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <unordered_map>
#include <cmath>
#include <cstdlib>

using namespace std;

int modExp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

unsigned long djb2Hash(const string &input) {
    unsigned long hash = 5381;
    for (char c : input) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

struct Block {
    int index;
    unsigned long prevHash;
    unsigned long ipHash;
    string creatorID;
    time_t timestamp;

    Block(int idx, unsigned long prev, unsigned long hash, string creator)
        : index(idx), prevHash(prev), ipHash(hash), creatorID(creator), timestamp(time(nullptr)) {}
};

class Verifier {
public:
    static const int p = 7057;
    static const int g = 5;
    unordered_map<int, int> verify_dict;
    int rand_h_create(int h) {
        int b = rand() % 2;
        verify_dict[h] = b;
        return b;
    }
    bool check_h(int h, int s, int y) {
        if (verify_dict.find(h) == verify_dict.end()) return false;
        int b = verify_dict[h];
        int a = modExp(g, s, p);
        int b0 = (h * modExp(y, b, p)) % p;
        return a == b0;
    }
};

class Blockchain {
private:
    vector<Block> chain;
    unordered_map<string, vector<Block>> userHistory;

    Block createGenesisBlock() {
        return Block(0, 0, 0, "system");
    }

public:
    Blockchain() {
        chain.push_back(createGenesisBlock());
    }

    void createBlock(const string &creatorID, const string &ipData) {
        unsigned long ipHash = djb2Hash(ipData);
        for (const auto &entry : userHistory) {
            for (const Block &block : entry.second) {
                if (block.ipHash == ipHash && block.creatorID != creatorID) {
                    cout << "Error: Content with this hash is already registered under user "
                        << block.creatorID << ". Block creation denied." << endl;
                    return;
                }
            }
        }
        int i = chain.size();
        Block newBlock(i, chain.back().prevHash, ipHash, creatorID);
        newBlock.prevHash = chain.back().ipHash;
        chain.push_back(newBlock);
        userHistory[creatorID].push_back(newBlock);
        cout << "Block created for " << creatorID << " with IP hash: " << ipHash << endl;
    }

    void viewAllTransactions() {
        cout << "Displaying all blocks in the blockchain:" << endl;
        for (const Block &block : chain) {
            cout << "Block #" << block.index << ", Creator ID: " << block.creatorID
                 << ", IP Hash: " << block.ipHash << ", Previous Hash: " << block.prevHash
                 << ", Timestamp: " << ctime(&block.timestamp);
        }
    }

    bool verificationZKP(unsigned long ipHash) {
        Verifier verifier;
        int prime_number = verifier.p;
        int gen_for_prime = verifier.g;
        int r = rand() % prime_number;
        int h = modExp(gen_for_prime, r, prime_number);
        int b = verifier.rand_h_create(h);
        int s = (r + b * ipHash) % (prime_number - 1);
        int y = modExp(gen_for_prime, ipHash, prime_number);
        return verifier.check_h(h, s, y);
    }

    bool verifyTransaction(const string &creatorID, const string &ipData) {
        unsigned long ipHash = djb2Hash(ipData);
        for (const Block &block : userHistory[creatorID]) {
            if (block.ipHash == ipHash && block.creatorID == creatorID) {
                cout << "Ownership verified for " << creatorID << " with IP hash: " << ipHash << endl;
                if (verificationZKP(ipHash)) {
                    cout << "Zero-Knowledge Proof verified successfully." << endl;
                    return true;
                } else {
                    cout << "Zero-Knowledge Proof verification failed." << endl;
                }
            }
        }
        cout << "Ownership verification failed." << endl;
        return false;
    }
};

int main() {
    Blockchain blockchain;
    int c;

    while (true) {
        cout << "Enter 1 to create a new block" << endl;
        cout << "Enter 2 to verify a transaction" << endl;
        cout << "Enter 3 to view all transactions/blocks" << endl;
        cout << "Enter 4 to exit" << endl;
        cin >> c;

        if (c == 1) {
            cout << "Enter creator ID: ";
            string creatorID;
            cin >> creatorID;
            cin.ignore();
            cout << "Enter content: ";
            string ipData;
            getline(cin, ipData);
            blockchain.createBlock(creatorID, ipData);
        } else if (c == 2) {
            cout << "Enter creator ID: ";
            string creatorIDtc;
            cin >> creatorIDtc;
            cin.ignore();
            cout << "Enter content: ";
            string ipDatatc;
            getline(cin, ipDatatc);
            blockchain.verifyTransaction(creatorIDtc, ipDatatc);
        } else if (c == 3) {
            blockchain.viewAllTransactions();
        } else if (c == 4) {
            break;
        } else {
            cout << "Invalid option. Please try again." << endl;
        }
        cout << endl;
    }

    return 0;
}
