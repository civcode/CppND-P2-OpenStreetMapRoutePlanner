#ifndef ROUTE_MODEL_H
#define ROUTE_MODEL_H

#include <limits>
#include <cmath>
#include <unordered_map>
#include "model.h"
#include <iostream>

class RouteModel : public Model {

  public:
    class Node : public Model::Node {
      public:
        // Add public Node variables and methods here.
        Node* parent = nullptr;

        float h_value = std::numeric_limits<float>::max();
        float g_value = 0.0;
        bool visited = false;
        std::vector<RouteModel::Node *> neighbors;
        
        Node(){}
        Node(int idx, RouteModel* search_model, Model::Node node) : Model::Node(node), parent_model(search_model), index(idx) {}
      
        float distance(Node other) const {
          //std::cout << "float distance()\n";
          //std::cout << "x = " << x << std::endl;
          //std::cout << "other.x = " << other.x << std::endl;
          return std::sqrt(std::pow(x-other.x, 2) + std::pow(y-other.y, 2));
        }
      
        void FindNeighbors();
      
      private:
        // Add private Node variables and methods here.
        std::vector<Node> m_Nodes;
      
        int index;
        RouteModel* parent_model = nullptr;
        RouteModel::Node* FindNeighbor(std::vector<int> node_indices);
      
    };
    
    // Add public RouteModel variables and methods here.
    RouteModel(const std::vector<std::byte> &xml);  
    auto &SNodes() { return  m_Nodes; }
    auto &GetNodeToRoadMap() { return node_to_road; }
    Node &FindClosestNode(float x, float y);
    std::vector<Node> path; // This variable will eventually store the path that is found by the A* search.
   

  private:
    // Add private RouteModel variables and methods here.
    std::unordered_map<int, std::vector<const Model::Road*>> node_to_road;
    std::vector<Node> m_Nodes;
    void CreateNodeToRoadHashmap();
};

#endif