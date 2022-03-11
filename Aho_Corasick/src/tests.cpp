#include <iostream>
#include <string>
#include <vector>
#include "catch.hpp"
#include "node.h"
#include "bor.h"

TEST_CASE("Node::addDescendant() test") {
    std::cout << "Сhecking the adding descendants function...\n";
    Node nodeA('a', nullptr);
    Node nodeB('b', nullptr);
    Node nodeC('b', nullptr);
    REQUIRE(nodeA.addDescendant(&nodeB) == true);
    REQUIRE(nodeA.addDescendant(&nodeC) == false);
    REQUIRE(nodeA.addDescendant(&nodeB) == false);
    REQUIRE(nodeA.addDescendant(&nodeA) == false);
    std::cout << "\tCorrect\n";
}

TEST_CASE("Node::addTerminal() test") {
    std::cout << "Сhecking the adding terminals function...\n";
    Node node('a', nullptr);
    REQUIRE(node.addTerminal(0) == true);
    REQUIRE(node.addTerminal(1) == true);
    REQUIRE(node.addTerminal(1) == false);
    std::cout << "\tCorrect\n";
}

TEST_CASE("Bor::algorithmAhoCorasick() test") {
    std::cout << "Сhecking the Aho-Corasick algorithm...\n";
    std::vector<std::string> patterns = {"abc"};
    std::string text = "abccabc";
    std::vector<std::pair<int, int>> res;
    res.emplace_back(1, 1);
    res.emplace_back(5, 1);
    Bor b1(patterns);
    REQUIRE(b1.algorithmAhoCorasick(text, false) == res);
    patterns = {"ab", "bc", "abc"};
    text = "cabcabbca";
    res.clear();
    res.emplace_back(2, 1);
    res.emplace_back(2, 3);
    res.emplace_back(3, 2);
    res.emplace_back(5, 1);
    res.emplace_back(7, 2);
    Bor b2(patterns);
    REQUIRE(b2.algorithmAhoCorasick(text, false) == res);
    std::string pattern = "a*";
    text = "aaba";
    res.clear();
    res.emplace_back(1, 1);
    res.emplace_back(2, 1);
    Bor b3(pattern, '*');
    REQUIRE(b3.algorithmAhoCorasick(text, true) == res);
    std::cout << "\tCorrect\n";
}

TEST_CASE("Bor::maxEdges() test") {
    std::cout << "Сhecking the max number of edges outgoing from one node function...\n";
    std::string pattern = "a";
    Bor b1(pattern, ' ');
    REQUIRE(b1.maxEdges() == 2);
    pattern = "aab ab ac b";
    Bor b2(pattern, ' ');
    REQUIRE(b2.maxEdges() == 4);
    pattern = "";
    Bor b3(pattern, ' ');
    REQUIRE(b3.maxEdges() == 1);
    std::cout << "\tCorrect\n";
}

TEST_CASE("Bor::erasePattern() test") {
    std::cout << "Сhecking the erase patterns from string function...\n";
    std::vector<std::string> patterns = {"abc"};
    std::string text = "abc";
    Bor b1(patterns);
    REQUIRE(b1.erasePattern(text, patterns, false) == "");
    patterns = {"ab", "bc", "de"};
    text = "cabcabf";
    Bor b2(patterns);
    REQUIRE(b2.erasePattern(text, patterns, false) == "cf");
    std::cout << "\tCorrect\n";
}
