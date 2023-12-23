#ifndef GREEDYTSP_HPP
#define GREEDYTSP_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <limits>
#include "Node.hpp"

class GreedyTSP {
public:
    static void greedyTSP(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        std::string line;
        std::vector<Node> nodes;
        bool startReading = false;

        while (std::getline(file, line)) {
            if (line.find("NODE_COORD_SECTION") != std::string::npos) {
                startReading = true;
                break;
            }
        }

        while (std::getline(file, line)) {
            if (isdigit(line[0])) {
                int id;
                double x, y;
                std::istringstream iss(line);
                iss >> id >> x >> y;
                nodes.push_back(Node(id, x, y));
            }
        }

        std::vector<int> visitedNodes;
        visitedNodes.push_back(1);
        double totalDistance = 0.0;
        auto start = std::clock();

        while (visitedNodes.size() < nodes.size()) {
            int current = visitedNodes.back();
            double minimumDistance = std::numeric_limits<double>::max();
            int nearestNode = -1;

            for (const auto& node : nodes) {
                if (std::find(visitedNodes.begin(), visitedNodes.end(), node.id) == visitedNodes.end()) {
                    double dist = nodes[current - 1].distance(node);
                    if (dist < minimumDistance) {
                        minimumDistance = dist;
                        nearestNode = node.id;
                    }
                }
            }

            if (nearestNode != -1) {
                visitedNodes.push_back(nearestNode);
            } else {
                std::cerr << "Can't find nearest node." << std::endl;
                break;
            }

            totalDistance += minimumDistance;
        }

        visitedNodes.push_back(1);
        totalDistance += nodes[visitedNodes.back() - 1].distance(nodes[0]);

        auto endTime = std::clock();
        double totalTime = static_cast<double>(endTime - start) / CLOCKS_PER_SEC * 1000.0;

        std::cout << "Path: ";
        for (int node : visitedNodes) {
            std::cout << node << " ";
        }

        std::cout << "\nTotal Distance: " << totalDistance << "\nTime in ms: " << totalTime << std::endl;
        file.close();
    }
};

#endif 
