#define CATCH_CONFIG_MAIN

#include "../Catch2/catch_amalgamated.cpp"
#include "../implementation/interface.h"

TEST_CASE("comparing 2 files"){
    std::ifstream a("/home/dahudohu/Programming!/University/DSA_THIRD_HOMEWORK/tests/2Texts/text1.txt", std::ifstream::in);
    std::ifstream b("/home/dahudohu/Programming!/University/DSA_THIRD_HOMEWORK/tests/2Texts/text2.txt", std::ifstream::in);

    Comparator c;
    ComparisonReport report = c.compare(a, b);

    REQUIRE(report.commonWords.countOfUniqueWords() == 161);
    REQUIRE(report.commonWords.getSize() == 335);
    REQUIRE(report.uniqueWords[0].countOfUniqueWords() == 311);
    REQUIRE(report.uniqueWords[0].getSize() == 411);
    REQUIRE(report.uniqueWords[1].countOfUniqueWords() == 293);
    REQUIRE(report.uniqueWords[1].getSize() == 348);

}

TEST_CASE("comparing the same file"){
    std::ifstream a("/home/dahudohu/Programming!/University/DSA_THIRD_HOMEWORK/tests/2Texts/text1.txt", std::ifstream::in);
    std::ifstream b("/home/dahudohu/Programming!/University/DSA_THIRD_HOMEWORK/tests/2Texts/text1.txt", std::ifstream::in);

    Comparator c;
    ComparisonReport report = c.compare(a, b);

    REQUIRE(report.commonWords.countOfUniqueWords() == 415);
    REQUIRE(report.commonWords.getSize() == 746);
    REQUIRE(report.uniqueWords[0].countOfUniqueWords() == 0);
    REQUIRE(report.uniqueWords[1].countOfUniqueWords() == 0);
}


TEST_CASE("comparing large files"){
    std::ifstream a("/home/dahudohu/Programming!/University/DSA_THIRD_HOMEWORK/tests/2Texts/large1.txt", std::ifstream::in);
    std::ifstream b("/home/dahudohu/Programming!/University/DSA_THIRD_HOMEWORK/tests/2Texts/large2.txt", std::ifstream::in);

    Comparator c;
    ComparisonReport report = c.compare(a, b);

    REQUIRE(report.commonWords.countOfUniqueWords() == 121);
    REQUIRE(report.commonWords.getSize() == 451210);
    REQUIRE(report.uniqueWords[0].countOfUniqueWords() == 1195);
    REQUIRE(report.uniqueWords[0].getSize() == 865430);
    REQUIRE(report.uniqueWords[1].countOfUniqueWords() == 225);
    REQUIRE(report.uniqueWords[1].getSize() == 1202540);
}


TEST_CASE("Comparator works correctly for the streams [one two three four two one] and [two one four one one]") {
    std::stringstream a("one\ntwo\rthree\t\r\n\t\tfour two one");
    std::stringstream b("two one four one one");

    Comparator c;
    ComparisonReport report = c.compare(a, b);

     REQUIRE(report.commonWords.countOfUniqueWords() == 3);
     REQUIRE(report.commonWords.getSize() == 4);
     REQUIRE(report.uniqueWords[0].countOfUniqueWords() == 2);
     REQUIRE(report.uniqueWords[0].getSize() == 2);
     REQUIRE(report.uniqueWords[1].countOfUniqueWords() == 1);
     REQUIRE(report.uniqueWords[1].getSize() == 1);
}