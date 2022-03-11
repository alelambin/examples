#include <iostream>
#include <fstream>
#include <string>
#include <getopt.h>
#include "node.h"
#include "graph.h"

int main (int argc, char *argv[]) {
    std::string inputFileName = "";
    std::string outputFileName = "";
    const char *shortOptions = "fo:h?";
    option longOptions[] = {
        {"file", no_argument, nullptr, 'f'},
        {"help", no_argument, nullptr, 'h'},
        {0, 0, nullptr, 0}
    };
    int longIndex;
    int option = getopt_long(argc, argv, shortOptions, longOptions, &longIndex);
    while (option != -1) {
        switch (option) {
            case 'f':
                inputFileName = optarg;
                break;
            case 'o':
                outputFileName = optarg;
                break;
            case 'h':
                std::cout << "\t-f --file\tSpecify the name of the input file\n";
                std::cout << "\t-o <file>\tSpecify the name of the output file\n";
                std::cout << "\t-h -? --help\tCall help information\n";
                return 0;
        }
        option = getopt_long(argc, argv, shortOptions, longOptions, &longIndex);
    }

    Graph graph;
    int n;
    char source, destination;
    char sNode, dNode;
    int weight;
    if (inputFileName.size() > 0) {
        std::ifstream inputFile(inputFileName);
        if (!inputFile.is_open()) {
            std::cout << "Wrong input file name\n";
            return 0;
        }
        inputFile >> n;
        inputFile >> source;
        inputFile >> destination;
        for (int i = 0; i < n; i++) {
            inputFile >> sNode >> dNode >> weight;
            graph.addNode(sNode);
            graph.addNode(dNode);
            graph.addEdge(sNode, dNode, weight);
        }
        inputFile.close();
    } else {
        std::cin >> n;
        std::cin >> source;
        std::cin >> destination;
        for (int i = 0; i < n; i++) {
            std::cin >> sNode >> dNode >> weight;
            graph.addNode(sNode);
            graph.addNode(dNode);
            graph.addEdge(sNode, dNode, weight);
        }
    }
    unsigned int flow = 0;
    try {
        flow = graph.FordFulkerson(source, destination);
    } catch (const char *exception) {
        std::cout << exception << '\n';
        return 0;
    }
    if (outputFileName.size() > 0) {
        std::ofstream outputFile(outputFileName);
        if (!outputFile.is_open()) {
            std::cout << "Wrong output file name\n";
            return 0;
        }
        outputFile << flow << '\n' << graph;
        outputFile.close();
    } else {
        std::cout << flow << '\n' << graph;
    }
    return 0;
}