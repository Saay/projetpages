#include "scheme.h"
#include <iostream>

std::vector<double>* scheme::getResult() {return (&result);}
std::vector<double> const * scheme::getTimeStep() const {return (& timeStep);}
bool scheme::isSimulationFinished() const {return simulationFinished;}
std::string * scheme::getName() {return &name;}
double CIR::nextStep(const double& deltaTime,const  double& deltaW) const {
  return std::abs((current + a*(b - current) * deltaTime + nu * std::sqrt(current * deltaTime) *deltaW));
}

double CIR::nextStep() {
  
  double deltaTime = timeStep[index], deltaW = V();
  current = nextStep(deltaTime, deltaW);
  result[index] = current;
  if (index == (int)timeStep.size() -1) {
    simulationFinished = true;
    index = 0;
  } else {
    index += 1;
  }
  return current;
}

void scheme::fullSimulation() {
  resetParameters();
  while (not simulationFinished)
    {
      nextStep();
    }
}

void scheme::resetParameters() {
  index = 0;
  current = 0.0;
  simulationFinished=false;
}

double heston::nextStep() {

  double sig = sigma->nextStep();
  double deltaTime = timeStep[index], deltaW = V();
  
  current = current + mu*deltaTime + std::sqrt(sig) * deltaW;
  result[index] = current;
  if (index == (int)timeStep.size() -1) {
    simulationFinished = true;
    index = 0;
  } else {
    index ++;
  }
  return current;
}


