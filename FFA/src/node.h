#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

class Node;
using throughput = std::pair<unsigned int, unsigned int>;
using edge = std::tuple<Node *, throughput, bool>;

class Node {
public:
    Node (char);
    char name () const;
    void addEdge (Node *, unsigned int, bool fict = false);
    std::vector<edge> edges () const;
    bool isVisited () const;
    void visit (bool);
    void regularize ();
    void normalize ();
    bool reduceThroughput (edge, unsigned int);
    friend std::ostream &operator << (std::ostream &, const Node *);

#ifndef TEST
private:
#endif
    bool increaseThroughput (Node *, unsigned int);

private:
    char name_;
    std::vector<edge> edges_;
    bool visit_;

};

#endif