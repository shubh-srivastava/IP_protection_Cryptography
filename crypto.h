#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>

using namespace std;

unsigned long djb2Hash(const string &input);
int modExp(int base, int exp, int mod);

#endif
