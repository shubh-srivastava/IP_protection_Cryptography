#ifndef USER_H
#define USER_H

#include <string>

struct User {
    std::string id;
    int privateKey;
    int publicKey;

    User(const std::string &uid, int priv, int pub)
        : id(uid), privateKey(priv), publicKey(pub) {}
};

#endif
