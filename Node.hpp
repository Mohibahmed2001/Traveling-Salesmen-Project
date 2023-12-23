#ifndef NODE_HPP
#define NODE_HPP

#include <cmath>

class Node {
public:
    int id;
    double x, y;
    Node* edge1;
    Node* edge2;  

    Node(int _id, double _x, double _y) : id(_id), x(_x), y(_y), edge1(nullptr), edge2(nullptr) {}
    double distance(const Node& other) const {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }
};

#endif 
