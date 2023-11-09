#include <UnitTest++/UnitTest++.h>
#include "modAlphaCipher.h"
#include <string>
#include <locale>
#include <codecvt>

SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK_EQUAL(L"БВГБВ", modAlphaCipher(L"БВГ").encrypt(L"ААААА").c_str());
    }

    TEST(LongKey) {
        CHECK_EQUAL(L"БВГДЕ", modAlphaCipher(L"БВГДЕЁЖЗ").encrypt(L"ААААА").c_str());
    }

    TEST(LowCaseKey) {
        CHECK_EQUAL(L"БВГБВ", modAlphaCipher(L"бвг").encrypt(L"ААААА").c_str());
    }

    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher(L"Б1В"), cipher_error);
    }

    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher(L"Б,В"), cipher_error);
    }

    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher(L"Б В"), cipher_error);
    }

    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher(L""), cipher_error);
    }

    TEST(WeakKey) {
        CHECK_THROW(modAlphaCipher(L"ААААА"), cipher_error);
    }
}

struct KeyB_fixture {
    modAlphaCipher * p;
    KeyB_fixture()
    {
        p = new modAlphaCipher(L"Б");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL(L"ВБВБЕФЛ", modAlphaCipher(L"Б").encrypt(L"ААААААААА").c_str());
    }

    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL(L"ВБВБЕФЛ", modAlphaCipher(L"Б").encrypt(L"ааааааааа").c_str());
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        CHECK_EQUAL(L"ВБВБЕФЛ", modAlphaCipher(L"Б").encrypt(L"ААААА АААА АААА!!!!!!").c_str());
    }

    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        CHECK_EQUAL(L"ТОПГЬНДПЕПН", modAlphaCipher(L"Б").encrypt(L"С новым 2022годом").c_str());
    }

    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(L""), cipher_error);
    }

    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt(L"1234+8765=9999"), cipher_error);
    }

    TEST(MaxShiftKey) {
        CHECK_EQUAL(L"АЯАЯГТЙ", modAlphaCipher(L"Я").encrypt(L"БАБАДУК").c_str());
    }
}

SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL(L"ААААААААА", p->decrypt(L"ВБВБЕФЛ").c_str());
    }

    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt(L"ВБВБЕФЛ"), cipher_error);
    }

    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt(L"ВБВБЕФЛ"), cipher_error);
    }

    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->decrypt(L"ТОПГЬН2022ДПЕПН"), cipher_error);
    }

    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p->decrypt(L"РСЙГЁУ,НЙС"), cipher_error);
    }

    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(L""), cipher_error);
    }

    TEST(MaxShiftKey) {
        CHECK_EQUAL(L"БАБАДУК", modAlphaCipher(L"Я").decrypt(L"АЯАЯГТЙ").c_str());
    }
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
