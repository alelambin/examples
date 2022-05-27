#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <getopt.h>
#include "node.h"

class Graph {
public:
    Graph () = default;
    ~Graph ();
    bool isContain (char);
    bool addNode (char);
    bool addEdge (char, char, double);
    void regularize ();
    std::string greedySearch (char, char);
    std::string astarSearch (char, char);
    std::string astarSearch (char, char, char);
    void refresh ();
    friend std::ostream &operator << (std::ostream &, const Graph &);

private:
    std::vector<Node *> nodes;

};

#endif