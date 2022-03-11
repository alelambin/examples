#include "node.h"

Node::Node (char name) : name_(name) {
    this->visit_ = false;
}

char Node::name () const {
    return this->name_;
}

void Node::addEdge (Node *node, unsigned int weight, bool fict/* = false*/)  {
    for (auto &edge : this->edges_)
        if (std::get<Node *>(edge)->name() == node->name() && std::get<bool>(edge) == fict) {
            std::get<throughput>(edge).second += weight;
            return;
        }
    this->edges_.emplace_back(node, std::make_pair(0, weight), fict);
}

std::vector<edge> Node::edges () const {
    return this->edges_;
}

bool Node::isVisited () const {
    return this->visit_;
}

void Node::visit (bool v) {
    this->visit_ = v;
}

void Node::regularize () {
    std::sort(this->edges_.begin(), this->edges_.end(),
        [](edge edge1, edge edge2){
            if (std::get<Node *>(edge1)->name() == std::get<Node *>(edge2)->name())
                return std::get<bool>(edge1);
            else
                return std::get<Node *>(edge1)->name() < std::get<Node *>(edge2)->name();
        });
}

void Node::normalize () {
    std::sort(this->edges_.begin(), this->edges_.end(),
        [](edge edge1, edge edge2){
            return std::get<Node *>(edge1)->name() < std::get<Node *>(edge2)->name();
        });
}

bool Node::reduceThroughput (edge curEdge, unsigned int flow) {
    if (std::get<throughput>(curEdge).second - std::get<throughput>(curEdge).first < flow)
        return false;

    if (std::get<bool>(curEdge)) {
        for (auto &edge : this->edges_)
            if (std::get<Node *>(edge)->name() == std::get<Node *>(curEdge)->name() && std::get<bool>(edge) == std::get<bool>(curEdge)) {
                std::get<throughput>(edge).second -= flow;
                break;
            }
        if (std::get<Node *>(curEdge)->increaseThroughput(this, flow))
            return true;
        for (auto &edge : this->edges_)
            if (std::get<Node *>(edge)->name() == std::get<Node *>(curEdge)->name() && std::get<bool>(edge) == std::get<bool>(curEdge)) {
                std::get<throughput>(edge).second += flow;
                break;
            }
        return false;
    } else {
        for (auto &edge : this->edges_)
            if (std::get<Node *>(edge)->name() == std::get<Node *>(curEdge)->name() && std::get<bool>(edge) == std::get<bool>(curEdge)) {
                std::get<throughput>(edge).first += flow;
                std::get<Node *>(curEdge)->addEdge(this, flow, true);
                return true;
            }
        return false;
    }
}

std::ostream &operator << (std::ostream &out, const Node *node) {
    for (auto &edge : node->edges_)
        if (!std::get<bool>(edge))
            out << node->name() << ' ' << std::get<Node *>(edge)->name() << ' ' << std::get<throughput>(edge).first << '\n';
    return out;
}

bool Node::increaseThroughput (Node *node, unsigned int flow) {
    for (auto &edge : this->edges_)
        if (std::get<Node *>(edge)->name() == node->name() && !std::get<bool>(edge)) {
            std::get<throughput>(edge).first -= flow;
            return true;
        }
    return false;
}
