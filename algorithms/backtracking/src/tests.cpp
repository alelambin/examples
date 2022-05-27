#include <iostream>
#include "catch.hpp"
#include "backtracking.h"

TEST_CASE("bktg::isSquare() test") {
    std::cout << "Сhecking the verification square function...\n";
    matrix emptyTable = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    matrix filledTable = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    matrix partialTable = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 0, 1}
    };
    REQUIRE(bktg::isSquare(emptyTable, {1, 0}, {1, 0}) == 0);
    REQUIRE(bktg::isSquare(emptyTable, {0, 1}, {1, 2}) == 0);
    REQUIRE(bktg::isSquare(emptyTable, {0, 0}, {2, 2}) == 0);
    REQUIRE(bktg::isSquare(emptyTable, {-1, 0}, {2, 2}) == -1);
    REQUIRE(bktg::isSquare(emptyTable, {0, -1}, {2, 2}) == -1);
    REQUIRE(bktg::isSquare(emptyTable, {-1, -1}, {2, 2}) == -1);
    REQUIRE(bktg::isSquare(emptyTable, {0, 0}, {3, 2}) == -1);
    REQUIRE(bktg::isSquare(emptyTable, {0, 0}, {2, 3}) == -1);
    REQUIRE(bktg::isSquare(emptyTable, {0, 0}, {3, 3}) == -1);
    REQUIRE(bktg::isSquare(filledTable, {1, 0}, {1, 0}) == 1);
    REQUIRE(bktg::isSquare(filledTable, {0, 1}, {1, 2}) == 1);
    REQUIRE(bktg::isSquare(filledTable, {0, 0}, {2, 2}) == 1);
    REQUIRE(bktg::isSquare(filledTable, {-1, 0}, {2, 2}) == -1);
    REQUIRE(bktg::isSquare(filledTable, {0, -1}, {2, 2}) == -1);
    REQUIRE(bktg::isSquare(filledTable, {-1, -1}, {2, 2}) == -1);
    REQUIRE(bktg::isSquare(filledTable, {0, 0}, {3, 2}) == -1);
    REQUIRE(bktg::isSquare(filledTable, {0, 0}, {2, 3}) == -1);
    REQUIRE(bktg::isSquare(filledTable, {0, 0}, {3, 3}) == -1);
    REQUIRE(bktg::isSquare(partialTable, {0, 1}, {1, 2}) == -1);
    REQUIRE(bktg::isSquare(partialTable, {0, 0}, {2, 2}) == -1);
    REQUIRE(bktg::isSquare(partialTable, {-1, 0}, {2, 2}) == -1);
    REQUIRE(bktg::isSquare(partialTable, {0, -1}, {2, 2}) == -1);
    REQUIRE(bktg::isSquare(partialTable, {-1, -1}, {2, 2}) == -1);
    REQUIRE(bktg::isSquare(partialTable, {0, 0}, {3, 2}) == -1);
    REQUIRE(bktg::isSquare(partialTable, {0, 0}, {2, 3}) == -1);
    REQUIRE(bktg::isSquare(partialTable, {0, 0}, {3, 3}) == -1);
    std::cout << "\tCorrect\n";
}

TEST_CASE("bktg::addSquare() test") {
    std::cout << "Сhecking the add square function...\n";
    square s;
    matrix table = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    matrix correctTable = {
        {0, 0, 0},
        {1, 1, 0},
        {1, 1, 0}
    };
    s = std::make_pair(std::make_pair(0, 1), 2);
    REQUIRE(bktg::addSquare(s, table) == true);
    REQUIRE(table == correctTable);
    s = std::make_pair(std::make_pair(-1, 0), 1);
    REQUIRE(bktg::addSquare(s, table) == false);
    s = std::make_pair(std::make_pair(0, -1), 1);
    REQUIRE(bktg::addSquare(s, table) == false);
    s = std::make_pair(std::make_pair(-1, -1), 1);
    REQUIRE(bktg::addSquare(s, table) == false);
    s = std::make_pair(std::make_pair(3, 0), 1);
    REQUIRE(bktg::addSquare(s, table) == false);
    s = std::make_pair(std::make_pair(0, 3), 1);
    REQUIRE(bktg::addSquare(s, table) == false);
    s = std::make_pair(std::make_pair(3, 3), 1);
    REQUIRE(bktg::addSquare(s, table) == false);
    std::cout << "\tCorrect\n";
}

TEST_CASE("bktg::removeSquare() test") {
    std::cout << "Сhecking the remove square function...\n";
    square s;
    matrix table = {
        {0, 0, 0},
        {1, 1, 0},
        {1, 1, 0}
    };
    matrix correctTable = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    s = std::make_pair(std::make_pair(0, 1), 2);
    REQUIRE(bktg::removeSquare(s, table) == true);
    REQUIRE(table == correctTable);
    s = std::make_pair(std::make_pair(-1, 0), 1);
    REQUIRE(bktg::removeSquare(s, table) == false);
    s = std::make_pair(std::make_pair(0, -1), 1);
    REQUIRE(bktg::removeSquare(s, table) == false);
    s = std::make_pair(std::make_pair(-1, -1), 1);
    REQUIRE(bktg::removeSquare(s, table) == false);
    s = std::make_pair(std::make_pair(3, 0), 1);
    REQUIRE(bktg::removeSquare(s, table) == false);
    s = std::make_pair(std::make_pair(0, 3), 1);
    REQUIRE(bktg::removeSquare(s, table) == false);
    s = std::make_pair(std::make_pair(3, 3), 1);
    REQUIRE(bktg::removeSquare(s, table) == false);
    std::cout << "\tCorrect\n";
}

TEST_CASE("bktg::getMinSquares() test") {
    std::cout << "Сhecking the minimum squares search function...\n";
    int operationCounter = 0;
    REQUIRE(bktg::getMinSquares(0, operationCounter).size() == 0);
    REQUIRE(bktg::getMinSquares(1, operationCounter).size() == 0);
    REQUIRE(bktg::getMinSquares(2, operationCounter).size() == 4);
    REQUIRE(bktg::getMinSquares(3, operationCounter).size() == 6);
    REQUIRE(bktg::getMinSquares(5, operationCounter).size() == 8);
    REQUIRE(bktg::getMinSquares(7, operationCounter).size() == 9);
    REQUIRE(bktg::getMinSquares(9, operationCounter).size() == 6);
    REQUIRE(bktg::getMinSquares(11, operationCounter).size() == 11);
    REQUIRE(bktg::getMinSquares(13, operationCounter).size() == 11);
    REQUIRE(bktg::getMinSquares(15, operationCounter).size() == 6);
    REQUIRE(bktg::getMinSquares(17, operationCounter).size() == 12);
    std::cout << "\tCorrect\n";
}
