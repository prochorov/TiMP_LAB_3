#include <cstring>
#include <UnitTest++/UnitTest++.h>
#include "TableCipher.h"

SUITE(KeyTest) {
    
    TEST(ValidKey) {
        CHECK_EQUAL("LLEHO", Cipher("4").encrypt("HELLO"));
    }

    TEST(BigKey) {
        CHECK_EQUAL("OLLEH", Cipher("100").encrypt("HELLO"));
    }

    TEST(FloatKey) {
        CHECK_EQUAL("LLEHO", Cipher("4.20").encrypt("HELLO"));
    }
    
    TEST(LettersInKey) {
        CHECK_THROW(Cipher("4FOUR"), std::string);
    }
            
    TEST(NegativeKey) {
        CHECK_THROW(Cipher cp("-4"), cipher_error);
    }

    TEST(EmptyKey) {
        CHECK_THROW(Cipher cp(""), std::invalid_argument);
    }
    
    TEST(WeakKey) {
        CHECK_THROW(Cipher cp("0"), std::string);
    }
}

struct KeyB_fixture {
    Cipher * p;
    KeyB_fixture() {
        p = new Cipher("4");
    }
    ~KeyB_fixture() {
        delete p;
    }
};

SUITE(EncryptTest) {
    
    TEST_FIXTURE(KeyB_fixture, StringWithLetters) {
        CHECK_EQUAL("LLEHO", p -> encrypt("HELLO"));
    }
    
    TEST_FIXTURE(KeyB_fixture, StringWithSymbols) {
        CHECK_EQUAL("11EH0", p -> encrypt("HE110"));
    }
    
    TEST_FIXTURE(KeyB_fixture, StringWithWhitespaceAndSymbols) {
        CHECK_EQUAL("LO!LWDE LHOR", p -> encrypt("HELLO WORLD!"));
    }

    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p -> encrypt(""), std::string);
    }
}

SUITE(DecryptTest) {
    
    TEST_FIXTURE(KeyB_fixture, StringWithLetters) {
        CHECK_EQUAL("HELLO", p-> decrypt("LLEHO"));
    }
    
    TEST_FIXTURE(KeyB_fixture, StringWithSymbols) {
        CHECK_EQUAL("HE11O", p-> decrypt("11EHO"));
    }
    
    TEST_FIXTURE(KeyB_fixture, StringWithWhitespaceAndSymbols) {
        CHECK_EQUAL("HELLO WORLD!", p-> decrypt("LO!LWDE LHOR"));
    }
    
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p-> decrypt(""), std::string);
    }
}

int main(int argc, char** argv) {
    return UnitTest::RunAllTests();
}
