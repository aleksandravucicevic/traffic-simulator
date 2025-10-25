#pragma once
#include "Graph.h"

struct PathInfo
{
    int prevNodeID;
    double distance;
    double time;

    PathInfo():prevNodeID(-1), distance(std::numeric_limits<double>::infinity()), time(std::numeric_limits<double>::infinity()){}
};

class Vehicle
{
    std::string name;
    int startLocationID;
    int goalLocationID;
    double averageSpeed;
    
    //currentNodeID, prevNodeID - distance - speed
    std::map<int,std::multimap<int,std::pair<double,double>>> graph;
    //currentNodeID, nextNodeID - PathInfo (prevNodeId,distance,time)
    std::map<int,std::map<int,PathInfo>> pathInfoD;
    std::map<int,std::map<int,PathInfo>> pathInfoT;
    //currentNodeID, length of the segment, distance traveled, time needed, time elapsed
    std::vector<std::tuple<int,double,double,double,double>> vehicleInfoForDistSim;
    std::vector<std::tuple<int,double,double,double,double>> vehicleInfoForTimeSim;

    public:
    Vehicle(std::string name, Graph& graph, int startID, int goalID, double averageSpeed=50.0);

    std::string getName() const;
    int getStartID() const;
    int getGoalID() const;
    double getAverageSpeed() const;
    std::vector<std::tuple<int,double,double,double,double>>& getVehicleInfoForDistSim();
    std::vector<std::tuple<int,double,double,double,double>>& getVehicleInfoForTimeSim();

    void floydWarshall();
    void setQuickestPath();
    void printPathD(std::ostream&,Graph&);
    void printPathT(std::ostream&,Graph&);
    void setVehicleInfoForDistSim();
    void setVehicleInfoForTimeSim();
    void printVehicleInfoForDistSim(std::ostream&);
    void printVehicleInfoForTimeSim(std::ostream&);

    private:
    void constructGraph(const std::multimap<int,std::tuple<int,int,double,double>>&);
    void calculateVehicleSpeedOnRoadSegments();
    void initializePathInfoD();
    void initializePathInfoT();

    //currentNodeID - distance - speed
    std::vector<std::tuple<int,double,double>> getPathD();
    std::vector<std::tuple<int,double,double>> getPathT();
};