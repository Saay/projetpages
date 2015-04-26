#include "scheme.h"
#include <iostream>

std::vector<double>*        scheme::getResult()    {return (&result);}
std::vector<double> const * scheme::getTimeStep() const {return (& timeStep);}
bool          scheme::isSimulationFinished() const {return simulationFinished;}
std::string * scheme::getName()                    {return &name;}
double        heston::getDrift()                   {return mu;}
double        scheme::getDrift()                   {return 0.0;}


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

void scheme::fullSimulation(bool asiatPayoff) {
  resetParameters();
  while (not simulationFinished)
    {
      nextStep();
    }
}

void scheme::resetParameters() {
  index = 0;
  current = x0;
  simulationFinished=false;
}

double heston::nextStep() {

  double sig = sigma->nextStep();
  double deltaTime = timeStep[index], deltaW = V();
  current = current + current*mu*deltaTime + current*std::sqrt(sig * deltaTime) * deltaW;
  result[index] = current;
  if (index == (int)timeStep.size() -1) {
    simulationFinished = true;
    index = 0;
  } else {
    index ++;
  }
  return current;
}

double hestonPP::retrieveSt(int time) {
  return 0.0;
}


void hestonPP::fullSimulation(bool asiatPayoff) {
  heston::fullSimulation();
  if (asiatPayoff) {
    for (int i = 0; i < (int)result.size();++i) {
      result[i] = retrieveSt(i);
   } 
  }else {
    result[result.size() -1] = retrieveSt(result.size()-1);
  } 
}
