#pragma once
#include "Node.h"

class Graph
{
    //ID, type - Node*
    std::map<int, std::pair<int,Node*>> nodes;
    //currentNodeID, prevID - nextID - currentNodeLength - currentNodeSpeed
    std::multimap<int,std::tuple<int,int,double,double>> neighbors;
    int numLocations=0, numIntersections=0;
    public:
    ~Graph();
    void addNode(Node*);
    
    Node* findNodeByID(int);
    const Node* findNodeByID(int) const;

    std::vector<std::vector<std::tuple<int,int,double>>> transformGraphToMatrix() const;
    void printGraphMatrix(std::ostream&,std::vector<std::vector<std::tuple<int,int,double>>>) const;

    std::vector<LocationNode*> vectorOfLocations() const;
    std::vector<IntersectionNode*> vectorOfIntersections() const;
    std::vector<Node*> vectorOfLocationsAndIntersections() const;
    int findNodeInVector(std::vector<Node*>,const Node*) const;
    int findNodeInVector(std::vector<LocationNode*>,const Node*) const;

    int getNumLocations() const;
    int getNumIntersections() const;
    std::map<int, std::pair<int,Node*>> getNodes() const;
    std::multimap<int,std::tuple<int,int,double,double>> getNeighbors() const;

    void setNumOfLocations(int);
    void setNumOfIntersections(int);

    void serialize(const std::string&);
    static Graph deserialize(const std::string&,int&,int&);

    private:
    void addNodeToNeighborhood(int,int,int,double,double);
};