#include "bor.h"

Bor::Bor (std::string &pattern, char joker) {
    this->root = new Node('\0', nullptr);
    bool flag = pattern[0] != joker;
    int begin = 0;
    for (int i = 0; i < pattern.size(); i++) {
        if (pattern[i] == joker && flag) {
            this->patterns.emplace_back(pattern.substr(begin, i - begin), i);
            flag = false;
        }
        if (pattern[i] != joker && !flag) {
            begin = i;
            flag = true;
        }
    }
    if (pattern[pattern.size() - 1] != joker)
        this->patterns.emplace_back(pattern.substr(begin, pattern.size() - begin), pattern.size());
    this->patternEnd = 0;
    for (int i = pattern.size() - 1; i >= 0; i--)
        if (pattern[i] == joker)
            this->patternEnd++;
        else
            break;
    this->addBranch(true);
    this->addSuffixLinks();
}

Bor::Bor (std::vector<std::string> &patterns) {
    this->root = new Node('\0', nullptr);
    for (auto &pattern : patterns) 
        this->patterns.emplace_back(pattern, 0);
    this->patternEnd = 0;
    this->addBranch(false);
    this->addSuffixLinks();
}

Bor::~Bor () {
    root->deleteDescendants();
    delete root;
}

std::vector<std::pair<int, int>> Bor::algorithmAhoCorasick (std::string &text, bool isJoker) {
    auto curNode = root;
    std::vector<std::pair<int, int>> strFound;
    if (isJoker) {
        std::vector<int> strOccurrences(text.size(), 0);
        for (int index = 0; index < text.size() - this->patternEnd; index++) {
            auto nextNode = curNode->getDescendant(text[index]);
            while (nextNode == nullptr) {
                if (curNode->name() == '\0') {
                    nextNode = curNode;
                    break;
                }
                curNode = curNode->suffixLink();
                nextNode = curNode->getDescendant(text[index]);
            }
            for (auto &patternIndex : nextNode->terminals())
                if (index - patternIndex + 1 >= 0)
                    strOccurrences[index - patternIndex + 1]++;
            auto temp = nextNode->endLink();
            while (temp != nullptr) {
                for (auto &patternIndex : temp->terminals())
                    if (index - patternIndex + 1 >= 0)
                        strOccurrences[index - patternIndex + 1]++;
                temp = temp->endLink();
            }
            curNode = nextNode;
        }
        for (int i = 0; i < strOccurrences.size(); i++)
            if (strOccurrences[i] == patterns.size())
                strFound.emplace_back(i + 1, 1);
    } else {
        for (int index = 0; index < text.size(); index++) {
            auto nextNode = curNode->getDescendant(text[index]);
            while (nextNode == nullptr) {
                if (curNode->name() == '\0') {
                    nextNode = curNode;
                    break;
                }
                curNode = curNode->suffixLink();
                nextNode = curNode->getDescendant(text[index]);
            }
            if (!nextNode->terminals().empty())
                strFound.emplace_back(index - this->patterns[nextNode->terminals()[0] - 1].first.size() + 2, nextNode->terminals()[0]);
            auto temp = nextNode->endLink();
            while (temp != nullptr) {
                strFound.emplace_back(index - this->patterns[temp->terminals()[0] - 1].first.size() + 2, temp->terminals()[0]);
                temp = temp->endLink();
            }
            curNode = nextNode;
        }
        std::sort(strFound.begin(), strFound.end(), [](std::pair<int, int> pair1, std::pair<int, int> pair2){
            return pair1.first == pair2.first ? pair1.second < pair2.second : pair1.first < pair2.first;
        });
    }
    return strFound;
}

int Bor::maxEdges () const {
    int max = 0;
    std::queue<Node *> queue;
    Node *curNode = root;
    queue.push(root);
    while (!queue.empty()) {
        int links = (curNode->suffixLink() ? 1 : 0) + (curNode->endLink() ? 1 : 0);
        max = curNode->descendants().size() + links > max ? curNode->descendants().size() + links : max;
        queue.pop();
        for (auto &node : curNode->descendants())
            queue.push(node);
        curNode = queue.front();
    }
    return max;
}

std::string Bor::erasePattern (std::string &text, std::vector<std::string> &patterns, bool isJoker) {
    std::vector<bool> isErase(text.size(), false);
    auto entrance = algorithmAhoCorasick(text, isJoker);
    for (auto &obj : entrance)
        for (int i = obj.first - 1; i < obj.first + patterns[obj.second - 1].size() - 1; i++)
            isErase[i] = true;
    std::string result = "";
    for (int i = 0; i < text.size(); i++)
        if (!isErase[i])
            result += text[i];
    return result;
}

void Bor::addBranch (bool isJoker) {
    int strNum = 1;
    for (auto &str : patterns) {
        Node *curNode = root;
        for (int i = 0; i < str.first.size(); i++) {
            auto nextNode = curNode->getDescendant(str.first[i]);
            if (nextNode == nullptr) {
                nextNode = new Node(str.first[i], curNode);
                curNode->addDescendant(nextNode);
            }
            if (i == str.first.size() - 1)
                if (isJoker)
                    nextNode->addTerminal(str.second);
                else 
                    nextNode->addTerminal(strNum);
            else
                curNode = nextNode;
        }
        strNum++;
    }
}

void Bor::addSuffixLinks () {
    std::queue<Node *> queue;
    Node *curNode = root;
    queue.push(root);
    while (!queue.empty()) {
        curNode->addSuffixLink();
        queue.pop();
        for (auto &node : curNode->descendants())
            queue.push(node);
        curNode = queue.front();
    }
}
