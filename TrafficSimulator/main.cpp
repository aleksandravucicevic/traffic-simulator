#include <cstdio>
#include "Node.cpp"
#include "Graph.cpp"
#include "Vehicle.cpp"
#include "Simulation.cpp"

int main()
{
    LocationNode* A = new LocationNode(NodeType::LOCATION,"A");
    LocationNode* B = new LocationNode(NodeType::LOCATION,"B");
    LocationNode* C = new LocationNode(NodeType::LOCATION,"C");
    LocationNode* D = new LocationNode(NodeType::LOCATION,"D");

    RoadNode* roadToA = new RoadNode(NodeType::ROAD,"Put ka lokaciji A",340,80,5);
    RoadNode* roadFromA = new RoadNode(NodeType::ROAD,"Put od lokacije A",320,50,3);
    RoadNode* roadToB = new RoadNode(NodeType::ROAD,"Put ka lokaciji B",575,80,7);
    RoadNode* roadFromB = new RoadNode(NodeType::ROAD,"Put od lokacije B",220,25,4);
    RoadNode* roadToC = new RoadNode(NodeType::ROAD,"Put ka lokaciji C",456,40,8);
    RoadNode* roadFromC = new RoadNode(NodeType::ROAD,"Put od lokacije C",400,30,5);
    RoadNode* roadToD = new RoadNode(NodeType::ROAD,"Put ka lokaciji D",430,50,4);
    RoadNode* roadFromD = new RoadNode(NodeType::ROAD,"Put od lokacije D",620,60,6);
    RoadNode* roadBetweenIntersections = new RoadNode(NodeType::ROAD,"Put izmedju raskrsnica",150,40,3);

    IntersectionNode* I1 = new IntersectionNode(NodeType::INTERSECTION,3);
    IntersectionNode* I2 = new IntersectionNode(NodeType::INTERSECTION,3);

    A->setIncRoadID(roadToA->getID());
    A->setOutRoadID(roadFromA->getID());
    B->setIncRoadID(roadToB->getID());
    B->setOutRoadID(roadFromB->getID());
    C->setIncRoadID(roadToC->getID());
    C->setOutRoadID(roadFromC->getID());
    D->setIncRoadID(roadToD->getID());
    D->setOutRoadID(roadFromD->getID());

    roadToA->setStartNodeID(I1->getID());
    roadToA->setEndNodeID(A->getID());
    roadFromA->setStartNodeID(A->getID());
    roadFromA->setEndNodeID(I1->getID());
    roadToC->setStartNodeID(I1->getID());
    roadToC->setEndNodeID(C->getID());
    roadFromC->setStartNodeID(C->getID());
    roadFromC->setEndNodeID(I1->getID());
    roadToD->setStartNodeID(I1->getID());
    roadToD->setEndNodeID(D->getID());
    roadFromD->setStartNodeID(D->getID());
    roadFromD->setEndNodeID(I2->getID());
    roadToB->setStartNodeID(I1->getID());
    roadToB->setEndNodeID(B->getID());
    roadFromB->setStartNodeID(B->getID());
    roadFromB->setEndNodeID(I2->getID());
    roadBetweenIntersections->setStartNodeID(I2->getID());
    roadBetweenIntersections->setEndNodeID(I1->getID());

    I1->setStdLength(2.00);
    I2->setStdLength(3.00);
    I1->setAverageSpeed(50.00);
    I2->setAverageSpeed(50.00);
    I1->setCurrentNumOfVehiclesOnIntersection(0);
    I2->setCurrentNumOfVehiclesOnIntersection(0);
    I1->setRealSpeed();
    I2->setRealSpeed();

    I1->connectIncomingRoadToIntersection(roadFromA);
    I1->connectIncomingRoadToIntersection(roadFromC);
    I1->connectIncomingRoadToIntersection(roadBetweenIntersections);
    I1->connectOutgoingRoadToIntersection(roadToA);
    I1->connectOutgoingRoadToIntersection(roadToB);
    I1->connectOutgoingRoadToIntersection(roadToC);
    I1->connectOutgoingRoadToIntersection(roadToD);

    I2->connectIncomingRoadToIntersection(roadFromB);
    I2->connectIncomingRoadToIntersection(roadFromD);
    I2->connectOutgoingRoadToIntersection(roadBetweenIntersections);

    I1->addPairsOfConnectedRoads(roadFromA->getID(),roadToB->getID(),I1->getStdLength());
    I1->addPairsOfConnectedRoads(roadFromA->getID(),roadToC->getID(),I1->getStdLength());
    I1->addPairsOfConnectedRoads(roadFromA->getID(),roadToD->getID(),I1->getStdLength());
    I1->addPairsOfConnectedRoads(roadFromC->getID(),roadToA->getID(),I1->getStdLength());
    I1->addPairsOfConnectedRoads(roadFromC->getID(),roadToB->getID(),I1->getStdLength());
    I1->addPairsOfConnectedRoads(roadFromC->getID(),roadToC->getID(),I1->getStdLength());
    I1->addPairsOfConnectedRoads(roadFromC->getID(),roadToD->getID(),I1->getStdLength());
    I1->addPairsOfConnectedRoads(roadBetweenIntersections->getID(),roadToA->getID(),I1->getStdLength());
    I1->addPairsOfConnectedRoads(roadBetweenIntersections->getID(),roadToB->getID(),I1->getStdLength());
    I1->addPairsOfConnectedRoads(roadBetweenIntersections->getID(),roadToC->getID(),I1->getStdLength());
    I1->addPairsOfConnectedRoads(roadBetweenIntersections->getID(),roadToD->getID(),I1->getStdLength());

    I2->addPairsOfConnectedRoads(roadFromB->getID(),roadBetweenIntersections->getID(),I2->getStdLength());
    I2->addPairsOfConnectedRoads(roadFromD->getID(),roadBetweenIntersections->getID(),I2->getStdLength());
    
    Graph* trafficGraph = new Graph();
    trafficGraph->addNode(I1);
    trafficGraph->addNode(I2);
    trafficGraph->addNode(A);
    trafficGraph->addNode(B);
    trafficGraph->addNode(C);
    trafficGraph->addNode(D);
    trafficGraph->addNode(roadToA);
    trafficGraph->addNode(roadFromA);
    trafficGraph->addNode(roadToB);
    trafficGraph->addNode(roadFromB);
    trafficGraph->addNode(roadToC);
    trafficGraph->addNode(roadFromC);
    trafficGraph->addNode(roadToD);
    trafficGraph->addNode(roadFromD);
    trafficGraph->addNode(roadBetweenIntersections);

    const std::string fileName = "graf";
    trafficGraph->serialize(fileName);

    int numOfLocations, numOfIntersections=0;
    Graph* graph2 = new Graph();
    *graph2=graph2->deserialize("graf",numOfLocations,numOfIntersections);
    graph2->setNumOfLocations(numOfLocations);
    graph2->setNumOfIntersections(numOfIntersections);

    std::vector<IntersectionNode*> intersectionVector=trafficGraph->vectorOfIntersections();
    std::vector<std::vector<std::tuple<int,int,double>>> graphMatrix=trafficGraph->transformGraphToMatrix();

    Vehicle* vehicle1 = new Vehicle("auto1",*trafficGraph,A->getID(),C->getID());
    Vehicle* vehicle2 = new Vehicle("auto2",*trafficGraph,D->getID(),C->getID());
    Vehicle* vehicle3 = new Vehicle("auto3",*trafficGraph,C->getID(),B->getID());

    std::vector<Vehicle*> vectorOfVehicles;
    vectorOfVehicles.push_back(vehicle1);
    vectorOfVehicles.push_back(vehicle2);
    vectorOfVehicles.push_back(vehicle3);

    std::map<Vehicle*,std::vector<std::tuple<int,double,double,double,double>>> mapOfVehiclesForDistSim;
    std::map<Vehicle*,std::vector<std::tuple<int,double,double,double,double>>> mapOfVehiclesForTimeSim;

    for(auto vehicle: vectorOfVehicles)
    {
        vehicle->floydWarshall();
        vehicle->setVehicleInfoForDistSim();
        mapOfVehiclesForDistSim.emplace(vehicle,vehicle->getVehicleInfoForDistSim());
    }

    for(auto vehicle: vectorOfVehicles)
    {
        vehicle->setQuickestPath();
        vehicle->setVehicleInfoForTimeSim();
        mapOfVehiclesForTimeSim.emplace(vehicle,vehicle->getVehicleInfoForTimeSim());
    }

    Simulation simDistance(*trafficGraph,mapOfVehiclesForDistSim);
    Simulation simTime(*trafficGraph,mapOfVehiclesForTimeSim);

    std::string selector;
    do
    {    
        std::cout<<std::endl;
        std::cout << " ________________________________________________________________________________" <<std::endl;
        std::cout << "|                                                                                |" <<std::endl;
        std::cout << "|                             Izaberite jednu opciju:                            |" <<std::endl;
        std::cout << "|________________________________________________________________________________|" <<std::endl;
        std::cout << "|       [1] Izvrsenje simulacije        |     [2] Pregled saobracajne mreze      |" <<std::endl;
        std::cout << "|                                       |      u kojoj se odvija simulacija      |" <<std::endl;
        std::cout << "|_______________________________________|________________________________________|" <<std::endl;
        std::cout << "|          [3] Prikaz putanje           |              [4] Izlaz                 |" <<std::endl;
        std::cout << "|                vozila                 |                                        |" <<std::endl;
        std::cout << "|_______________________________________|________________________________________|" <<std::endl;
        std::cout<<std::endl;

        
        std::cin>>selector;
        if(selector=="1")
        {
            std::string selector2;
            do{
                std::cout<<std::endl;
                std::cout<< " ___________________________________________________________________" <<std::endl;
                std::cout<< "|                  Simulaciju odraditi tako da se...                |" <<std::endl;
                std::cout<< "|___________________________________________________________________|" <<std::endl;
                std::cout<< "|     [1] Minimizuje distanca     |     [2] Minimizuje vrijeme      |" <<std::endl;
                std::cout<< "|_________________________________|_________________________________|" <<std::endl;
                std::cout<<std::endl;
                    
                std::cin>>selector2;

                Simulation::setSimCounterToZero();

                if(selector2=="1")
                {
                    std::string selector3;
                    do{
                        std::cout<<std::endl;
                        std::cout << " ________________________________________________________________________________" <<std::endl;
                        std::cout << "|                                                                                |" <<std::endl;
                        std::cout << "|                             Izaberite jednu opciju:                            |" <<std::endl;
                        std::cout << "|________________________________________________________________________________|" <<std::endl;
                        std::cout << "|          [1] Izvrsenje jednog         |          [2] Prikaz trenutnog          |" <<std::endl;
                        std::cout << "|           koraka simulacije           |               stanja vozila            |" <<std::endl;
                        std::cout << "|_______________________________________|________________________________________|" <<std::endl;
                        std::cout << "|        [3] Prikaz prosjecnog          |               [4] Izlaz                |" <<std::endl;
                        std::cout << "|           vremena putovanja           |                                        |" <<std::endl;
                        std::cout << "|_______________________________________|________________________________________|" <<std::endl;
                        std::cout<<std::endl;

                        std::cin>>selector3;
                        if(selector3=="1")
                        {
                            if(!simDistance.isSimulationOver())
                            {
                                simDistance.doOneStepOfSimulation();
                            }
                            else
                            {
                                std::cout<<"Simulacija je zarsena."<<std::endl;
                            }
                        }
                        else if(selector3=="2")
                        {
                            simDistance.currentPositionOfVehicles(std::cout);
                        }
                        else if(selector3=="3")
                        {
                            simDistance.printAverageTime(std::cout,*trafficGraph,vectorOfVehicles);
                        }
                        else if(selector3!="4")
                        {
                            std::cout<<"Nevalidan unos."<<std::endl;
                        }
                    }while(selector3!="4");
                
                    
                }
                else if(selector2=="2")
                {
                    std::string selector3;
                    do{
                        std::cout<<std::endl;
                        std::cout << " ________________________________________________________________________________" <<std::endl;
                        std::cout << "|                                                                                |" <<std::endl;
                        std::cout << "|                             Izaberite jednu opciju:                            |" <<std::endl;
                        std::cout << "|________________________________________________________________________________|" <<std::endl;
                        std::cout << "|          [1] Izvrsenje jednog         |          [2] Prikaz trenutnog          |" <<std::endl;
                        std::cout << "|           koraka simulacije           |               stanja vozila            |" <<std::endl;
                        std::cout << "|_______________________________________|________________________________________|" <<std::endl;
                        std::cout << "|        [3] Prikaz prosjecnog          |               [4] Izlaz                |" <<std::endl;
                        std::cout << "|           vremena putovanja           |                                        |" <<std::endl;
                        std::cout << "|_______________________________________|________________________________________|" <<std::endl;
                        std::cout<<std::endl;

                        std::cin>>selector3;
                        if(selector3=="1")
                        {
                            if(!simTime.isSimulationOver())
                            {
                                simTime.doOneStepOfSimulation();
                            }
                            else
                            {
                                std::cout<<"Simulacija je zarsena."<<std::endl;
                            }
                        }
                        else if(selector3=="2")
                        {
                            simTime.currentPositionOfVehicles(std::cout);
                        }
                        else if(selector3=="3")
                        {
                            simTime.printAverageTime(std::cout,*trafficGraph,vectorOfVehicles);
                        }
                        else if(selector3!="4")
                        {
                            std::cout<<"Nevalidan unos."<<std::endl;
                        }
                    }while(selector3!="4");
                }
                else
                {
                    std::cout<<"Nevalidan unos."<<std::endl;
                }
            }while(selector2!="1" && selector2!="2");
        }
        else if(selector=="2")
        {
            std::cout<<std::endl<<"_____________________________________________________"<<std::endl;
            graph2->printGraphMatrix(std::cout,graphMatrix);
            std::cout<<"_____________________________________________________"<<std::endl;

            for(auto intersection: intersectionVector)
            {
                std::cout<<"_____________________________________________________"<<std::endl;
                intersection->printIntersectionMatrix(std::cout,intersection->transformIntersectionToMatrix());
            }
            std::cout<<"_____________________________________________________"<<std::endl;
        }
        else if(selector=="3")
        {
            for(auto vehicle: vectorOfVehicles)
            {
                std::cout<<std::endl<<"__________________________________________________________________________________________________________________________________________________________________________________"<<std::endl;
                std::cout<<"Vozilo "<<vehicle->getName()<<":"<<std::endl;
                std::cout<<"[po distanci]: "<<std::endl;
                vehicle->printPathD(std::cout,*trafficGraph);
                std::cout<<std::endl<<"[po vremenu]: "<<std::endl;
                vehicle->printPathT(std::cout,*trafficGraph);
            }
            std::cout<<std::endl<<"__________________________________________________________________________________________________________________________________________________________________________________"<<std::endl;
        }  
        else if(selector!="4")
            std::cout<<"Nevalidan unos.";
    }while(selector!="4");

    return 0;
}