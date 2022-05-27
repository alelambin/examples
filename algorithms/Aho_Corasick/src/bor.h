#ifndef BOR_H
#define BOR_H

#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include "node.h"

class Bor {
public:
    Bor (std::string &, char);
    Bor (std::vector<std::string> &);
    ~Bor ();
    std::vector<std::pair<int, int>> algorithmAhoCorasick (std::string &, bool);
    int maxEdges () const;
    std::string erasePattern (std::string &, std::vector<std::string> &, bool);

protected:
    void addBranch (bool);
    void addSuffixLinks ();

private:
    Node *root;
    std::vector<std::pair<std::string, int>> patterns;
    int patternEnd;

};

#endif
