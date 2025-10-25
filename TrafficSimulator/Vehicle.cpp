#include "Vehicle.h"

Vehicle::Vehicle(std::string name, Graph& graph, int startID, int goalID, double averageSpeed): name(name), startLocationID(startID), goalLocationID(goalID), averageSpeed(averageSpeed)
{
    this->constructGraph(graph.getNeighbors());
}
std::string Vehicle::getName() const
{
    return this->name;
}
int Vehicle::getStartID() const
{
    return this->startLocationID;
}
int Vehicle::getGoalID() const
{
    return this->goalLocationID;
}
double Vehicle::getAverageSpeed() const
{
    return this->averageSpeed;
}

void Vehicle::calculateVehicleSpeedOnRoadSegments()
{
    double targetSpeed=this->getAverageSpeed();
    double realSpeed=0;

    for(auto& elem: graph)
    {
        for(auto& segment: elem.second)
        {
            int nodeID=segment.first;
            double distanceOfTheSegment=segment.second.first;
            double speedOfTheSegment=segment.second.second;

            if(targetSpeed<speedOfTheSegment)
                realSpeed=speedOfTheSegment;
            else
                realSpeed=targetSpeed;

            std::pair<double,double> newSegment=std::make_pair(distanceOfTheSegment,realSpeed);
            segment.second.swap(newSegment);
        }
    }
}

void Vehicle::constructGraph(const std::multimap<int,std::tuple<int,int,double,double>>& neighbors)
{
    for(const auto& pair: neighbors)
    {
        int currentNodeID=pair.first;
        int nextNodeID=std::get<1>(pair.second);
        double distance=std::get<2>(pair.second);
        double speed=std::get<3>(pair.second);
        std::pair<double,double> distSpeed=std::make_pair(distance,speed);
        this->graph[currentNodeID].emplace(nextNodeID,distSpeed);
    }

    //change speed of the nodes (max speed) to speed of the vehicle (real speed)
    this->calculateVehicleSpeedOnRoadSegments();
}
void Vehicle::initializePathInfoD()
{
    for(auto& node: graph)
    {
        for(auto& neighbor: node.second)
        {
            int nextNodeID=neighbor.first;
            double distance=neighbor.second.first;
            double speed=neighbor.second.second;
            double time=distance/speed;
            
            pathInfoD[node.first][neighbor.first].distance=distance;
            pathInfoD[node.first][neighbor.first].time=time;
            pathInfoD[node.first][neighbor.first].prevNodeID=node.first;
        }
    }
}
void Vehicle::initializePathInfoT()
{
    for(auto& node: graph)
    {
        for(auto& neighbor: node.second)
        {
            int nextNodeID=neighbor.first;
            double distance=neighbor.second.first;
            double speed=neighbor.second.second;
            double time=distance/speed;
            
            pathInfoT[node.first][neighbor.first].distance=distance;
            pathInfoT[node.first][neighbor.first].time=time;
            pathInfoT[node.first][neighbor.first].prevNodeID=node.first;
        }
    }
}

void Vehicle::floydWarshall()
{
    this->initializePathInfoD();
    for(auto& kNode: graph)
    {
        for(auto& iNode: graph)
        {
            for(auto& jNode: graph)
            {
                double newDistance=pathInfoD[iNode.first][kNode.first].distance + pathInfoD[kNode.first][jNode.first].distance;
                double newTime=pathInfoD[iNode.first][kNode.first].time + pathInfoD[kNode.first][jNode.first].time;

                if(newDistance < pathInfoD[iNode.first][jNode.first].distance)
                {
                    pathInfoD[iNode.first][jNode.first].distance=newDistance;
                    pathInfoD[iNode.first][jNode.first].time=newTime;
                    pathInfoD[iNode.first][jNode.first].prevNodeID=pathInfoD[kNode.first][jNode.first].prevNodeID;
                }
            }
        }
    }
}
void Vehicle::setQuickestPath()
{
    this->initializePathInfoT();
    for(auto& kNode: graph)
    {
        for(auto& iNode: graph)
        {
            for(auto& jNode: graph)
            {
                double newDistance=pathInfoT[iNode.first][kNode.first].distance + pathInfoT[kNode.first][jNode.first].distance;
                double newTime=pathInfoT[iNode.first][kNode.first].time + pathInfoT[kNode.first][jNode.first].time;
                
                if(newTime < pathInfoT[iNode.first][jNode.first].time)
                {
                    pathInfoT[iNode.first][jNode.first].distance=newDistance;
                    pathInfoT[iNode.first][jNode.first].time=newTime;
                    pathInfoT[iNode.first][jNode.first].prevNodeID=pathInfoT[kNode.first][jNode.first].prevNodeID;
                }
            }
        }
    }
}

std::vector<std::tuple<int,double,double>> Vehicle::getPathD()
{
    std::vector<std::tuple<int,double,double>> path;
    int currentNodeID=this->getGoalID();
    int startNodeID=this->getStartID();
    double currentDistance;
    double currentTime;

    while(currentNodeID!=startNodeID)
    {
        if(pathInfoD.find(startNodeID) != pathInfoD.end() && pathInfoD[startNodeID].find(currentNodeID) != pathInfoD[startNodeID].end())
        {
            currentDistance=pathInfoD[startNodeID][currentNodeID].distance;
            currentTime=pathInfoD[startNodeID][currentNodeID].time;
            
            path.push_back(std::make_tuple(currentNodeID,currentDistance,currentTime));
            currentNodeID=pathInfoD[startNodeID][currentNodeID].prevNodeID;
        }
    }
    path.push_back(std::make_tuple(startNodeID,0,0));
    std::reverse(path.begin(),path.end());
    return path;
}

void Vehicle::printPathD(std::ostream& out, Graph& graph)
{
    std::vector<std::tuple<int,double,double>> path=this->getPathD();
    int n=path.size();

    for(int i=0;i<n;i++)
    {
        int currentNodeID=std::get<0>(path[i]);
        double distance=std::get<1>(path[i]);
        double time=std::get<2>(path[i]);
        
        Node* node=graph.findNodeByID(currentNodeID);
        if(node->getType()==NodeType::LOCATION)
        {
            LocationNode* locNode=dynamic_cast<LocationNode*>(node);
            out<<locNode->locationName()<<" ("<<distance<<","<<time<<")";
        }
        else if(node->getType()==NodeType::ROAD)
        {
            RoadNode* roadNode=dynamic_cast<RoadNode*>(node);
            out<<roadNode->NameOfRoad()<<" ("<<distance<<","<<time<<")";
        }
        else if(node->getType()==NodeType::INTERSECTION)
        {
            IntersectionNode* interNode=dynamic_cast<IntersectionNode*>(node);
            out<<interNode->intersectionName()<<" ("<<distance<<","<<time<<")";
        }

        if(i!=n-1)
        {
            out<<" -> ";
        }
    }
}
std::vector<std::tuple<int,double,double>> Vehicle::getPathT()
{
    std::vector<std::tuple<int,double,double>> path;
    int currentNodeID=this->getGoalID();
    int startNodeID=this->getStartID();
    double currentDistance;
    double currentTime;

    while(currentNodeID!=startNodeID)
    {
        if(pathInfoT.find(startNodeID) != pathInfoT.end() && pathInfoT[startNodeID].find(currentNodeID) != pathInfoT[startNodeID].end())
        {
            currentDistance=pathInfoT[startNodeID][currentNodeID].distance;
            currentTime=pathInfoT[startNodeID][currentNodeID].time;
            
            path.push_back(std::make_tuple(currentNodeID,currentDistance,currentTime));
            currentNodeID=pathInfoT[startNodeID][currentNodeID].prevNodeID;
        }
    }
    path.push_back(std::make_tuple(startNodeID,0,0));
    std::reverse(path.begin(),path.end());
    return path;
}

void Vehicle::printPathT(std::ostream& out, Graph& graph)
{
    std::vector<std::tuple<int,double,double>> path=this->getPathT();
    int n=path.size();

    for(int i=0;i<n;i++)
    {
        int currentNodeID=std::get<0>(path[i]);
        double distance=std::get<1>(path[i]);
        double time=std::get<2>(path[i]);
        
        Node* node=graph.findNodeByID(currentNodeID);
        if(node->getType()==NodeType::LOCATION)
        {
            LocationNode* locNode=dynamic_cast<LocationNode*>(node);
            out<<locNode->locationName()<<" ("<<distance<<","<<time<<")";
        }
        else if(node->getType()==NodeType::ROAD)
        {
            RoadNode* roadNode=dynamic_cast<RoadNode*>(node);
            out<<roadNode->NameOfRoad()<<" ("<<distance<<","<<time<<")";
        }
        else if(node->getType()==NodeType::INTERSECTION)
        {
            IntersectionNode* interNode=dynamic_cast<IntersectionNode*>(node);
            out<<interNode->intersectionName()<<" ("<<distance<<","<<time<<")";
        }

        if(i!=n-1)
        {
            out<<" -> ";
        }
    }
}

void Vehicle::setVehicleInfoForDistSim()
{
    std::vector<std::tuple<int,double,double>> path=this->getPathD();
    int n=path.size();

    std::vector<std::tuple<int,double,double,double,double>> pathDetail;
    int currentNodeID;
    double distance, time, length, neededTime;

    for(int i=0; i<n-1;i++)
    {
        currentNodeID=std::get<0>(path[i]);
        distance=std::get<1>(path[i]);
        time=std::get<2>(path[i]);
        int nextNodeID=std::get<0>(path[i+1]);

        auto currentNodeIter=pathInfoD.find(currentNodeID);
        if(currentNodeIter!=pathInfoD.end())
        {
            auto &nextNodeMap=currentNodeIter->second;
            auto nextNodeIter=nextNodeMap.find(nextNodeID);
            if(nextNodeIter!=nextNodeMap.end())
            {
                //we found info about the length of the road
                PathInfo &info=nextNodeIter->second;
                length=info.distance;
                neededTime=info.time;
            }
        }

        pathDetail.push_back(std::make_tuple(currentNodeID,length,distance,neededTime,time));
    }

    currentNodeID=std::get<0>(path[n-1]);
    distance=std::get<1>(path[n-1]);
    time=std::get<2>(path[n-1]);
    //last node is a location
    length=0;
    neededTime=0;

    pathDetail.push_back(std::make_tuple(currentNodeID,length,distance,neededTime,time));

    this->vehicleInfoForDistSim=pathDetail;
}

std::vector<std::tuple<int,double,double,double,double>>& Vehicle::getVehicleInfoForDistSim()
{
    return this->vehicleInfoForDistSim;
}
void Vehicle::printVehicleInfoForDistSim(std::ostream& out)
{
    int tmp=0;
    for(auto& info: vehicleInfoForDistSim)
    {
        std::tuple<int,double,double,double,double> infoPath=info;
        out<<std::get<0>(info)<<" (duzina: "<<std::get<1>(info)<<", predjena duzina: "<<std::get<2>(info)<<", potrebno vrijeme: "<<std::get<3>(info)<<" proteklo vrijeme: "<<std::get<4>(info)<<")";
        if(tmp<vehicleInfoForDistSim.size())
        {
            out<<" -> ";
        }
        tmp++;
    }
}
void Vehicle::setVehicleInfoForTimeSim()
{
    std::vector<std::tuple<int,double,double>> path=this->getPathT();
    int n=path.size();

    std::vector<std::tuple<int,double,double,double,double>> pathDetail;
    int currentNodeID;
    double distance, time, length, neededTime;

    for(int i=0; i<n-1;i++)
    {
        currentNodeID=std::get<0>(path[i]);
        distance=std::get<1>(path[i]);
        time=std::get<2>(path[i]);
        int nextNodeID=std::get<0>(path[i+1]);

        auto currentNodeIter=pathInfoT.find(currentNodeID);
        if(currentNodeIter!=pathInfoT.end())
        {
            auto &nextNodeMap=currentNodeIter->second;
            auto nextNodeIter=nextNodeMap.find(nextNodeID);
            if(nextNodeIter!=nextNodeMap.end())
            {
                //we found the info about the length of the road
                PathInfo &info=nextNodeIter->second;
                length=info.distance;
                neededTime=info.time;
            }
        }

        pathDetail.push_back(std::make_tuple(currentNodeID,length,distance,neededTime,time));
    }

    currentNodeID=std::get<0>(path[n-1]);
    distance=std::get<1>(path[n-1]);
    time=std::get<2>(path[n-1]);
    //last node is a location
    length=0;
    neededTime=0;

    pathDetail.push_back(std::make_tuple(currentNodeID,length,distance,neededTime,time));

    this->vehicleInfoForTimeSim=pathDetail;
}

std::vector<std::tuple<int,double,double,double,double>>& Vehicle::getVehicleInfoForTimeSim()
{
    return this->vehicleInfoForTimeSim;
}
void Vehicle::printVehicleInfoForTimeSim(std::ostream& out)
{
    int tmp=0;
    for(auto& info: vehicleInfoForTimeSim)
    {
        std::tuple<int,double,double,double,double> infoPath=info;
        out<<std::get<0>(info)<<" (duzina: "<<std::get<1>(info)<<", predjena duzina: "<<std::get<2>(info)<<", potrebno vrijeme: "<<std::get<3>(info)<<" proteklo vrijeme: "<<std::get<4>(info)<<")";
        if(tmp<vehicleInfoForTimeSim.size())
        {
            out<<" -> ";
        }
        tmp++;
    }
}