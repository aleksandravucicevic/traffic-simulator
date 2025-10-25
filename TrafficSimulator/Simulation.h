#pragma once
#include "ISimulation.h"

class Simulation: virtual public ISimulation
{
    //used for saving info about simulation (per step)
    std::map<Vehicle*,std::vector<std::pair<int,std::string>>> simInfo;
    static int simulationCounter;
    int numOfStepsInSimulation;

    public:
    Simulation(Graph&,std::map<Vehicle*,std::vector<std::tuple<int,double,double,double,double>>>&);

    virtual std::map<Vehicle*,std::pair<int,std::string>> doOneStepOfSimulation() override;
    virtual bool isSimulationOver() override;
    virtual void currentPositionOfVehicles(std::ostream&) override;
    virtual double averageTime(Graph&,Vehicle&) override;

    static void setSimCounterToZero();
    void setSimInfo(Graph&,std::map<Vehicle*,std::vector<std::tuple<int,double,double,double,double>>>&,int&);
    void printAverageTime(std::ostream&,Graph&,std::vector<Vehicle*>);

    int simSteps() const;

    private:
    std::string getNodeName(Graph&,int);
};