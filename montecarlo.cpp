#include "montecarlo.h"
#include <iostream>

void monteCarlo::setQuantile(double quant) {quantile=quant;}
std::vector<double>* monteCarlo::getRawResult() {return &rawResult;}



double monteCarlo::doSimulations(int n) {
  if (saveResult && n >= (int)rawResult.size()) {
    rawResult.resize(n);
  }
  result = 0.0;
  nbAlreadySimulated = 0;
  for (int i = 0; i<n; ++i) {
    oneStep();
  }
  return result/(double)n;
}


double monteCarlo::doSimulationsWithPrecision(double precision, int maxIteration) {
  int batchSize = 1000;
  result = 0.0;
  nbAlreadySimulated = 0;
  saveResult = true;
  oneStep();
  do {
    for (int i = 0; i < batchSize; ++i) {
    oneStep();
    }
    computeVariance();
    confidenceInterval = quantile*std::sqrt(variance/nbAlreadySimulated);
  } while (confidenceInterval  > precision && (nbAlreadySimulated < maxIteration));
  return result/ (double) nbAlreadySimulated;
}

inline void monteCarlo::oneStep() {
  S.fullSimulation();
  payoff(*(S.getResult()),*(S.getTimeStep()));
  result += payoffResult;

  if (saveResult) {
    if (nbAlreadySimulated < (int)rawResult.size())
      rawResult[nbAlreadySimulated] = payoffResult;
    else {
      rawResult.push_back(payoffResult);
    }
  }
  nbAlreadySimulated ++;
}

void monteCarlo::computeVariance() {
  double mean = result / (double)nbAlreadySimulated;
  double var = 0.0;
  for (int i = 0; i < nbAlreadySimulated; ++i) {
    var += (rawResult[i] - mean)*(rawResult[i] - mean);
  }
  variance = var / ((double) nbAlreadySimulated -1);
}



double vanillePricing::payoff(const std::vector<double>& path, const std::vector<double>& timeStep) {
  //TODO caluler t et le remplacer dans l'exponetiel
  payoffResult = std::exp(-S.getDrift() * 1) * std::max(path[path.size()-1]-K,0.0);
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


