#include "graph.h"

Graph::~Graph () {
    for (auto &node : this->nodes)
        delete node;
}

bool Graph::isContain (char name) {
    for (auto &node : this->nodes)
        if (node->name() == name)
            return true;
    return false;
}

bool Graph::addNode (char name) {
    if (!this->isContain(name))
        this->nodes.push_back(new Node(name));
    else
        return false;
    return true;
}

void Graph::addEdge (char nodeName1, char nodeName2, int weight, bool fict/* = false*/) {
    if (nodeName1 == nodeName2)
        return;
    Node *node1, *node2;
    for (auto &node : this->nodes) {
        if (node->name() == nodeName1)
            node1 = node;
        if (node->name() == nodeName2)
            node2 = node;
    }
    node1->addEdge(node2, weight, fict);
}

unsigned int Graph::FordFulkerson (char sourceName, char destinationName) {
    Node *source = nullptr, *destination = nullptr;
    for (auto &node : this->nodes) {
        if (node->name() == sourceName)
            source = node;
        if (node->name() == destinationName)
            destination = node;
    }
    if (source == nullptr)
        throw "Source name does not exist";
    if (destination == nullptr)
        throw "Destination name does not exist";
    std::vector<std::pair<Node *, edge>> path;
    while (depthSearch(source, destinationName, path)) {
        unsigned int curFlow = std::numeric_limits<unsigned int>::max();
        for (auto &obj : path)
            if (std::get<throughput>(obj.second).second - std::get<throughput>(obj.second).first < curFlow)
                curFlow = std::get<throughput>(obj.second).second - std::get<throughput>(obj.second).first;
        for (auto &obj : path)
            obj.first->reduceThroughput(obj.second, curFlow);
        path.clear();
    }
    int maxFlow = 0;
    for (auto &edge : source->edges())
        maxFlow += std::get<throughput>(edge).first;
    this->normalize();
    return maxFlow;
}

std::ostream &operator << (std::ostream &out, const Graph &graph) {
    for (auto &node : graph.nodes)
        out << node;
    return out;
}

bool Graph::depthSearch (Node *cur, char destinationName, std::vector<std::pair<Node *, edge>> &path) {
    if (cur->name() == destinationName)
        return true;
    cur->regularize();
    cur->visit(true);
    for (auto &edge : cur->edges())
        if (!std::get<Node *>(edge)->isVisited() && std::get<throughput>(edge).second != std::get<throughput>(edge).first) {
            if (depthSearch(std::get<Node *>(edge), destinationName, path)) {
                path.emplace_back(cur, edge);
                cur->visit(false);
                return true;
            }
        }
    cur->visit(false);
    return false;
}

void Graph::normalize () {
    for (auto &node : this->nodes)
        node->normalize();
    std::sort(this->nodes.begin(), this->nodes.end(),
        [](Node *node1, Node *node2){
            return node1->name() < node2->name();
        });
}

Node *Graph::getNode (char name) {
    for (auto &node : this->nodes)
        if (node->name() == name) 
            return node;
    return nullptr;
}
