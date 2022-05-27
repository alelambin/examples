#include <iostream>
#include "catch.hpp"
#include "node.h"
#include "graph.h"

TEST_CASE ("Node::addEdge() test") {
    std::cout << "Сhecking the add edge function...\n";
    Node a('a');
    Node b('b');
    Node c('c');
    Node d('d');
    REQUIRE(a.addEdge(&b, 5) == true);
    REQUIRE(a.addEdge(&c, 0) == true);
    REQUIRE(a.addEdge(&a, 5) == true);
    REQUIRE(a.addEdge(&a, 0) == true);
    REQUIRE(b.addEdge(&b, 0) == true);
    REQUIRE(a.addEdge(&d, -5) == false);
    REQUIRE(a.addEdge(&a, -5) == false);
    for (auto &edge : a.edges())
        REQUIRE(edge.second >= 0);
    std::cout << "\tCorrect\n";
}

TEST_CASE ("Graph::addNode() test") {
    std::cout << "Сhecking the add node function...\n";
    Graph G;
    REQUIRE(G.addNode('a') == true);
    REQUIRE(G.addNode('b') == true);
    REQUIRE(G.addNode('a') == false);
    std::cout << "\tCorrect\n";
}

TEST_CASE ("Graph::addEdge() test") {
    std::cout << "Сhecking the add edge function...\n";
    Graph G;
    G.addNode('a');
    G.addNode('b');
    G.addNode('c');
    G.addNode('d');
    REQUIRE(G.addEdge('a', 'b', 5) == true);
    REQUIRE(G.addEdge('a', 'c', 0) == true);
    REQUIRE(G.addEdge('a', 'a', 5) == true);
    REQUIRE(G.addEdge('a', 'a', 0) == true);
    REQUIRE(G.addEdge('a', 'd', -5) == false);
    REQUIRE(G.addEdge('a', 'a', -5) == false);
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

TEST_CASE ("Graph::greedySearch() and Graph::astarSearch() test") {
    Graph G;
    SECTION ("G1") {
        std::cout << "Сhecking the greedy and A* search functions...\n";
        G.addNode('a');
        G.addNode('b');
        G.addNode('c');
        G.addNode('d');
        G.addEdge('a', 'b', 1);
        G.addEdge('a', 'c', 2);
        G.addEdge('a', 'd', 4);
        G.addEdge('b', 'd', 2);
        G.addEdge('c', 'd', 3);
        REQUIRE(G.greedySearch('a', 'd') == "abd");
        G.refresh();
        REQUIRE(G.astarSearch('a', 'd') == "abd");
        G.refresh();
        REQUIRE(G.astarSearch('a', 'c') == "ac");
        G.refresh();
        REQUIRE(G.astarSearch('a', 'c', 'd') == "ac");
    }
    SECTION ("G2") {
        G.addNode('a');
        G.addNode('b');
        G.addNode('c');
        G.addNode('d');
        G.addNode('e');
        G.addNode('f');
        G.addNode('g');
        G.addNode('h');
        G.addNode('i');
        G.addNode('j');
        G.addNode('k');
        G.addNode('l');
        G.addNode('m');
        G.addNode('n');
        G.addEdge('a', 'b', 1);
        G.addEdge('a', 'c', 2);
        G.addEdge('a', 'd', 3);
        G.addEdge('b', 'e', 4);
        G.addEdge('b', 'f', 1);
        G.addEdge('c', 'g', 2);
        G.addEdge('d', 'h', 3);
        G.addEdge('d', 'i', 2);
        G.addEdge('d', 'j', 1);
        G.addEdge('e', 'k', 5);
        G.addEdge('e', 'l', 1);
        G.addEdge('h', 'm', 3);
        G.addEdge('h', 'n', 1);
        REQUIRE(G.greedySearch('a', 'n') == "adhn");
        G.refresh();
        REQUIRE(G.astarSearch('a', 'n') == "adhn");
        G.refresh();
        REQUIRE(G.astarSearch('a', 'l') == "abel");
        G.refresh();
        REQUIRE(G.astarSearch('a', 'l', 'n') == "adhn");
    }
    SECTION ("G3") {
        G.addNode('a');
        G.addNode('b');
        G.addNode('x');
        G.addNode('y');
        G.addNode('z');
        G.addEdge('a', 'b', 1);
        G.addEdge('a', 'x', 10);
        G.addEdge('b', 'y', 1);
        G.addEdge('x', 'y', 1);
        G.addEdge('y', 'z', 20);
        REQUIRE(G.greedySearch('a', 'z') == "abyz");
        G.refresh();
        REQUIRE(G.astarSearch('a', 'z') == "abyz");
        G.refresh();
        REQUIRE(G.astarSearch('a', 'y') == "axy");
        G.refresh();
        REQUIRE(G.astarSearch('a', 'y', 'z') == "axy");
    }
    SECTION ("G4") {
        G.addNode('a');
        G.addNode('b');
        G.addNode('c');
        G.addNode('d');
        G.addNode('e');
        G.addNode('f');
        G.addNode('g');
        G.addNode('h');
        G.addEdge('c', 'b', 1);
        G.addEdge('c', 'g', 4);
        G.addEdge('d', 'b', 1);
        G.addEdge('d', 'f', 7);
        G.addEdge('d', 'g', 1);
        G.addEdge('g', 'e', 3);
        G.addEdge('e', 'e', 1);
        REQUIRE(G.astarSearch('a', 'c') == "");
        G.refresh();
        REQUIRE(G.astarSearch('c', 'h') == "");
        G.refresh();
        REQUIRE(G.astarSearch('a', 'h') == "");
        G.refresh();
        REQUIRE(G.astarSearch('b', 'c') == "");
        G.refresh();
        REQUIRE(G.astarSearch('c', 'f') == "");
        G.refresh();
        REQUIRE(G.astarSearch('a', 'a') == "a");
        G.refresh();
        REQUIRE(G.astarSearch('c', 'c') == "c");
        G.refresh();
        REQUIRE(G.astarSearch('e', 'e') == "e");
        std::cout << "\tCorrect\n";
    }
}
