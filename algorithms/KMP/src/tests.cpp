#include <iostream>
#include <string>
#include <vector>
#include "catch.hpp"
#include "kmp.h"

TEST_CASE("kmp::prefixFunction() test") {
    std::cout << "Сhecking the prefix function...\n";
    std::string str = "abcdef";
    std::vector<int> vec = {0, 0, 0, 0, 0, 0};
    REQUIRE(kmp::prefixFunction(str) == vec);
    str = "abababab";
    vec = {0, 0, 1, 2, 3, 4, 5, 6};
    REQUIRE(kmp::prefixFunction(str) == vec);
    str = "aaaaa";
    vec = {0, 1, 2, 3, 4};
    REQUIRE(kmp::prefixFunction(str) == vec);
    str = "aabaabaaaabaabaaab";
    vec = {0, 1, 0, 1, 2, 3, 4, 5, 2, 2, 3, 4, 5, 6, 7, 8, 9, 3};
    REQUIRE(kmp::prefixFunction(str) == vec);
    std::cout << "\tCorrect\n";
}

TEST_CASE("kmp::kmpSearch() test") {
    std::cout << "Сhecking the finding a pattern in a string function...\n";
    std::string pattern = "a";
    std::string text = "aabaab";
    std::vector<int> vec = {0, 1, 3, 4};
    REQUIRE(kmp::kmpSearch(text, pattern) == vec);
    pattern = "abab";
    text = "ababababab";
    vec = {0, 2, 4, 6};
    REQUIRE(kmp::kmpSearch(text, pattern) == vec);
    pattern = "abc";
    text = "ababa";
    vec = {-1};
    REQUIRE(kmp::kmpSearch(text, pattern) == vec);
    std::cout << "\tCorrect\n";
}

TEST_CASE("kmp::convertVector() test") {
    std::cout << "Сhecking the vector to string conversion function...\n";
    std::vector<int> vec = {0, 1, 2, 3};
    REQUIRE(kmp::convertVector(vec) == "0, 1, 2, 3");
    vec = {0};
    REQUIRE(kmp::convertVector(vec) == "0");
    vec = {};
    REQUIRE(kmp::convertVector(vec) == "");
    std::cout << "\tCorrect\n";
}
