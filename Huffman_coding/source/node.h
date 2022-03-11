#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <variant>
#include <memory>

class Node {
public:
    Node (std::weak_ptr<Node>, char);
    Node (std::shared_ptr<Node>, std::shared_ptr<Node>, std::weak_ptr<Node>);
    void add ();
    void recalculate ();
    void print (std::ostream &, int);
    int colorPrint (std::vector<std::shared_ptr<Node>>, int);

private:
    std::shared_ptr<Node> left, right;
    std::weak_ptr<Node> parent;
    std::variant<char, std::monostate> data;
    unsigned int weight;
    friend class Tree;

};

#endif //NODE_H
