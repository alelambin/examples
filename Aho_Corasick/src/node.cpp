#include "node.h"

Node::Node (char name, Node *ancestor) : name_(name), ancestor(ancestor) {
    this->suffixLink_ = nullptr;
    this->endLink_ = nullptr;
}

char Node::name () const {
    return this->name_;
}

std::vector<Node *> Node::descendants () const {
    return this->descendants_;
}

Node *Node::getDescendant (char name) const {
    for (auto &node : descendants_)
        if (node->name() == name)
            return node;
    return nullptr;
}

bool Node::addDescendant (Node *descendant) {
	if (this == descendant)
		return false;
	for (auto &son : this->descendants_)
		if (son->name_ == descendant->name())
			return false;
    this->descendants_.push_back(descendant);
    return true;
}

void Node::deleteDescendants () {
    for (auto &node : this->descendants_) {
        node->deleteDescendants();
        delete node;
    }
}

bool Node::addTerminal (int strNum) {
	for (auto &num : this->terminals_)
		if (num == strNum)
			return false;
    this->terminals_.push_back(strNum);
    return true;
}

std::vector<int> Node::terminals () const {
    return this->terminals_;
}

void Node::addSuffixLink () {
    if (this->name() == '\0') {
        this->suffixLink_ = this;
    } else if (this->ancestor->name() == '\0') {
        this->suffixLink_ = this->ancestor;
    } else {
        auto curNode = this->ancestor->suffixLink_;
        auto nextNode = curNode->getDescendant(this->name());
        while (nextNode == nullptr) {
            if (curNode->name() == '\0') {
                nextNode = curNode;
                break;
            }
            curNode = curNode->suffixLink_;
            nextNode = curNode->getDescendant(this->name());
        }
        this->suffixLink_ = nextNode;
        auto temp = nextNode;
        while (temp->terminals().empty()) {
            if (temp->name() == '\0')
                break;
            temp = temp->suffixLink();
        }
        if (!temp->terminals().empty())
            this->endLink_ = temp;
    }
}

Node *Node::suffixLink () const {
    return this->suffixLink_;
}

Node *Node::endLink () const {
    return this->endLink_;
}
