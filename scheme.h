#ifndef SCHEME_H
#define SCHEME_H

#include <vector>
#include <cmath>
#include "randomVar.h"

class scheme {
 public:
 scheme(randomVar V) : V(V) {}
 scheme(randomVar<> V, std::vector<double>& timeStep, std::vector<double> & result): V(V), timeStep(timeStep), result(result), index(0) {}
  
  virtual void fullSimulation() 
  virtual double nextStep(double deltaTime, double deltaW) const {return 0.0;}
  virtual double nextStep() {return 0.0;}
  

  
 private:
  randomVar<>& V;
  std::vector<double>& timeStep;
  std::vector<double>& result;
  double current;
  int index;
};


// Ornstein Ulhenbeck : dXt = (a - bXt) dt + nu * sqrt(Xt)dWt
class OU : scheme {
 OU(randomVar& V, double a, double b, double nu): scheme(V), a(a),b(b),nu(nu) {}


 private:
  double a,b,nu;
};


// Heston : dXt = mu*dt + sigmadWt avec with sigma ~ OU, with possibly correlated browniens
class heston : scheme {
 heston(randomVar<> V, scheme& sigma, double mu, std::vector<double>& timeStep, std::vector<double>& result) : scheme(V,timeStep,result), sigma(sigma), mu(mu) {}
 private:
  scheme sigma;
  double mu;
  
};

#endif
