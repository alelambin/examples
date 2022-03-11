#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

class Node {
public:
    Node (char);
    char name () const;
    bool addEdge (Node *, double);
    std::vector<std::pair<Node *, double>> edges () const;
    void regularize ();
    void visited ();
    bool isVisited () const;
    void updateWeight (double);
    double weight () const;
    void refresh();
    friend std::ostream &operator << (std::ostream &, const Node *);

private:
    char name_;
    std::vector<std::pair<Node *, double>> edges_;
    bool visit;
    double weight_;

};

#endif