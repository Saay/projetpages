#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <vector>
#include <cmath>
#include "scheme.h"

class monteCarlo {
 public:
 monteCarlo(scheme&S, bool saveResult = true): S(S), saveResult(saveResult) {};

  virtual double payoff(const std::vector<double>& path, const std::vector<double>& timeStep) = 0;
  double doSimulations(int nbSimulation);
  double doSimulationsWithPrecision(double precision, int maxIteration = 1000000);
  void oneStep();

  std::vector<double>* getRawResult();
  double               getConfidenceInterval();
 
  void setQuantile(double quant);

  void computeVariance();


 protected:
  double quantile = 2.0;
  scheme& S;
  double confidenceInterval = 1.0;
  double payoffResult = 0.0;
  double result = 0.0;
  int nbAlreadySimulated = 0;
  bool saveResult = true;
  std::vector<double> rawResult;
  double variance = 0.0;
};

class vanillePricing : public monteCarlo {
 public:
 vanillePricing(scheme& S, double strike = 0.5, bool saveResult = true): 
  monteCarlo(S,saveResult), K(strike) {};
  virtual double payoff(const std::vector<double>& path, const std::vector<double>& timeStep);

 private:
  double K;
};

class asiatPricing : public monteCarlo {
 public:
 asiatPricing(scheme& S, bool saveResult = true): monteCarlo(S,saveResult) {};
  virtual double payoff(const std::vector<double>& path, const std::vector<double>& timeStep);
};

#endif
