#include "scheme.h"
#include <iostream>

std::vector<double>* scheme::getResult() {return &result;}
std::vector<double>* scheme::getTimeStep() {return &timeStep;}

double CIR::nextStep(const double& deltaTime,const  double& deltaW) const {
  return std::abs((current + a*(b - current) * deltaTime + nu * std::sqrt(current * deltaTime) *deltaW));
}

double CIR::nextStep() {
  if (index == (int)timeStep.size()) {
    std::cerr << "nextStep() called while \"index\" was out of bound" << index << " " << (int)timeStep.size() << std::endl;
    return 0.0;
  }
  
  double deltaTime = timeStep[index], deltaW = V();
  current = nextStep(deltaTime, deltaW);
  result[index] = current;
  index += 1;
  return current;
}

void scheme::fullSimulation() {
  index = 0;
  while (index < (int)timeStep.size())
    {
      std::cerr << index << std::endl;
      nextStep();
    }
}


double heston::nextStep() {
  double sig = sigma.nextStep();
  double deltaTime = timeStep[index], deltaW = V();
  
  current = current + mu*deltaTime + std::sqrt(sig) * deltaW;
  result[index] = current;
  index ++;
  return current;
}
