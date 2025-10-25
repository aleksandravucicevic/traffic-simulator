#include "Graph.h"

Graph::~Graph()
{
    for(auto& pair: nodes)
        delete pair.second.second;
}

void Graph::addNodeToNeighborhood(int currentNodeID,int prevNodeID,int nextNodeID,double currentNodeLen,double currentNodeSpeed)
{
    this->neighbors.emplace(currentNodeID,std::make_tuple(prevNodeID,nextNodeID,currentNodeLen,currentNodeSpeed));
}

void Graph::addNode(Node* node)
{
    nodes.emplace(node->getID(), std::make_pair(node->getType(),node));

    int prevNodeID, nextNodeID;
    double currentNodeLen,currentNodeSpeed;
    if(node->getType()==NodeType::LOCATION)
    {
        this->numLocations++;
        LocationNode* location=dynamic_cast<LocationNode*>(node);
        int incRoadID=location->getIncRoadID();
        int outRoadID=location->getOutRoadID();

        this->addNodeToNeighborhood(location->getID(),incRoadID,outRoadID,0.0,0.0);
    }
    else if(node->getType()==NodeType::ROAD)
    {
        RoadNode* currentRoad=dynamic_cast<RoadNode*>(node);
        prevNodeID=currentRoad->getStartNodeID();
        nextNodeID=currentRoad->getEndNodeID();
        currentNodeLen=currentRoad->Length();
        currentNodeSpeed=currentRoad->MaxSpeed();
        this->addNodeToNeighborhood(currentRoad->getID(),prevNodeID,nextNodeID,currentNodeLen,currentNodeSpeed);
    }
    else if(node->getType()==NodeType::INTERSECTION)
    {
        this->numIntersections++;
        IntersectionNode* currentIntersection=dynamic_cast<IntersectionNode*>(node);
        currentNodeSpeed=currentIntersection->getAverageSpeed();
        std::vector<RoadNode*> incRoads=currentIntersection->getIncomingRoads();
        std::vector<RoadNode*> outRoads=currentIntersection->getOutgoingRoads();

        for(auto& incRoad: incRoads)
        {
            int incRoadID=incRoad->getID();
            for(auto& outRoad: outRoads)
            {
                int outRoadID=outRoad->getID();
                double lenBtwRoads=currentIntersection->getLengthBetweenRoads(incRoadID,outRoadID);
                this->addNodeToNeighborhood(currentIntersection->getID(),incRoadID,outRoadID,lenBtwRoads,currentNodeSpeed);
            }
        }
    }
}

Node* Graph::findNodeByID(int idx)
{
    return nodes.at(idx).second;
}
const Node* Graph::findNodeByID(int idx) const
{
    return nodes.at(idx).second;
}

int Graph::getNumLocations() const
{
    return this->numLocations;
}
int Graph::getNumIntersections() const
{
    return this->numIntersections;
}
std::map<int, std::pair<int,Node*>> Graph::getNodes() const
{
    return this->nodes;
}
std::multimap<int,std::tuple<int,int,double,double>> Graph::getNeighbors() const
{
    return this->neighbors;
}
void Graph::setNumOfLocations(int numOfLocs)
{
    this->numLocations=numOfLocs;
}
void Graph::setNumOfIntersections(int numOfInters)
{
    this->numIntersections=numOfInters;
}
std::vector<Node*> Graph::vectorOfLocationsAndIntersections() const
{
    int n=this->getNumLocations()+this->getNumIntersections();
    std::vector<Node*> vectorOfLocationsAndIntersections;

    for(const auto& nd: nodes)
    {
        Node* node=nd.second.second;
        if(node->getType()==NodeType::LOCATION || node->getType()==NodeType::INTERSECTION)
        {
            vectorOfLocationsAndIntersections.emplace_back(node);
        }
    }

    return vectorOfLocationsAndIntersections;
}
std::vector<LocationNode*> Graph::vectorOfLocations() const
{
    int locs=this->getNumLocations();
    std::vector<LocationNode*> locations;

    for(const auto& nd: nodes)
    {
        Node* node=nd.second.second;
        if(node->getType()==NodeType::LOCATION)
        {
            locations.emplace_back((LocationNode*)node);
        }
    }

    return locations;
}
std::vector<IntersectionNode*> Graph::vectorOfIntersections() const
{
    int inters=this->getNumIntersections();
    std::vector<IntersectionNode*> intersections;

    for(const auto& nd: nodes)
    {
        Node* node=nd.second.second;
        if(node->getType()==NodeType::INTERSECTION)
        {
            intersections.emplace_back((IntersectionNode*)node);
        }
    }

    return intersections;
}

int Graph::findNodeInVector(std::vector<Node*> vectorOfLocationsAndIntersections,const Node* node) const
{
    int idx=0;
    int size=vectorOfLocationsAndIntersections.size();

    for(const auto& n: vectorOfLocationsAndIntersections)
    {
        if(n->getID()==node->getID())
        {
            if(idx<size)
                return idx;
        }
        else
            idx++;
    }
    
    return -1;
}
int Graph::findNodeInVector(std::vector<LocationNode*> vectorOfLocations,const Node* node) const
{
    int idx=0;
    int size=vectorOfLocations.size();

    if(node->getType()!=NodeType::LOCATION)
    {
        return -1;
    }

    for(const auto& n: vectorOfLocations)
    {
        if(n->getID()==node->getID())
        {
            if(idx<size)
                return idx;
        }
        else
            idx++;
    }
    
    return -1;
}
std::vector<std::vector<std::tuple<int,int,double>>> Graph::transformGraphToMatrix() const
{
    int n=this->getNumLocations()+this->getNumIntersections();
    std::vector<Node*> vectorOfLocationsAndIntersections=this->vectorOfLocationsAndIntersections();

    std::tuple init=std::make_tuple(-1,-1,std::numeric_limits<double>::infinity());
    std::vector<std::vector<std::tuple<int,int,double>>> graphMatrix(n,std::vector<std::tuple<int,int,double>>(n,init));

    for(const auto& pair: nodes)
    {
        Node* node=pair.second.second;
        if(RoadNode* road=dynamic_cast<RoadNode*>(node))
        {
            int startID=road->getStartNodeID();
            int endID=road->getEndNodeID();
            
            const Node* startNode=this->findNodeByID(startID);
            const Node* endNode=this->findNodeByID(endID);

            int startIdx=this->findNodeInVector(vectorOfLocationsAndIntersections,startNode);
            int endIdx=this->findNodeInVector(vectorOfLocationsAndIntersections,endNode);

            graphMatrix[startIdx][endIdx]=std::make_tuple(startID,endID,road->Length());
        }
    }

    return graphMatrix;
}
void Graph::printGraphMatrix(std::ostream& out,std::vector<std::vector<std::tuple<int,int,double>>> matrix) const
{
    int n=this->getNumLocations()+this->getNumIntersections();
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            out<<std::setw(8)<<std::left<<std::fixed<<std::setprecision(2)<<std::get<2>(matrix[i][j])<<" ";
        }
        out<<std::endl;
    }
}

void Graph::serialize(const std::string& fileName)
{
    std::ofstream file(fileName);
    file<<this->getNumLocations()<<","<<this->getNumIntersections()<<std::endl;
    for(auto& pair : nodes)
    {
        Node* node=pair.second.second;
        if(LocationNode* locNode=dynamic_cast<LocationNode*>(node))
            locNode->print(file);
        else if(RoadNode* roadNode=dynamic_cast<RoadNode*>(node))
            roadNode->print(file);
        else if(IntersectionNode* interNode=dynamic_cast<IntersectionNode*>(node))
            interNode->print(file);
    }
    file.close();
}

Graph Graph::deserialize(const std::string& fileName,int& numOfLocations,int& numOfIntersections)
{
    Graph graph;
    std::ifstream file(fileName);

    std::string line;

    std::getline(file,line);
    std::istringstream iss(line);
    std::string numOfLocationsStr, numOfIntersectionsStr;
    if(std::getline(iss,numOfLocationsStr,',') && std::getline(iss,numOfIntersectionsStr))
    {
        numOfLocations=std::stoi(numOfLocationsStr);
        numOfIntersections=std::stoi(numOfIntersectionsStr);
    }
    
    while(std::getline(file,line))
    {
        std::istringstream iss(line);
        std::string typeOfNode, nodeName, IDStr;
        int nodeID, nodeType;

        if(std::getline(iss,typeOfNode,',') && std::getline(iss,nodeName,',') && std::getline(iss,IDStr))
        {
            nodeType=std::stoi(typeOfNode);
            nodeID=std::stoi(IDStr);

            if(nodeType==0)
            {
                LocationNode* locNode=new LocationNode(NodeType::LOCATION,nodeID,nodeName);
                
                std::string incRoadIDStr, outRoadIDStr;
                if(std::getline(file,line))
                {
                    std::istringstream iss(line);
                    if(std::getline(iss,incRoadIDStr,',') && std::getline(iss,outRoadIDStr))
                    {
                        int incRoadID=std::stoi(incRoadIDStr);
                        int outRoadID=std::stoi(outRoadIDStr);

                        locNode->setIncRoadID(incRoadID);
                        locNode->setOutRoadID(outRoadID);
                    }
                }
                    
                graph.addNode(locNode);
            }

            else if(nodeType==1)
            {
                std::string startID, endID, lengthStr, maxSpeedStr, maxVehiclesStr;
                if(std::getline(file,line))
                {
                    std::istringstream iss(line);
                    if(std::getline(iss,startID,',') && std::getline(iss,endID,',') && std::getline(iss, lengthStr,',') && std::getline(iss, maxSpeedStr,',') && std::getline(iss, maxVehiclesStr))
                    {
                        int startNodeID=std::stoi(startID);
                        int endNodeID=std::stoi(endID);
                        double length=std::stod(lengthStr);
                        double maxSpeed=std::stod(maxSpeedStr);
                        int maxVehicles = std::stoi(maxVehiclesStr);
                        RoadNode* roadNode=new RoadNode(NodeType::ROAD,nodeID,nodeName,startNodeID,endNodeID,length,maxSpeed,maxVehicles);
                        graph.addNode(roadNode);
                    }
                }
            }

            else if(nodeType==2)
            {
                int numOfVehicles, numOfRoads, numOfPairs;
                std::string info, numOfVehiclesStr, incRoadStr, outRoadStr, lengthStr, speedStr, numOfRoadsStr, numOfPairsStr;

                if(std::getline(file,line))
                {
                    std::istringstream iss(line);
                    if(std::getline(iss,numOfVehiclesStr))
                    {
                        numOfVehicles=std::stoi(numOfVehiclesStr);
                        IntersectionNode* interNode=new IntersectionNode(NodeType::INTERSECTION,nodeID,numOfVehicles);

                        if(std::getline(file,line))
                        {
                            std::istringstream iss(line);
                            if(std::getline(iss,numOfRoadsStr))
                            {
                                numOfRoads=std::stoi(numOfRoadsStr);
                                int br=0;
                                while(br<numOfRoads)
                                {
                                    if(std::getline(file,line))
                                    {
                                        std::istringstream iss(line);
                                        if(std::getline(iss,info,',') && std::getline(iss,nodeName,',') && std::getline(iss,IDStr))
                                        {
                                            nodeID=stoi(IDStr);
                                            if(info=="inc")
                                                interNode->connectIncomingRoadToIntersection((RoadNode*)graph.findNodeByID(nodeID));
                                            else if(info=="out")
                                                interNode->connectOutgoingRoadToIntersection((RoadNode*)graph.findNodeByID(nodeID));
                                        }
                                    }
                                    br++;
                                }

                                if(std::getline(file,line))
                                {
                                    std::istringstream iss(line);
                                    if(std::getline(iss,numOfPairsStr))
                                    {
                                        numOfPairs=std::stoi(numOfPairsStr);
                                        int br=0;
                                        while(br<numOfPairs)
                                        {
                                            if(std::getline(file,line))
                                            {
                                                std::istringstream iss(line);
                                                if(std::getline(iss,incRoadStr,',') && std::getline(iss,outRoadStr,',') && std::getline(iss,lengthStr))
                                                {
                                                    int incRoadID=std::stoi(incRoadStr);
                                                    int outRoadID=std::stoi(outRoadStr);
                                                    double length=std::stod(lengthStr);

                                                    interNode->addPairsOfConnectedRoads(incRoadID,outRoadID,length);
                                                }
                                            }
                                            br++;
                                        }
                                    }
                                }
                            }
                        }

                        graph.addNode(interNode);
                    }
                }
            }
        }
    }
    file.close();
    return graph;
}