#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <iomanip>

enum NodeType { LOCATION, ROAD, INTERSECTION };


class Node
{
    NodeType type;
    int ID;
    static int IDcounter;

    public:
    Node(NodeType type) : type(type), ID(IDcounter++) {}
    Node(NodeType type, int ID) : type(type), ID(ID) {}

    int getID() const;
    virtual NodeType getType() const = 0;

    static void setIDcounterToZero();

    virtual void print(std::ostream&) = 0;

};

class LocationNode : public Node
{
    std::string name;
    int incRoadID;
    int outRoadID;
    public:
    LocationNode(NodeType type, std::string name) : Node(type), name(name) {}
    LocationNode(NodeType type, int ID, std::string name) : Node(type,ID), name(name) {}
    std::string locationName() const;
    void setIncRoadID(int);
    void setOutRoadID(int);
    int getIncRoadID() const;
    int getOutRoadID() const;

    virtual NodeType getType() const override;
    virtual void print(std::ostream&) override;
};

class RoadNode : public Node
{
    double length;
    double maxSpeed;
    int maxVehicles;
    int currentNumOfVehicles;

    int startNodeID;
    int endNodeID;
    std::string name;

    public:
    RoadNode(NodeType type, std::string name, int startID, int endID, double len, double maxSpeed, int maxVehicles, int currentNumVehicles=0) : Node(type), name(name), startNodeID(startID), endNodeID(endID), length(len), maxSpeed(maxSpeed), maxVehicles(maxVehicles), currentNumOfVehicles(currentNumVehicles) {}
    RoadNode(NodeType type, int ID, std::string name, int startID, int endID, double len, double maxSpeed, int maxVehicles, int currentNumVehicles=0) : Node(type,ID), name(name), startNodeID(startID), endNodeID(endID), length(len), maxSpeed(maxSpeed), maxVehicles(maxVehicles), currentNumOfVehicles(currentNumVehicles) {}
    RoadNode(NodeType type, std::string name, double len, double maxSpeed, int maxVehicles, int currentNumVehicles=0) : Node(type), name(name), length(len), maxSpeed(maxSpeed), maxVehicles(maxVehicles), currentNumOfVehicles(currentNumVehicles) {}
    
    double Length() const;
    double MaxSpeed() const;
    int MaxVehicles() const;
    int getCurrentNumOfVehicles() const;
    std::string NameOfRoad() const;

    int getStartNodeID() const;
    int getEndNodeID() const;

    void setStartNodeID(int);
    void setEndNodeID(int);
    void setCurrentNumOfVehiclesOnRoad(int);

    virtual NodeType getType() const override;
    virtual void print(std::ostream&) override;
};

class IntersectionNode : public Node
{
    std::string name="I"+std::to_string(this->getID());
    int maxNumOfVehiclesBeforeHalt;
    int currentNumOfVehicles;
    double stdLength;
    double averageSpeed;
    double realSpeed;
    std::vector<RoadNode*> incomingRoads;
    std::vector<RoadNode*> outgoingRoads;
    std::map<std::pair<int,int>,double> pairsOfConnectedRoads;

    public:
    IntersectionNode(NodeType type) : Node(type) {}
    IntersectionNode(NodeType type, int maxNumOfVehicles) : Node(type), maxNumOfVehiclesBeforeHalt(maxNumOfVehicles) {}
    IntersectionNode(NodeType type, int ID, int maxNumOfVehicles) : Node(type,ID), maxNumOfVehiclesBeforeHalt(maxNumOfVehicles) {}

    void setIntersectionName(std::string);
    void setCurrentNumOfVehiclesOnIntersection(int);
    void setStdLength(double);
    void setAverageSpeed(double);

    std::string intersectionName() const;
    int getMaxNumOfVehiclesBeforeHalt() const;
    int CurrentNumOfVehicles() const;
    double getStdLength() const;
    double getAverageSpeed() const;

    std::vector<RoadNode*> getIncomingRoads() const;
    std::vector<RoadNode*> getOutgoingRoads() const;

    void connectIncomingRoadToIntersection(RoadNode*);
    void connectOutgoingRoadToIntersection(RoadNode*);

    void setRealSpeed();

    int numOfIncomingRoads() const;
    int numOfOutgoingRoads() const;
    int numOfRoadsConnectedToIntersection() const;

    RoadNode* findRoadByID(int);
    const RoadNode* findRoadByID(int) const;

    void addPairsOfConnectedRoads(int,int,double);
    int numOfPairsOfConnectedRoads() const;

    double getLengthBetweenRoads(int,int) const;

    std::vector<std::vector<std::tuple<int,int,double>>> transformIntersectionToMatrix();
    void printIntersectionMatrix(std::ostream&, std::vector<std::vector<std::tuple<int,int,double>>>) const;

    virtual NodeType getType() const override;
    virtual void print(std::ostream&) override;

    private:
    double calculateRealSpeed(int);
};