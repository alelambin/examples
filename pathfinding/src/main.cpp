#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <getopt.h>
#include "node.h"
#include "graph.h"

int main (int argc, char *argv[]) {
    bool greedySearchFlag = false;
    std::string outputFileName = "";
    const char *shortOptions = "go:h?";
    option longOptions[] = {
        {"greedy", no_argument, nullptr, 'g'},
        {"help", no_argument, nullptr, 'h'},
        {0, 0, nullptr, 0}
    };
    int longIndex;
    int option = getopt_long(argc, argv, shortOptions, longOptions, &longIndex);
    while (option != -1) {
        switch (option) {
            case 'g':
                greedySearchFlag = true;
                break;
            case 'o':
                outputFileName = optarg;
                break;
            case 'h':
                std::cout << "\t-g --greedy\tEnable greedy search mode\n";
                std::cout << "\t-o <file>\tSpecify the name of the output file\n";
                std::cout << "\t-h -? --help\tCall help information\n";
                return 0;
        }
        option = getopt_long(argc, argv, shortOptions, longOptions, &longIndex);
    }
    Graph graph;
    char start, finish1, finish2 = '\0';
    std::string nodes;
    std::getline(std::cin, nodes);
    nodes.erase(remove_if(nodes.begin(), nodes.end(), isspace), nodes.end());
    if (greedySearchFlag)
        if (nodes.size() == 2) {
            start = nodes[0];
            finish1 = nodes[1];
        } else {
            std::cerr << "Error: wrong input data\n";
            return 0;
        }
    else
        if (nodes.size() == 2) {
            start = nodes[0];
            finish1 = nodes[1];
        } else if (nodes.size() == 3) {
            start = nodes[0];
            finish1 = nodes[1];
            finish2 = nodes[2];
        } else {
            std::cerr << "Error: wrong input data\n";
            return 0;
        }
    char node1, node2;
    double len;
    while (!std::cin.eof()) {
        std::cin >> node1 >> node2 >> len;
        graph.addNode(node1);
        graph.addNode(node2);
        graph.addEdge(node1, node2, len);
    }
    std::string path;
    if (greedySearchFlag)
        path = graph.greedySearch(start, finish1);
    else
        if (finish2)
            path = graph.astarSearch(start, finish1, finish2);
        else
            path = graph.astarSearch(start, finish1);
    if (outputFileName.size()) {
        if (path.empty()) {
            std::cout << "Could not find the path\n";
            return 0;
        }
        std::ofstream outputFile(outputFileName);
        if (outputFile.is_open())
            outputFile << path;
        else
            std::cout << "Error: could not open the file\n" << path << '\n';
        outputFile.close();
    } else {
        if (!path.empty())
            std::cout << path << '\n';
        else
            std::cout << "Could not find the path\n";
    }
    return 0;
}
