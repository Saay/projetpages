#include "montecarlo.h"



double monteCarlo::doSimulations(int n) {
  rawResult.resize(n);
  for (int i = 0; i<n; ++i) {
    S.fullSimulation();
    payoffResult = payoff(*(S.getResult()),*(S.getTimeStep()));
    rawResult[i] = payoffResult;
    result += payoffResult;
    nbAlreadySimulated ++;
  }
  return result/(double)n;
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
