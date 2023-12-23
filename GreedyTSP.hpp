#ifndef GREEDYTSP_HPP
#define GREEDYTSP_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>
#include "Node.hpp"

class GreedyTSP {
public:
    static void greedyTSP(const std::string& filename) {
        // PROCESS READ FILE
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error open " << filename << std::endl;
            return;
        }
        std::string line;
        std::vector<Node> nodes;
        bool startReading = false;
        while (std::getline(file, line)) {
            // LAST LINE
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
        // BEGIN ALGO
        std::vector<int> visitedNodes;
        std::vector<Edge> edges;
        auto start = std::clock();
        for (int i = 0; i < nodes.size(); ++i) {
            for (int j = i + 1; j < nodes.size(); ++j) {
                edges.push_back(Edge(nodes[i], nodes[j]));
            }
        }
        std::sort(edges.begin(), edges.end());
        for (const auto& edge : edges) {
            if (addEdge(visitedNodes, edge)) {
                std::cout << "Edge from " << edge.node1.id << " to " << edge.node2.id << " of weight " << edge.weight << std::endl;
            }
        }
        std::cout << "\nPath: ";
        for (int node : visitedNodes) {
            std::cout << node << " ";
        }
        auto endTime = std::clock();
        double totalTime = static_cast<double>(endTime - start) / CLOCKS_PER_SEC * 1000.0;
        std::cout << "\nTotal Distance: " << calculateTotalDistance(visitedNodes, nodes) << "\nTime in millis: " << totalTime << std::endl;
        file.close();
    }
private:
    struct Edge {
        Node node1, node2;
        double weight;

        Edge(const Node& n1, const Node& n2) : node1(n1), node2(n2), weight(n1.distance(n2)) {}

        bool operator<(const Edge& other) const {
            return weight < other.weight;
        }
    };
    static double calculateTotalDistance(const std::vector<int>& visitedNodes, const std::vector<Node>& nodes) {
        double totalDistance = 0.0;
        for (size_t i = 1; i < visitedNodes.size(); ++i) {
            totalDistance += nodes[visitedNodes[i - 1] - 1].distance(nodes[visitedNodes[i] - 1]);
        }
        totalDistance += nodes[visitedNodes.back() - 1].distance(nodes[0]);
        return totalDistance;
    }
    static bool addEdge(std::vector<int>& visitedNodes, const Edge& edge) {
        if (visitedNodes.size() == 0) {
            visitedNodes.push_back(edge.node1.id);
            visitedNodes.push_back(edge.node2.id);
            return true;
        }
        if (std::find(visitedNodes.begin(), visitedNodes.end(), edge.node1.id) != visitedNodes.end() &&
            std::find(visitedNodes.begin(), visitedNodes.end(), edge.node2.id) == visitedNodes.end()) {
            visitedNodes.push_back(edge.node2.id);
            return true;
        }
        if (std::find(visitedNodes.begin(), visitedNodes.end(), edge.node2.id) != visitedNodes.end() &&
            std::find(visitedNodes.begin(), visitedNodes.end(), edge.node1.id) == visitedNodes.end()) {
            visitedNodes.push_back(edge.node1.id);
            return true;
        }
        return false;
    }
};
#endif

