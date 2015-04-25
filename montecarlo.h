#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <vector>
#include <cmath>
#include "scheme.h"
#include "randomvar.h"

class monteCarlo {
 public:
 monteCarlo(scheme&S, bool saveResult = true): S(S), saveResult(saveResult) {};

  virtual double payoff(const std::vector<double>& path, const std::vector<double>& timeStep) = 0;
  double doSimulations(int nbSimulation);
  void oneStep();
  std::vector<double>* getRawResult();

  double computeVariance();

 protected:
  scheme& S;
  double payoffResult = 0.0;
  double result = 0.0;
  int nbAlreadySimulated = 0;
  bool saveResult = true;
  std::vector<double> rawResult;
  double variance = 0.0;
};

class vanillePricing : public monteCarlo {
 public:
 vanillePricing(scheme& S, bool saveResult = true): monteCarlo(S,saveResult) {};
  virtual double payoff(const std::vector<double>& path, const std::vector<double>& timeStep);
};

class asiatPricing : public monteCarlo {
 public:

 asiatPricing(scheme& S, bool saveResult = true): monteCarlo(S,saveResult) {};
  virtual double payoff(const std::vector<double>& path, const std::vector<double>& timeStep);
};

#endif
