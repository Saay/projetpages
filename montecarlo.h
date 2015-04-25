#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <vector>
#include <cmath>
#include "scheme.h"
#include "randomvar.h"

class monteCarlo {
 public:
 monteCarlo(scheme& S): S(S) {}
  virtual double payoff(const std::vector<double>& path, const std::vector<double>& timeStep) = 0;
  virtual double doSimulations(int nbSimulation);
  
  std::vector<double>* getRawResult();

    protected:
  scheme& S;
  double payoffResult = 0.0;
  double result = 0.0;
  int nbAlreadySimulated = 0;
  std::vector<double> rawResult;
  
};

class vanillePricing : public monteCarlo {
 public:
 vanillePricing(scheme& S): monteCarlo(S) {};
  virtual double payoff(const std::vector<double>& path, const std::vector<double>& timeStep);
};

class asiatPricing : public monteCarlo {
 public:

 asiatPricing(scheme& S): monteCarlo(S) {};
  virtual double payoff(const std::vector<double>& path, const std::vector<double>& timeStep);
};

#endif
