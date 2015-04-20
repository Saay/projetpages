#include "montecarlo.h"



double monteCarlo::nSimulations(int n) {
  for (int i = 0; i<n; ++i) {
    S.fullSimulation();
    result += payoff(*(S.getResult()),*(S.getTimeStep()));
  }
  return result;
}


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
