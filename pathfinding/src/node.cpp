#include "node.h"

Node::Node (char name) : name_(name) {
    this->visit = false;
    this->weight_ = std::numeric_limits<double>::max();
}

char Node::name () const {
    return this->name_;
}

bool Node::addEdge (Node *node, double len) {
    if (len < 0)
        return false;
    if (node->name() == this->name())
        return true;
    this->edges_.emplace_back(node, len);
    return true;
}

std::vector<std::pair<Node *, double>> Node::edges () const {
    return this->edges_;
}

void Node::regularize () {
    std::sort(this->edges_.begin(), this->edges_.end(),
              [](std::pair<Node *, double> n1, std::pair<Node *, double> n2){
                  return n1.second == n2.second ? n1.first->name() < n2.first->name() : n1.second < n2.second;
    });
}

void Node::visited () {
    this->visit = true;
}

bool Node::isVisited () const {
    return this->visit;
}

void Node::updateWeight (double weight) {
    this->weight_ = weight;
}

double Node::weight () const {
    return this->weight_;
}

void Node::refresh () {
    this->visit = false;
    this->weight_ = std::numeric_limits<double>::max();
}

std::ostream &operator << (std::ostream &out, const Node *node) {
    out << node->name_ << ": ";
    for (auto &edge : node->edges_)
        out << edge.first->name() << "(" << edge.second << ") ";
    return out;
}