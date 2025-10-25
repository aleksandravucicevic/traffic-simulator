#pragma once
#include "Graph.h"
#include "Vehicle.h"

class ISimulation
{
    public:
    virtual std::map<Vehicle*,std::pair<int,std::string>> doOneStepOfSimulation() = 0;
    virtual bool isSimulationOver() = 0;
    virtual void currentPositionOfVehicles(std::ostream&) = 0;
    virtual double averageTime(Graph&,Vehicle&) = 0;

    static constexpr double SIMULATION_CONSTANT=0.2;
};