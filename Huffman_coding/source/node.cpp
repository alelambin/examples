#include "node.h"

Node::Node (std::weak_ptr<Node> parent, char data) : left(nullptr), right(nullptr), parent(parent) {
    this->data = data;
    this->weight = 0;
}

Node::Node (std::shared_ptr<Node> left, std::shared_ptr<Node> right, std::weak_ptr<Node> parent) : left(left), right(right), parent(parent) {
    this->data = std::monostate();
    this->weight = 0;
}

void Node::add () {
    this->weight++;
    if (this->parent.lock())
        this->parent.lock()->add();
}

void Node::recalculate () {
    if (std::holds_alternative<std::monostate>(this->data)) {
        int leftWeight = 0, rightWeight = 0;
        if (this->left)
            leftWeight = this->left->weight;
        if (this->right)
            rightWeight = this->right->weight;
        this->weight = leftWeight + rightWeight;
    }
    if (this->parent.lock())
        this->parent.lock()->recalculate();
}

void Node::print (std::ostream &out, int level) {
    if (this->right)
        this->right->print(out, level + 1);

    for (int i = 0; i < level; i++)
        out << '\t';
    if (std::holds_alternative<char>(this->data))
        if (std::get<char>(this->data) == '\0')
            out << " * (" << this->weight << ")\n";
        else
            out << '\'' << std::get<char>(this->data) << "\'(" << this->weight << ")\n";
    else
        out << "   (" << this->weight << ")\n";

    if (this->left)
        this->left->print(out, level + 1);
}

int Node::colorPrint (std::vector<std::shared_ptr<Node>> arr, int level) {
    int strCount = 0;

    if (this->right)
        strCount += this->right->colorPrint(arr, level + 1);
    
    for (int i = 0; i < level; i++)
        std::cout << '\t';
    bool isColor = false;
    std::vector<std::shared_ptr<Node>>::iterator iter;
    for (iter = arr.begin(); iter != arr.end(); iter++) 
        if (this == iter->get()) {
            isColor = true;
            break;
        }
        
    if (isColor) 
        std::cout << "\033[1;33m";
    if (std::holds_alternative<char>(this->data))
        if (std::get<char>(this->data) == '\0')
            std::cout << " * (" << this->weight << ')';
        else
            std::cout << '\'' << std::get<char>(this->data) << "\'(" << this->weight << ')';
    else
        std::cout << "   (" << this->weight << ')';
    if (isColor) 
        std::cout << "\033[0m";
    std::cout << '\n';
    strCount++;

    if (this->left)
        strCount += this->left->colorPrint(arr, level + 1); 
    return strCount;
}
