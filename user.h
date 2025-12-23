#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

struct User {
    string id;
    int privateKey;
    int publicKey;

    User(const string &uid, int priv, int pub)
        : id(uid), privateKey(priv), publicKey(pub) {}
};

#endif
