#include "TableCipher.h"

Cipher::Cipher(const std::string& skey)
{
    try {
        int res = stoi(skey);
        if (res < 0) throw std::string("Negative value");
        key = res;
    } catch(std::invalid_argument e) {
        std::cerr << "Error: Key must be a number\n";
        exit(EXIT_FAILURE);
    } catch(std::string & e) {
        std::cerr << "Error: " << e << std::endl;
        exit(EXIT_FAILURE);
    }
}

std::string Cipher::encrypt(const std::string& open_text)
{
    std::string c = "";
    int poz = key - 1;
    while (poz >= 0) {
        for (uint i = poz; i < open_text.size(); i = i + key) {
            c += open_text[i];
        }
        poz -= 1;
    }
    return c;
}

std::string Cipher::decrypt(const std::string& cipher_text)
{
    std::string d = cipher_text;
    reverse(d.begin(), d.end());
    int poz = 0;
    int strk = d.size()/key;
    std::string last = "";
    int ost = d.size()%key;
    for (int i = 0; i < ost ; i++) {
        last += d[poz];
        d.erase(poz,1);
        poz += strk;
    }
    poz = strk - 1;
    std::string rez = "";
    while (poz >= 0) {
        for (uint i = poz; i < d.size(); i = i + strk) {
            rez += d[i];
        }
        poz -= 1;
    }
    return rez+last;
}
