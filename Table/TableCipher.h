#ifndef TABLECIPHER_H
#define TABLECIPHER_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <string>

class Cipher {
private:
    int key;
    std::string getValidOpenText(const std::string& s);
    std::string getValidCipherText(const std::string& s);
    int getValidKey(const int key, const std::string& s);

public:
    Cipher() = delete;
    Cipher(const std::string& skey);
    std::string encrypt(const std::string& open_text);
    std::string decrypt(const std::string& cipher_text);
    
};

class cipher_error: public std::invalid_argument
{
public:
    explicit cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};

#endif
