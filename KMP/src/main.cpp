#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <getopt.h>
#include "kmp.h"

int main (int argc, char *argv[]) {
    bool cycleFlag = false;
    std::string outputFileName = "";
    std::string inputFileName = "";
    const char *shortOptions = "cf:o:h?";
    option longOptions[] = {
        {"cycle", no_argument, nullptr, 'c'},
        {"help", no_argument, nullptr, 'h'},
        {0, 0, nullptr, 0}
    };
    int longIndex;
    int option = getopt_long(argc, argv, shortOptions, longOptions, &longIndex);
    while (option != -1) {
        switch (option) {
            case 'c':
                cycleFlag = true;
                break;
            case 'f':
                inputFileName = optarg;
                break;
            case 'o':
                outputFileName = optarg;
                break;
            case 'h':
                std::cout << "\t-c --cycle\tEnable cyclic shift mode\n";
                std::cout << "\t-f <file>\tSpecify the name of the input file\n";
                std::cout << "\t-o <file>\tSpecify the name of the output file\n";
                std::cout << "\t-h -? --help\tCall help information\n";
                return 0;
        }
        option = getopt_long(argc, argv, shortOptions, longOptions, &longIndex);
    }

    std::string pattern, text;
    if (!inputFileName.empty()) {
        std::ifstream inputFile(inputFileName);
        if (!inputFile.is_open()) {
            std::cerr << "Error: wrong input file name\n";
            return -1;
        }
        std::getline(inputFile, pattern);
        std::getline(inputFile, text);
        inputFile.close();
    } else {
        std::getline(std::cin, pattern);
        std::getline(std::cin, text);
    }

    std::string result = "";
    if (cycleFlag) {
        if (text.size() != pattern.size()) {
            std::cout << -1 << '\n';
            return 0;
        }
        auto temp = pattern;
        pattern = text;
        text = temp;
        text += text;
        result = std::to_string(kmp::kmpSearch(text, pattern)[0]);
    } else {
        auto indices = kmp::kmpSearch(text, pattern);
        result = kmp::convertVector(indices);
    }

    if (!outputFileName.empty()) {
        std::ofstream outputFile(outputFileName);
        if (!outputFile.is_open()) {
            std::cerr << "Error: wrong output file name\n";
            return -1;
        }
        outputFile << result;
        outputFile.close();
    } else {
        std::cout << result << '\n';
    }
    return 0;
}