#include <UnitTest++/UnitTest++.h>
#include "modAlphaCipher.h"
#include <string>


SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK_EQUAL("БВГБВ",modAlphaCipher("БВГ").encrypt("ААААА"));
    }

    TEST(LongKey) {
        CHECK_EQUAL("БВГДЕ",modAlphaCipher("БВГДЕЁЖЗ").encrypt("ААААА"));
    }

    TEST(LowCaseKey) {        
        CHECK_EQUAL("БВГБВ",modAlphaCipher("бвг").encrypt("ААААА")); 
    }
        
    TEST(DigitsInKey) {        
        CHECK_THROW(modAlphaCipher cp("Б1В"),cipher_error); 
    }
    
    TEST(PunctuationInKey) {        
        CHECK_THROW(modAlphaCipher cp("Б,В"),cipher_error); 
    }
    
    TEST(WhitespaceInKey) {        
        CHECK_THROW(modAlphaCipher cp("Б В"),cipher_error);
    }
    
    TEST(EmptyKey) {        
        CHECK_THROW(modAlphaCipher cp(""),cipher_error);
    }
    
    TEST(WeakKey) {        
        CHECK_THROW(modAlphaCipher cp("ААААА"),cipher_error);
    }
}

struct KeyB_fixture {
    modAlphaCipher * p;
    KeyB_fixture()
    {
        p = new modAlphaCipher("Б");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("ХМЁДНБУЙШОБАЮУБГЁСВМЯЕЙЧБЗФЁУФРПЕЫЁИЕБИБТЬЦБЯЪЙКДПСЭЛЙКЩЙРПГОЙЛ", p->encrypt("ФЛЕГМАТИЧНАЯЭТАВЕРБЛЮДИЦАЖУЕТУПОДЪЕЗДАЗАСЫХАЮЩИЙГОРЬКИЙШИПОВНИК"));
    }
    
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("ХМЁДНБУЙШОБАЮУБГЁСВМЯЕЙЧБЗФЁУФРПЕЫЁИЕБИБТЬЦБЯЪЙКДПСЭЛЙКЩЙРПГОЙЛ", p->encrypt("флегматичнаяэтаверблюдицажуетуподъездазасыхающийгорькийшиповник"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("ХМЁДНБУЙШОБАЮУБГЁСВМЯЕЙЧБЗФЁУФРПЕЫЁИЕБИБТЬЦБЯЪЙКДПСЭЛЙКЩЙРПГОЙЛ", p->encrypt("ФЛЕГМАТИЧНАЯ ЭТА ВЕРБЛЮДИЦА ЖУЕТ У ПОДЪЕЗДА ЗАСЫХАЮЩИЙ ГОРЬКИЙ ШИПОВНИК!!!"));
    }
    
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        CHECK_EQUAL("ТОПГЬНДПЕПН", p->encrypt("С новым 2022годом"));
    }
    
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(""),cipher_error);
    }
    
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt("1234+8765=9999"),cipher_error);
    }
    
    TEST(MaxShiftKey) {
        CHECK_EQUAL("УКДВЛЯСЗЦМЯЮЬСЯБДПАКЭГЗХЯЁТДСТОНГЩДЖГЯЖЯРЪФЯЭШЗИВНПЫЙЗИЧЗОНБМЗЙ", modAlphaCipher("Я").encrypt("ФЛЕГМАТИЧНАЯЭТАВЕРБЛЮДИЦАЖУЕТУПОДЪЕЗДАЗАСЫХАЮЩИЙГОРЬКИЙШИПОВНИК"));
    }
}

SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("ФЛЕГМАТИЧНАЯЭТАВЕРБЛЮДИЦАЖУЕТУПОДЪЕЗДАЗАСЫХАЮЩИЙГОРЬКИЙШИПОВНИК", p->decrypt("ХМЁДНБУЙШОБАЮУБГЁСВМЯЕЙЧБЗФЁУФРПЕЫЁИЕБИБТЬЦБЯЪЙКДПСЭЛЙКЩЙРПГОЙЛ"));
    }
    
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt("ХмёднбуйшОБАЮУБГЁСВМЯЕЙЧБЗФЁУФРПЕЫЁИЕБИБТЬЦБЯЪЙКДПСЭЛЙКЩЙРПГОЙЛ"),cipher_error);
    }
    
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt("ХМЁДНБУЙШОБА ЮУБ ГЁСВМЯЕЙЧБ ЗФЁУ ФРПЕЫЁИЕБ ИБТЬЦБЯЪЙК ДПСЭЛЙКЩЙР ПГОЙЛ"),cipher_error);
    }
    
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->decrypt("ТОПГЬН2022ДПЕПН"),cipher_error);
    }
    
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p->decrypt("РСЙГЁУ,НЙС"),cipher_error);
    }
    
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(""),cipher_error);
    }
    
    TEST(MaxShiftKey) {
        CHECK_EQUAL("ФЛЕГМАТИЧНАЯЭТАВЕРБЛЮДИЦАЖУЕТУПОДЪЕЗДАЗАСЫХАЮЩИЙГОРЬКИЙШИПОВНИК",modAlphaCipher("Я").decrypt("УКДВЛЯСЗЦМЯЮЬСЯБДПАКЭГЗХЯЁТДСТОНГЩДЖГЯЖЯРЪФЯЭШЗИВНПЫЙЗИЧЗОНБМЗЙ"));
    }
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
