// NearestNeighbor.hpp
#ifndef NEARESTNEIGHBOR_HPP
#define NEARESTNEIGHBOR_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>

class Node {
public:
    int id;
    double x, y;

    Node(int _id, double _x, double _y) : id(_id), x(_x), y(_y) {}
    double distance(const Node& other) const {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }
};

class NearestNeighbor {
public:
    static void nearestNeighbor(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        std::string line;
        std::vector<Node> nodes;
        while (std::getline(file, line)) {
            if (line == "NODE_COORD_SECTION")
                break;

          
            int id;
            double x, y;
            std::istringstream iss(line);
            iss >> id >> x >> y;
            nodes.push_back(Node(id, x, y));  
        }

        std::vector<int> visitedNodes;
        visitedNodes.push_back(1); 

        double totalDistance = 0.0;
        auto startTime = std::clock();

        while (visitedNodes.size() < nodes.size()) {
            int current = visitedNodes.back();
            double minDistance = std::numeric_limits<double>::max();
            int nearestNode = -1;

            for (const auto& node : nodes) {
                if (std::find(visitedNodes.begin(), visitedNodes.end(), node.id) == visitedNodes.end()) {
                    double dist = nodes[current - 1].distance(node);
                    std::cout << "Distance from " << current << " to " << node.id << ": " << dist << std::endl;  // Debug line
                    if (dist < minDistance) {
                        minDistance = dist;
                        nearestNode = node.id;
                    }
                }
            }
            if (nearestNode != -1) {
                visitedNodes.push_back(nearestNode);
            } else {
                
                std::cerr << "Error: Unable to find the nearest node." << std::endl;
                break;
            }

            totalDistance += minDistance;
        }
        visitedNodes.push_back(1);

        totalDistance += nodes[visitedNodes.back() - 1].distance(nodes[0]);

        auto endTime = std::clock();
        double totalTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC * 1000.0;
        std::cout << "Path: ";
        for (int node : visitedNodes) {
            std::cout << node << " ";
        }

        std::cout << "\nTotal Distance: " << totalDistance << "\nTime in ms: " << totalTime << std::endl;

        file.close();
    }
};

#endif // NEARESTNEIGHBOR_HPP
