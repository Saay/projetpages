#ifndef SCHEME_H
#define SCHEME_H

#include <vector>
#include <cmath>
#include "randomvar.h"

class scheme {
 public:
 scheme(randomVar<>& V, std::vector<double>& timeStep, std::vector<double> & result): V(V), timeStep(timeStep), result(result), index(0) {}
  
 scheme(randomVar<>& V, std::vector<double>& timeStep): V(V), timeStep(timeStep) {
    result.resize(timeStep.size());
  };
  
  void fullSimulation(); 
  virtual double nextStep() = 0;
  
  std::vector<double>*  getResult();
  std::vector<double>*  getTimeStep();
  
 protected:
  randomVar<>& V;
  std::vector<double>& timeStep;
  std::vector<double> result;
  double current = 0.0;
  int index = 0;
};


// Ornstein Ulhenbeck : dXt = a(b - Xt) dt + nu * sqrt(Xt)dWt
class CIR : public scheme {
 public:
 CIR(randomVar<>& V, double a, double b, double nu, std::vector<double>& timeStep, std::vector<double>& result): scheme(V,timeStep,result), a(a),b(b),nu(nu) {}

 CIR(randomVar<>& V, std::vector<double>& timeStep) : scheme(V,timeStep) {}

  virtual double nextStep(const double& deltaTime, const double& deltaW) const; 
  virtual double nextStep();
  

 private:
  double a = 1.0,b = 0.5,nu = 0.5;
};


// Heston : dXt = mu*dt + sigmadWt avec with sigma ~ CIR, with possibly correlated browniens
class heston : public scheme {
 public:
 heston(randomVar<>& V, CIR& sigma, double mu, std::vector<double>& timeStep, std::vector<double>& result) : scheme(V,timeStep,result), sigma(sigma), mu(mu) {}

 heston(randomVar<>& V, CIR& sigma) : scheme(V,*sigma.getTimeStep()), sigma(sigma) {};
 
  virtual double nextStep();

 private:
  CIR& sigma;
  double mu = 1.0;
  
}; 

#endif
