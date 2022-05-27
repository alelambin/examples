#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

class Node {
public:
    Node (char, Node *);
    char name () const;
    std::vector<Node *> descendants () const;
    Node *getDescendant (char) const;
    bool addDescendant (Node *);
    void deleteDescendants ();
    bool addTerminal (int);
    std::vector<int> terminals () const;
    void addSuffixLink ();
    Node *suffixLink () const;
    Node *endLink () const;

private:
    char name_;
    std::vector<Node *> descendants_;
    Node *ancestor;
    Node *suffixLink_;
    Node *endLink_;
    std::vector<int> terminals_;

};

#endif
