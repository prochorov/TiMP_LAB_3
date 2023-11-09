#include "modAlphaCipher.h"

modAlphaCipher::modAlphaCipher(const std::wstring &skey)
{
    for (unsigned i = 0; i < numAlpha.size(); i++)
    {
        alphaNum[numAlpha[i]] = i;
    }
    key = convert(getValidKey(skey));
}

std::wstring modAlphaCipher::encrypt(const std::wstring &open_text)
{
    std::vector<int> work = convert(getValidOpenText(open_text));
    for (unsigned i = 0; i < work.size(); i++)
    {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

std::wstring modAlphaCipher::decrypt(const std::wstring &cipher_text)
{
    std::vector<int> work = convert(getValidCipherText(cipher_text));
    for (unsigned i = 0; i < work.size(); i++)
    {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

inline std::vector<int> modAlphaCipher::convert(const std::wstring &s)
{
    std::vector<int> result;
    for (auto c : s)
    {
        result.push_back(alphaNum[c]);
    }
    return result;
}

inline std::wstring modAlphaCipher::convert(const std::vector<int> &v)
{
    std::wstring result;
    for (auto i : v)
    {
        result.push_back(numAlpha[i]);
    }
    return result;
}

inline std::wstring modAlphaCipher::getValidKey(const std::wstring &s)
{
    if (s.empty())
        throw cipher_error("Empty key");
    std::wstring tmp(s);
    for (wchar_t &wc : tmp)
    {
        if (!((wc > 1039 and wc < 1104) or wc == 1025 or wc == 1105))
            throw cipher_error(std::string("Invalid key "));
        if (wc > 1071 and wc < 1104)
            wc = wc - 32;
        else if (wc == 1105)
            wc = wc - 80;
    }
    return tmp;
}

inline std::wstring modAlphaCipher::getValidOpenText(const std::wstring &s)
{
    std::wstring tmp;
    for (auto wc : s)
    {
        if ((wc > 1039 and wc < 1104) or wc == 1025 or wc == 1105)
        {
            if (wc > 1071 and wc < 1104)
                tmp.push_back(wc - 32);
            else if (wc == 1105)
                tmp.push_back(wc - 80);
            else
                tmp.push_back(wc);
        }
    }
    if (tmp.empty())
        throw cipher_error("Empty open text");
    return tmp;
}

inline std::wstring modAlphaCipher::getValidCipherText(const std::wstring &s)
{
    if (s.empty())
        throw cipher_error("Empty cipher text");
    for (auto c : s)
    {
        if ((c > 1071 and c < 1104) or c == 1105)
            throw cipher_error(std::string("Invalid cipher text "));
    }
    return s;
}
