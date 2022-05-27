#include "kmp.h"

std::vector<int> kmp::prefixFunction (std::string &str) {
    std::vector<int> values = {0};
    int i = 1, j = 0;
    while (i < str.size()) {
        if (str[i] != str[j]) {
            if (j == 0) {
                values.push_back(0);
                i++;
            } else {
                j = values[j - 1];
            }
        } else {
            values.push_back(j + 1);
            i++;
            j++;
        }
    }
    return values;
}

std::vector<int> kmp::kmpSearch (std::string &text, std::string &pattern) {
    std::vector<int> indices;
    int i = 0, j = 0;
    auto prefix = prefixFunction(pattern);
    while (i < text.size()) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
            if (j == pattern.size()) {
                indices.push_back(i - j);
                j = prefix[j - 1];
            }
        } else {
            if (j == 0)
                i++;
            else
                j = prefix[j - 1];
        }
    }
    if (indices.empty())
        indices.push_back(-1);
    return indices;
}

std::string kmp::convertVector (std::vector<int> &indices) {
    std::string result = "";
    if (indices.empty())
        return "";
    for (auto &index : indices)
        result += std::to_string(index) + ',' + ' ';
    result.pop_back();
    result.pop_back();
    return result;
}