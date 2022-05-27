#define TEST

#include <iostream>
#include "catch.hpp"
#include "node.h"
#include "graph.h"

TEST_CASE ("Node::reduceThroughput() test") {
    std::cout << "Сhecking the edge capacity reduction function...\n";
    Node a('a');
    Node b('b');
    Node c('c');
    Node d('d');
    a.addEdge(&b, 5);
    a.addEdge(&c, 10);
    a.addEdge(&d, 15);
    auto edges = a.edges();
    REQUIRE(a.reduceThroughput(edges[0], 5) == true);
    REQUIRE(a.reduceThroughput(edges[1], 5) == true);
    REQUIRE(a.reduceThroughput(edges[2], 20) == false);
    REQUIRE(a.reduceThroughput(std::make_tuple(&a, std::make_pair(0, 10), false), 1) == false);
    REQUIRE(b.reduceThroughput(edges[0], 5) == false);
    std::cout << "\tCorrect\n";
}

TEST_CASE ("Node::increaseThroughput() test") {
    std::cout << "Сhecking the edge capacity increasing function...\n";
    Node a('a');
    Node b('b');
    Node c('c');
    Node d('d');
    a.addEdge(&b, 5);
    a.addEdge(&c, 10);
    auto edges = a.edges();
    REQUIRE(a.increaseThroughput(&b, 5) == true);
    REQUIRE(a.increaseThroughput(&c, 10) == true);
    REQUIRE(a.increaseThroughput(&d, 0) == false);
    std::cout << "\tCorrect\n";
}

TEST_CASE ("Graph::isContain() test") {
    std::cout << "Сhecking the presence of the node in the graph function...\n";
    Graph G;
    G.addNode('a');
    REQUIRE(G.isContain('a') == true);
    REQUIRE(G.isContain('b') == false);
    std::cout << "\tCorrect\n";
}

TEST_CASE ("Graph::depthSearch() test") {
    std::cout << "Сhecking the depth-first search function...\n";
    Graph G;
    std::vector<std::pair<Node *, edge>> path;
    G.addNode('a');
    auto a = G.getNode('a');
    REQUIRE(G.depthSearch(a, 'a', path) == true);
    G.addNode('b');
    auto b = G.getNode('b');
    REQUIRE(G.depthSearch(a, 'b', path) == false);
    b->addEdge(a, 1);
    REQUIRE(G.depthSearch(a, 'b', path) == false);
    a->addEdge(b, 1);
    REQUIRE(G.depthSearch(a, 'b', path) == true);
    std::cout << "\tCorrect\n";
}

TEST_CASE ("Graph::FordFulkerson() test") {
    Graph G;
    SECTION ("G1") {
        std::cout << "Сhecking the finding the maximum flow in the graph function...\n";
        G.addNode('a');
        G.addNode('b');
        G.addNode('c');
        G.addNode('d');
        G.addNode('e');
        G.addNode('f');
        G.addEdge('a', 'b', 7);
        G.addEdge('a', 'c', 6);
        G.addEdge('b', 'd', 6);
        G.addEdge('c', 'f', 9);
        G.addEdge('d', 'e', 3);
        G.addEdge('d', 'f', 4);
        G.addEdge('e', 'c', 2);
        REQUIRE(G.FordFulkerson('a', 'f') == 12);
    }
    SECTION ("G2") {
        G.addNode('a');
        G.addNode('b');
        G.addNode('c');
        G.addNode('d');
        G.addNode('e');
        G.addEdge('a', 'b', 2);
        G.addEdge('a', 'c', 3);
        G.addEdge('a', 'd', 1);
        G.addEdge('b', 'c', 4);
        G.addEdge('b', 'e', 3);
        G.addEdge('c', 'b', 4);
        G.addEdge('c', 'd', 1);
        G.addEdge('c', 'e', 2);
        G.addEdge('d', 'c', 1);
        G.addEdge('d', 'e', 1);
        REQUIRE(G.FordFulkerson('a', 'e') == 6);
    }
    SECTION ("G3") {
        G.addNode('a');
        G.addNode('b');
        G.addNode('c');
        G.addNode('d');
        G.addEdge('a', 'b', 10);
        G.addEdge('a', 'c', 10);
        G.addEdge('b', 'c', 1);
        G.addEdge('b', 'd', 10);
        G.addEdge('c', 'd', 10);
        REQUIRE(G.FordFulkerson('a', 'd') == 20);
    }
    SECTION ("G4") {
        G.addNode('a');
        G.addNode('b');
        G.addNode('c');
        G.addNode('d');
        G.addNode('e');
        G.addNode('f');
        G.addEdge('a', 'b', 1);
        G.addEdge('a', 'c', 2);
        G.addEdge('b', 'c', 3);
        G.addEdge('d', 'e', 1);
        G.addEdge('d', 'f', 2);
        G.addEdge('e', 'f', 3);
        REQUIRE(G.FordFulkerson('a', 'f') == 0);
    }
    SECTION ("G5") {
        G.addNode('a');
        G.addNode('b');
        G.addNode('c');
        G.addEdge('a', 'b', 1);
        G.addEdge('a', 'c', 2);
        G.addEdge('b', 'c', 3);
        try {
            G.FordFulkerson('a', 'f');
            REQUIRE(false);
        } catch (...) {
            REQUIRE(true);
        }
    }
    SECTION ("G6") {
        G.addNode('d');
        G.addNode('e');
        G.addNode('f');
        G.addEdge('d', 'e', 1);
        G.addEdge('d', 'f', 2);
        G.addEdge('e', 'f', 3);
        try {
            G.FordFulkerson('a', 'f');
            REQUIRE(false);
        } catch (...) {
            REQUIRE(true);
        }
        std::cout << "\tCorrect\n";
    }
}
