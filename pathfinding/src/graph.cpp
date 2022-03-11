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

bool Graph::addEdge (char nodeName1, char nodeName2, double len) {
    if (len < 0)
        return false;
    if (nodeName1 == nodeName2) 
        return true;
    Node *node1, *node2;
    for (auto &node : this->nodes) {
        if (node->name() == nodeName1)
            node1 = node;
        if (node->name() == nodeName2)
            node2 = node;
    }
    if (node1->addEdge(node2, len)) {
        return true;
    } else {
        return false;
    }
}

void Graph::regularize () {
    for (auto &node : this->nodes)
        node->regularize();
}

std::string Graph::greedySearch (char startName, char finishName) {
    std::string result = "";
    result += startName;
    if (startName == finishName)
        return result;
    Node *start = nullptr, *finish = nullptr;
    for (auto &node : this->nodes) {
        if (node->name() == startName)
            start = node;
        if (node->name() == finishName)
            finish = node;
    }
    if (start == nullptr || finish == nullptr)
        return "";
    this->regularize();
    start->visited();
    auto cur = start;
    std::stack<Node *> visitedNodes;
    visitedNodes.push(cur);
    while (!finish->isVisited()) {
        bool isPath = false;
        for (auto &edge : cur->edges())
            if (!edge.first->isVisited()) {
                cur = edge.first;
                isPath = true;
                break;
            }
        if (!isPath) {
            result.pop_back();
            visitedNodes.pop();
            if (visitedNodes.empty())
                return "";
            else
                cur = visitedNodes.top();
            continue;
        }
        cur->visited();
        visitedNodes.push(cur);
        result += cur->name();
    }
    return result;
}

std::string Graph::astarSearch (char startName, char finishName) {
    std::string result = "";
    if (startName == finishName) {
        result += startName;
        return result;
    }
    Node *start = nullptr, *finish = nullptr;
    for (auto &node : this->nodes) {
        if (node->name() == startName)
            start = node;
        if (node->name() == finishName)
            finish = node;
    }
    if (start == nullptr || finish == nullptr)
        return "";
    start->visited();
    auto cur = start;
    cur->visited();
    double weight = 0;
    std::vector<std::pair<char, char>> visitedEdges;
    auto heuristic = [finishName] (const Node *node) {return abs(finishName - node->name());};
    std::vector<std::pair<std::pair<Node *, Node *>, double>> queue;
    while (!finish->isVisited()) {
        for (auto &edge : cur->edges()) {
            double lenEdge = edge.second + heuristic(edge.first) + weight;
            auto temp = std::make_pair(std::make_pair(cur, edge.first), lenEdge);
            for (auto &obj : queue)
                if (obj.second > lenEdge)
                    continue;
                else
                    std::swap(temp, obj);
            queue.push_back(temp);
        }
        bool noPath = true;
        char prev;
        while (!queue.empty()) {
            cur = queue.back().first.second;
            weight = queue.back().second;
            prev = queue.back().first.first->name();
            queue.pop_back();
            if (cur->weight() > weight) {
                for (auto it = visitedEdges.begin(); it < visitedEdges.end(); it++)
                    if (it->second == cur->name()) {
                        visitedEdges.erase(it);
                        break;
                    }
                cur->updateWeight(weight);
                cur->visited();
                noPath = false;
                break;
            }
        }
        weight -= heuristic(cur);
        if (noPath)
            return "";
        else
            visitedEdges.emplace_back(prev, cur->name());
    }
    char node = finishName;
    std::string temp = "";
    temp += node;
    while (node != startName) {
        for (auto &edge : visitedEdges)
            if (edge.second == node) {
                node = edge.first;
                break;
            }
        temp += node;
    }
    for (int i = temp.size() - 1; i >= 0; i--)
        result += temp[i];
    return result;
}

std::string Graph::astarSearch (char startName, char finishName1, char finishName2) {
    std::string result = "";
    if (startName == finishName1 || startName == finishName2) {
        result += startName;
        return result;
    }
    Node *start = nullptr, *finish1 = nullptr, *finish2 = nullptr;
    for (auto &node : this->nodes) {
        if (node->name() == startName)
            start = node;
        if (node->name() == finishName1)
            finish1 = node;
        if (node->name() == finishName2)
            finish2 = node;
    }
    if (start == nullptr || finish1 == nullptr || finish2 == nullptr)
        return "";
    start->visited();
    auto cur = start;
    cur->visited();
    double weight = 0;
    std::vector<std::pair<char, char>> visitedEdges;
    auto heuristic = [finishName1, finishName2] (const Node *node) {
        return abs(finishName1 - node->name()) > abs(finishName2 - node->name()) ? abs(finishName2 - node->name()) : abs(finishName1 - node->name());
    };
    std::vector<std::pair<std::pair<Node *, Node *>, double>> queue;
    while (!finish1->isVisited() && !finish2->isVisited()) {
        for (auto &edge : cur->edges()) {
            double lenEdge = edge.second + heuristic(edge.first) + weight;
            auto temp = std::make_pair(std::make_pair(cur, edge.first), lenEdge);
            for (auto &obj : queue)
                if (obj.second > lenEdge)
                    continue;
                else
                    std::swap(temp, obj);
            queue.push_back(temp);
        }
        bool noPath = true;
        char prev;
        while (!queue.empty()) {
            cur = queue.back().first.second;
            weight = queue.back().second;
            prev = queue.back().first.first->name();
            queue.pop_back();
            if (cur->weight() > weight) {
                for (auto it = visitedEdges.begin(); it < visitedEdges.end(); it++)
                    if (it->second == cur->name()) {
                        visitedEdges.erase(it);
                        break;
                    }
                cur->updateWeight(weight);
                cur->visited();
                noPath = false;
                break;
            }
        }
        weight -= heuristic(cur);
        if (noPath)
            return "";
        else
            visitedEdges.emplace_back(prev, cur->name());
    }
    char node = visitedEdges[visitedEdges.size() - 1].second;
    std::string temp = "";
    temp += node;
    while (node != startName) {
        for (auto &edge : visitedEdges)
            if (edge.second == node) {
                node = edge.first;
                break;
            }
        temp += node;
    }
    for (int i = temp.size() - 1; i >= 0; i--)
        result += temp[i];
    return result;
}

void Graph::refresh () {
    for (auto &node : this->nodes)
        node->refresh();
}

std::ostream &operator << (std::ostream &out, const Graph &graph) {
    for (auto &node : graph.nodes)
        out << node << '\n';
    return out;
}