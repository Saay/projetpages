#include "scheme.h"


double OU::nextStep(const double& deltaTime,const  double& deltaW) const {
  return (current + (a-b*current) * deltaTime + nu * std::sqrt(current * deltaTime) *deltaW);
}

double OU::nextStep() {
  if (index = timeStep.size()) {
    cerr << "nextStep() called while \"index\" was out of bound" << endl;
    return 0.0;
  }
  
  double deltaTime, deltaW;
  deltaTime = timeStep[index];
  deltaW = V();
  current = nextStep(deltaTime, deltaW);
  result[index] = current;
  index += 1;
  return current;
}

void scheme::fullSimulation() {
  while (index < timeStep.size())
    {
      nextStep();
    }
}
