#include "montecarlo.h"


double monteCarlo::doSimulations(int n) {
  if (saveResult) {
    rawResult.resize(n);
  }
  result = 0.0;
  nbAlreadySimulated = 0;
  for (int i = 0; i<n; ++i) {
    oneStep();
  }
  return result/(double)n;
}

inline void monteCarlo::oneStep() {
  S.fullSimulation();
  payoffResult = payoff(*(S.getResult()),*(S.getTimeStep()));
  result += payoffResult;

  if (saveResult) {
    rawResult[nbAlreadySimulated] = payoffResult;
  }
  nbAlreadySimulated ++;
}



std::vector<double>* monteCarlo::getRawResult() {return &rawResult;}


double vanillePricing::payoff(const std::vector<double>& path, const std::vector<double>& timeStep) {
  payoffResult = path[path.size()-1];
  return payoffResult;
}

double asiatPricing::payoff(const std::vector<double>& path, const std::vector<double>& timeStep) {
  double result = 0.0;
  for (int i = 0; i < (int)path.size(); ++i) {
    result += path[i] * timeStep[i];
  }
  payoffResult = result;
  return payoffResult;
}
