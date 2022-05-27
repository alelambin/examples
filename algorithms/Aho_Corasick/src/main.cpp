#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <getopt.h>
#include "node.h"
#include "bor.h"

int main (int argc, char *argv[]) {
    bool jockerFlag = false;
    bool maxEdgesFlag = false;
    bool eraseFlag = false;
    std::string outputFileName = "";
    std::string inputFileName = "";
    const char *shortOptions = "jmef:o:h?";
    option longOptions[] = {
        {"joker", no_argument, nullptr, 'j'},
        {"max", no_argument, nullptr, 'm'},
        {"erase", no_argument, nullptr, 'e'},
        {"help", no_argument, nullptr, 'h'},
        {0, 0, nullptr, 0}
    };
    int longIndex;
    int option = getopt_long(argc, argv, shortOptions, longOptions, &longIndex);
    while (option != -1) {
        switch (option) {
            case 'j':
                jockerFlag = true;
                break;
            case 'm':
                maxEdgesFlag = true;
                break;
            case 'e':
                eraseFlag = true;
                break;
            case 'f':
                inputFileName = optarg;
                break;
            case 'o':
                outputFileName = optarg;
                break;
            case 'h':
                std::cout << "\t-j --joker\tEnable search with joker mode\n";
                std::cout << "\t-m --max\tEnable max edges search mode\n";
                std::cout << "\t-e --erase\tEnable erase found string mode\n";
                std::cout << "\t-f <file>\tSpecify the name of the input file\n";
                std::cout << "\t-o <file>\tSpecify the name of the output file\n";
                std::cout << "\t-h -? --help\tCall help information\n";
                return 0;
        }
        option = getopt_long(argc, argv, shortOptions, longOptions, &longIndex);
    }

    std::string text, pattern;
    if (jockerFlag) {
        char joker;
        if (!inputFileName.empty()) {
            std::ifstream inputFile(inputFileName);
            if (!inputFile.is_open()) {
                std::cerr << "Error: wrong input file name\n";
                return 0;
            }
            inputFile >> text;
            inputFile >> pattern;
            inputFile >> joker;
            inputFile.close();
        } else {
            std::cin >> text;
            std::cin >> pattern;
            std::cin >> joker;
        }
        Bor bor(pattern, joker);
        auto result = bor.algorithmAhoCorasick(text, true);
        if (!outputFileName.empty()) {
            std::ofstream outputFile(outputFileName);
            if (!outputFile.is_open()) {
                std::cerr << "Error: wrong output file name\n";
                return 0;
            }
            for (auto &obj : result)
                outputFile << obj.first << '\n';
            outputFile.close();
        } else {
            for (auto &obj : result)
                std::cout << obj.first << '\n';
        }
        if (maxEdgesFlag) 
            std::cout << "Max number of edges outgoing from one node is " << bor.maxEdges() << '\n';
        if (eraseFlag) {
            std::vector<std::string> pt = {pattern};
            std::cout << bor.erasePattern(text, pt, true) << '\n';
        }
    } else {
        int n;
        std::vector<std::string> patterns;
        if (!inputFileName.empty()) {
            std::ifstream inputFile(inputFileName);
            if (!inputFile.is_open()) {
                std::cerr << "Error: wrong input file name\n";
                return 0;
            }
            inputFile >> text;
            inputFile >> n;
            for (int i = 0; i < n; i++) {
                inputFile >> pattern;
                patterns.push_back(pattern);
            }
            inputFile.close();
        } else {
            std::cin >> text;
            std::cin >> n;
            for (int i = 0; i < n; i++) {
                std::cin >> pattern;
                patterns.push_back(pattern);
            }
        }
        Bor bor(patterns);
        auto result = bor.algorithmAhoCorasick(text, false);
        if (!outputFileName.empty()) {
            std::ofstream outputFile(outputFileName);
            if (!outputFile.is_open()) {
                std::cerr << "Error: wrong output file name\n";
                return 0;
            }
            for (auto &obj : result)
                outputFile << obj.first << ' ' << obj.second << '\n';
            outputFile.close();
        } else {
            for (auto &obj : result)
                std::cout << obj.first << ' ' << obj.second << '\n';
        }
        if (maxEdgesFlag) 
            std::cout << "Max number of edges outgoing from one node is " << bor.maxEdges() << '\n';
        if (eraseFlag)
            std::cout << bor.erasePattern(text, patterns, false) << '\n';
    }
    return 0;
}