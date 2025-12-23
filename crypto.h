#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>

unsigned long djb2Hash(const std::string &input);
int modExp(int base, int exp, int mod);

#endif
