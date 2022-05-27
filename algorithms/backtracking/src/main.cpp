#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <getopt.h>
#include "backtracking.h"

int main (int argc, char *argv[]) {
    bool operationCounterFlag = true;
    std::string outputFileName = "";
    const char *shortOptions = "co:h?";
    option longOptions[] = {
        {"counter", no_argument, nullptr, 'c'},
        {"help", no_argument, nullptr, 'h'},
        {0, 0, nullptr, 0}
    };
    int longIndex;
    int option = getopt_long(argc, argv, shortOptions, longOptions, &longIndex);
    while (option != -1) {
        switch (option) {
            case 'c':
                operationCounterFlag = false;
                break;
            case 'o':
                outputFileName = optarg;
                break;
            case 'h':
                std::cout << "\t-c --counter\tEnable operation counter mode\n";
                std::cout << "\t-o <file>\tSpecify the name of the output file\n";
                std::cout << "\t-h -? --help\tCall help information\n";
                return 0;
        }
        option = getopt_long(argc, argv, shortOptions, longOptions, &longIndex);
    }
    int n, operationCounter = 0;
    std::cin >> n;
    auto res = bktg::getMinSquares(n, operationCounter);
    if (!operationCounterFlag) {
        std::cout << operationCounter << '\n';
        return 0;
    }
    if (outputFileName.size()) {
        std::ofstream outputFile(outputFileName);
        outputFile << res.size() << '\n';
        for (auto &sq : res)
            outputFile << sq.first.first << ' ' << sq.first.second << ' ' << sq.second << '\n';
        outputFile.close();
    } else {
        std::cout << res.size() << '\n';
        for (auto &sq : res)
            std::cout << sq.first.first << ' ' << sq.first.second << ' ' << sq.second << '\n';
    }
    return 0;
}
