#include "Node.h"

int Node::getID() const
{
    return this->ID;
}

int Node::IDcounter=0;

void Node::setIDcounterToZero()
{
    IDcounter=0;
}

//location node methods
std::string LocationNode::locationName() const
{
    return this->name;
}
void LocationNode::setIncRoadID(int incID)
{
    this->incRoadID=incID;
}
void LocationNode::setOutRoadID(int outID)
{
    this->outRoadID=outID;
}
int LocationNode::getIncRoadID() const
{
    return this->incRoadID;
}
int LocationNode::getOutRoadID() const
{
    return this->outRoadID;
}
NodeType LocationNode::getType() const
{
    return LOCATION;
}
void LocationNode::print(std::ostream& out)
{
    out<<this->getType()<<","<<this->locationName()<<","<<this->getID()<<std::endl;
    out<<this->getIncRoadID()<<","<<this->getOutRoadID()<<std::endl;
}

//road node methods
NodeType RoadNode::getType() const
{
    return ROAD;
}
void RoadNode::print(std::ostream& out)
{
    out<<this->getType()<<","<<this->NameOfRoad()<<","<<this->getID()<<std::endl;
    out<<this->getStartNodeID()<<","<<this->getEndNodeID()<<","<<this->Length()<<","<<this->MaxSpeed()<<","<<this->MaxVehicles()<<std::endl;
}
double RoadNode::Length() const
{
    return this->length;
}
double RoadNode::MaxSpeed() const
{
    return this->maxSpeed;
}
int RoadNode::MaxVehicles() const
{
    return this->maxVehicles;
}
int RoadNode::getCurrentNumOfVehicles() const
{
    return this->currentNumOfVehicles;
}

std::string RoadNode::NameOfRoad() const
{
    return this->name;
}
int RoadNode::getStartNodeID() const
{
    return this->startNodeID;
}
int RoadNode::getEndNodeID() const
{
    return this->endNodeID;
}
void RoadNode::setStartNodeID(int startID)
{
    this->startNodeID=startID;
}
void RoadNode::setEndNodeID(int endID)
{
    this->endNodeID=endID;
}
void RoadNode::setCurrentNumOfVehiclesOnRoad(int numVehicles)
{
    this->currentNumOfVehicles=numVehicles;
}

//intersection node methods
NodeType IntersectionNode::getType() const
{
    return INTERSECTION;
}
void IntersectionNode::setIntersectionName(std::string name)
{
    this->name="I"+std::to_string(this->getID());
}
void IntersectionNode::setCurrentNumOfVehiclesOnIntersection(int numOfVehicles)
{
    this->currentNumOfVehicles=numOfVehicles;
}
void IntersectionNode::setStdLength(double stdLength)
{
    this->stdLength=stdLength;
}
void IntersectionNode::setAverageSpeed(double speed)
{
    this->averageSpeed=speed;
}
void IntersectionNode::print(std::ostream& out)
{
    out<<this->getType()<<","<<this->intersectionName()<<","<<this->getID()<<std::endl;
    out<<this->getMaxNumOfVehiclesBeforeHalt()<<std::endl;
    
    out<<this->numOfRoadsConnectedToIntersection()<<std::endl;
    for(RoadNode* road: this->getIncomingRoads())
    {
        out<<"inc,"<<road->NameOfRoad()<<","<<road->getID()<<std::endl;
    }
    for(RoadNode* road: this->getOutgoingRoads())
    {
        out<<"out,"<<road->NameOfRoad()<<","<<road->getID()<<std::endl;
    }
    out<<this->numOfPairsOfConnectedRoads()<<std::endl;
    for(const auto& map: pairsOfConnectedRoads)
    {
        int firstID=map.first.first;
        int secondID=map.first.second;
        double length=map.second;
        out<<firstID<<","<<secondID<<","<<length<<std::endl;
    }
}
std::string IntersectionNode::intersectionName() const
{
    return this->name;
}
int IntersectionNode::getMaxNumOfVehiclesBeforeHalt() const
{
    return this->maxNumOfVehiclesBeforeHalt;
}
int IntersectionNode::CurrentNumOfVehicles() const
{
    return this->currentNumOfVehicles;
}
double IntersectionNode::getStdLength() const
{
    return this->stdLength;
}
double IntersectionNode::getAverageSpeed() const
{
    return this->averageSpeed;
}
std::vector<RoadNode*> IntersectionNode::getIncomingRoads() const
{
    return this->incomingRoads;
}
std::vector<RoadNode*> IntersectionNode::getOutgoingRoads() const
{
    return this->outgoingRoads;
}
void IntersectionNode::connectIncomingRoadToIntersection(RoadNode* incRoad)
{
    this->incomingRoads.push_back(incRoad);
}
void IntersectionNode::connectOutgoingRoadToIntersection(RoadNode* outRoad)
{
    this->outgoingRoads.push_back(outRoad);
}
int IntersectionNode::numOfIncomingRoads() const
{
    return this->incomingRoads.size();
}    
int IntersectionNode::numOfOutgoingRoads() const
{
    return this->outgoingRoads.size();
}
int IntersectionNode::numOfRoadsConnectedToIntersection() const
{
    return this->incomingRoads.size() + this->outgoingRoads.size();
}

double IntersectionNode::calculateRealSpeed(int currentNumOfVehicles)
{
    int maxVehicles=this->getMaxNumOfVehiclesBeforeHalt();
    if(currentNumOfVehicles>=maxVehicles)
    {
        return 0;
    }
    else if(currentNumOfVehicles==0)
    {
        return this->getAverageSpeed();
    }   
    else
    {
        int numOfIncRoads=this->numOfIncomingRoads();
        int numOfOutRoads=this->numOfOutgoingRoads();
        double speedCoefficient;

        //calculating coefficient
        int difference=numOfIncRoads-numOfOutRoads;

        const double maxCoefficient=1.0;
        const double minCoefficient=0.5;

        const double standardSpeed=this->getAverageSpeed();
        const int higherLimit=3;
        const int lowerLimit=-3;

        if(difference<=lowerLimit)
            speedCoefficient=minCoefficient;
        else if(difference>=higherLimit)
            speedCoefficient=maxCoefficient;
        else
        {
            double tmp=(difference-lowerLimit)/static_cast<double>(higherLimit-lowerLimit);
            speedCoefficient=minCoefficient+tmp*(maxCoefficient-minCoefficient);
        }

        speedCoefficient-=0.1*currentNumOfVehicles;

        if(speedCoefficient<minCoefficient)
            speedCoefficient=minCoefficient;
        else if(speedCoefficient>maxCoefficient)
            speedCoefficient=maxCoefficient;

        return standardSpeed*speedCoefficient;
    }
}

void IntersectionNode::setRealSpeed()
{
    this->realSpeed=this->calculateRealSpeed(this->CurrentNumOfVehicles());
}

RoadNode* IntersectionNode::findRoadByID(int roadID)
{
    for(const auto& road : incomingRoads)
    {
        if(roadID==road->getID())
            return road;
    }
    for(const auto& road : outgoingRoads)
    {
        if(roadID==road->getID())
            return road;
    }
    return nullptr;
}
const RoadNode* IntersectionNode::findRoadByID(int roadID) const
{
    for(const auto& road : incomingRoads)
    {
        if(roadID==road->getID())
            return road;
    }
    for(const auto& road : outgoingRoads)
    {
        if(roadID==road->getID())
            return road;
    }
    return nullptr;
}

void IntersectionNode::addPairsOfConnectedRoads(int incRoadID,int outRoadID,double length)
{
    this->pairsOfConnectedRoads.emplace(std::make_pair(incRoadID,outRoadID),length);
}
int IntersectionNode::numOfPairsOfConnectedRoads() const
{
    return this->pairsOfConnectedRoads.size();
}

double IntersectionNode::getLengthBetweenRoads(int incRoadID, int outRoadID) const
{
    std::pair<int,int> pair=std::make_pair(incRoadID,outRoadID);
    if(pairsOfConnectedRoads.count(pair)>0)
        return pairsOfConnectedRoads.at(pair);
    else
        return std::numeric_limits<double>::infinity();
}

std::vector<std::vector<std::tuple<int,int,double>>> IntersectionNode::transformIntersectionToMatrix()
{
    int in=this->numOfIncomingRoads();
    int out=this->numOfOutgoingRoads();
    
    std::tuple init=std::make_tuple(-1,-1,std::numeric_limits<double>::infinity());

    std::vector<std::vector<std::tuple<int,int,double>>> distMatrix(in, std::vector<std::tuple<int,int,double>>(out,init));

    for(int i=0;i<in;i++)
    {
        RoadNode* incRoad=incomingRoads.at(i);
        for(int j=0;j<out;j++)
        {
            RoadNode* outRoad=outgoingRoads.at(j);
            double lengthBtwRoads=this->getLengthBetweenRoads(incRoad->getID(),outRoad->getID());
            distMatrix[i][j]=std::make_tuple(incRoad->getID(),outRoad->getID(),lengthBtwRoads);
        }
    }

    return distMatrix;
}

void IntersectionNode::printIntersectionMatrix(std::ostream& out, std::vector<std::vector<std::tuple<int,int,double>>> intersectionMatrix) const
{
    for(auto& row: intersectionMatrix)
    {
        for(auto& elem: row)
        {
            out<<std::setw(8)<<std::left<<std::fixed<<std::setprecision(2)<<std::get<2>(elem)<<" ";
        }
        out<<std::endl;
    }
}