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

    // Method to calculate distance between two nodes
    double distance(const Node& other) const {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }
};

class NearestNeighbor {
public:
    // Function to perform nearest neighbor algorithm
    static void nearestNeighbor(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        std::string line;
        std::vector<Node> nodes;
        bool startReading = false;  // Flag to indicate when to start reading coordinates

        // Find the line containing "NODE_COORD_SECTION"
        while (std::getline(file, line)) {
            if (line.find("NODE_COORD_SECTION") != std::string::npos) {
                startReading = true;
                break;
            }
        }

        // Read the file and extract node data starting from "NODE_COORD_SECTION"
        while (std::getline(file, line)) {
            // Stop reading when a line starting with "EOF" is encountered or if not in the section
            if (line.find("EOF") != std::string::npos || !startReading) {
                break;
            }

            // Check if the line starts with a number (indicating node coordinates)
            if (isdigit(line[0])) {
                // Extract node information
                int id;
                double x, y;
                std::istringstream iss(line);
                iss >> id >> x >> y;
                nodes.push_back(Node(id, x, y));  // Use push_back instead of emplace_back
            }
        }

        // Nearest neighbor algorithm
        std::vector<int> visitedNodes;
        visitedNodes.push_back(1); // Start from node 1

        double totalDistance = 0.0;
        auto startTime = std::clock();

        while (visitedNodes.size() < nodes.size()) {
            int current = visitedNodes.back();
            double minDistance = std::numeric_limits<double>::max();
            int nearestNode = -1;

            for (const auto& node : nodes) {
                if (std::find(visitedNodes.begin(), visitedNodes.end(), node.id) == visitedNodes.end()) {
                    double dist = nodes[current - 1].distance(node);
                    if (dist < minDistance) {
                        minDistance = dist;
                        nearestNode = node.id;
                    }
                }
            }

            // Update the nearest node
            if (nearestNode != -1) {
                visitedNodes.push_back(nearestNode);
            } else {
                // Handle the case when nearestNode is not updated correctly
                std::cerr << "Error: Unable to find the nearest node." << std::endl;
                break;
            }

            totalDistance += minDistance;
        }

        // Add the first node to close the tour
        visitedNodes.push_back(1);

        totalDistance += nodes[visitedNodes.back() - 1].distance(nodes[0]);

        auto endTime = std::clock();
        double totalTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC * 1000.0;

        // Print the results
        std::cout << "Path: ";
        for (int node : visitedNodes) {
            std::cout << node << " ";
        }

        std::cout << "\nTotal Distance: " << totalDistance << "\nTime in ms: " << totalTime << std::endl;

        file.close();
    }
};

#endif // NEARESTNEIGHBOR_HPP
