#pragma once
#include <vector>
#include <string>
#include <map>
#include <locale>
#include <stdexcept>

using namespace std;

class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error(const std::string& what_arg) : std::invalid_argument(what_arg) {}
    explicit cipher_error(const char* what_arg) : std::invalid_argument(what_arg) {}
};

class modAlphaCipher {
private:
    wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    map<wchar_t, int> alphaNum;
    vector<int> key;
    vector<int> convert(const wstring& s);
    wstring convert(const vector<int>& v);
    wstring getValidKey(const wstring& s);
    wstring getValidOpenText(const wstring& s);
    wstring getValidCipherText(const wstring& s);

public:
    modAlphaCipher() = delete;
    modAlphaCipher(const wstring& skey);
    wstring encrypt(const wstring& open_text);
    wstring decrypt(const wstring& cipher_text);
};
