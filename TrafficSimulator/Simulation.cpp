#include "Simulation.h"

int Simulation::simulationCounter=0;

void Simulation::setSimCounterToZero()
{
    simulationCounter=0;
}

Simulation::Simulation(Graph& graph,std::map<Vehicle*,std::vector<std::tuple<int,double,double,double,double>>>& vehicleInfo)
{
    this->setSimInfo(graph,vehicleInfo,numOfStepsInSimulation);
}

int Simulation::simSteps() const
{
    return this->numOfStepsInSimulation;
}

std::string Simulation::getNodeName(Graph& graph, int nodeID)
{
    Node* node=graph.findNodeByID(nodeID);

    if(node)
    {
        if(node->getType()==NodeType::LOCATION)
        {
            LocationNode* locationNode=dynamic_cast<LocationNode*>(node);
            return locationNode->locationName();
        }
        else if(node->getType()==NodeType::ROAD)
        {
            RoadNode* roadNode=dynamic_cast<RoadNode*>(node);
            return roadNode->NameOfRoad();
        }
        else if(node->getType()==NodeType::INTERSECTION)
        {
            IntersectionNode* intersectionNode=dynamic_cast<IntersectionNode*>(node);
            return intersectionNode->intersectionName();
        }
    }

    return "";
}

void Simulation::setSimInfo(Graph& graph,std::map<Vehicle*,std::vector<std::tuple<int,double,double,double,double>>>& vehicleInfo,int& stepCounter)
{
    for(auto& [vehicle,pathDetail]: vehicleInfo)
    {
        std::vector<std::pair<int,std::string>> vehicleStepInfo;

        //start node
        int startNodeID=std::get<0>(pathDetail.front());
        std::string startNodeName=getNodeName(graph, startNodeID);
        vehicleStepInfo.push_back(std::make_pair(startNodeID, startNodeName));
        stepCounter=1;
        
        for(size_t i=0;i<pathDetail.size();++i)
        {
            int currentNodeID=std::get<0>(pathDetail[i]);
            double length=std::get<1>(pathDetail[i]);
            double distance=std::get<2>(pathDetail[i]);
            double neededTime=std::get<3>(pathDetail[i]);
            double elapsedTime=std::get<4>(pathDetail[i]);

            double simulationTime=stepCounter*SIMULATION_CONSTANT;
            stepCounter++;

            if(simulationTime>=elapsedTime)
            {
                //vehicle reaches the next node
                if(i<pathDetail.size()-1)
                {
                    int nextNodeID=std::get<0>(pathDetail[i+1]);
                    std::string nextNodeName=getNodeName(graph,nextNodeID);
                    vehicleStepInfo.push_back(std::make_pair(nextNodeID,nextNodeName));
                }
            }
            else
            {
                //vehicle remains at the current node
                std::string currentNodeName=getNodeName(graph,currentNodeID);
                vehicleStepInfo.push_back(std::make_pair(currentNodeID,currentNodeName));
            }
        }

        simInfo[vehicle]=vehicleStepInfo;
    }
}
std::map<Vehicle*,std::pair<int,std::string>> Simulation::doOneStepOfSimulation()
{
    std::map<Vehicle*,std::pair<int,std::string>> stepInfo;

    for(auto& [vehicle,stepVector]: simInfo)
    {
        if(simulationCounter<stepVector.size())
        {
            stepInfo[vehicle]=stepVector[simulationCounter];
        }
        else
        {
            //if there is no further info - the vehicle has arrived at its destination
            stepInfo[vehicle]=stepVector.back();
        }
    }
    simulationCounter++;
    return stepInfo;
}
bool Simulation::isSimulationOver()
{
    int stepCounter;
    for(auto& [vehicle,stepVector]: simInfo)
    {
        int tmp=stepVector.size();
        if(tmp>stepCounter)
        {
            stepCounter=tmp;
        }
    }
    
    if(simulationCounter<stepCounter)
        return false;
    return true;
}
void Simulation::currentPositionOfVehicles(std::ostream& out)
{
    out<<"Trenutne pozicije vozila:"<<std::endl;
    
    for(auto& [vehicle,stepVector]: simInfo)
    {
        if(simulationCounter<stepVector.size())
        {
            std::pair<int,std::string> currentPosition=stepVector[simulationCounter];
            out<<"Vozilo: "<<vehicle->getName()<<", trenutna pozicija: "<<currentPosition.second<< std::endl;
        }
        else
        {
            //if the sim is over for the vehicle - it reached the destination
            std::pair<int, std::string> lastPosition=stepVector.back();
            out<<"Vozilo: "<<vehicle->getName()<<", trenutna pozicija: "<<lastPosition.second<<" [Simulacija zavrsena za vozilo "<<vehicle->getName()<<"]"<< std::endl;
        }
    }
}
double Simulation::averageTime(Graph& graph,Vehicle& vehicle)
{
    std::vector<std::tuple<int,double,double,double,double>>& vehicleInfo=vehicle.getVehicleInfoForTimeSim();

    double totalTimeNeeded=0.0;
    double maxTime=0.0;

    for(const auto& segment: vehicleInfo)
    {
        int currentNodeID=std::get<0>(segment);
        double length=std::get<1>(segment);
        double timeNeeded=std::get<3>(segment);

        totalTimeNeeded+=timeNeeded;

        Node* currentNode=graph.findNodeByID(currentNodeID);
        if(currentNode)
        {
            double speed;
            double timeForSegment;
            double length;
            if(currentNode->getType()==NodeType::LOCATION)
            {
                timeForSegment=0.0;
            }
            else if(currentNode->getType()==NodeType::ROAD)
            {
                RoadNode* road=dynamic_cast<RoadNode*>(currentNode);
                speed=road->MaxSpeed();
                length=road->Length();
            }
            else if(currentNode->getType()==NodeType::INTERSECTION)
            {
                IntersectionNode* intersection=dynamic_cast<IntersectionNode*>(currentNode);
                speed=intersection->getAverageSpeed();
                length=intersection->getStdLength();
            }
            timeForSegment=length/speed;

            maxTime+=timeForSegment;
        }
    }

    double averageTime=(totalTimeNeeded+maxTime)/2.0;
    return averageTime;
}
void Simulation::printAverageTime(std::ostream& out,Graph& graph,std::vector<Vehicle*> vectorOfVehicles)
{
    for(auto vehicle: vectorOfVehicles)
    {
        double avgTime=this->averageTime(graph,*vehicle);
        std::cout<<"Prosjecno vrijeme putovanja od "<<this->getNodeName(graph,vehicle->getStartID())<<" do "<<this->getNodeName(graph,vehicle->getGoalID())<<" iznosi: "<<avgTime<<std::endl;
    }
}