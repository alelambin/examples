#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <tuple>
#include <limits>
#include <algorithm>
#include "node.h"

class Graph {
public:
    Graph () = default;
    ~Graph ();
    bool isContain (char);
    bool addNode (char);
    void addEdge (char, char, int, bool fict = false);
    unsigned int FordFulkerson (char, char);
    friend std::ostream &operator << (std::ostream &, const Graph &);

#ifndef TEST
private:
#endif
    bool depthSearch (Node *, char, std::vector<std::pair<Node *, edge>> &);
    void normalize ();
    Node *getNode (char);

private:
    std::vector<Node *> nodes;

};

#endif