#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <memory>
#include <cmath>
#include "node.h"

class Tree {
public:
    Tree ();
    std::pair<std::shared_ptr<Node>, std::string> find (char);
    std::pair<std::shared_ptr<Node>, char> find (std::string &);
    std::shared_ptr<Node> insert (char);
    friend std::ostream &operator<< (std::ostream &, const Tree &);
    static void removeSpaces (std::string &);
    static void changeRadix (std::string &, int);
    static std::string encode (std::string &, bool);
    static std::string decode (std::string &, bool);

private:
    std::pair<std::shared_ptr<Node>, std::string> recursionFind (std::shared_ptr<Node>, char, std::string);
    std::pair<std::shared_ptr<Node>, char> recursionFind (std::shared_ptr<Node>, std::string &);
    std::vector<std::shared_ptr<Node>> normalize ();

    std::shared_ptr<Node> root;
    std::vector<std::shared_ptr<Node>> nodeArray;

};

#endif //TREE_H
