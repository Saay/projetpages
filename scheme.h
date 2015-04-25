#ifndef SCHEME_H
#define SCHEME_H

#include <vector>
#include <cmath>
#include "randomvar.h"
#include <string>


class scheme {
 public:
 scheme(randomVar<>& V, const std::vector<double>& timeStep, std::vector<double> & result): V(V), timeStep(timeStep), result(result), index(0) {}
  
 scheme(randomVar<>& V, const std::vector<double>& timeStep): V(V), timeStep(timeStep) {
    result.resize(timeStep.size());
  };
  
  void fullSimulation(); 
  virtual double nextStep() = 0;
  void resetParameters();
  std::vector<double>*  getResult();
  std::vector<double> const *  getTimeStep() const ;
  bool isSimulationFinished() const;
  virtual std::string* getName();


 protected:
  std::string name;
  randomVar<>& V;
  std::vector<double> const & timeStep;
  std::vector<double> result;
  double current = 0.0;
  int index = 0;
  bool simulationFinished = false;
};


// Ornstein Ulhenbeck : dXt = a(b - Xt) dt + nu * sqrt(Xt)dWt
class CIR : public scheme {
 public:
 CIR(randomVar<>& V, double a, double b, double nu, const std::vector<double>& timeStep, std::vector<double>& result): scheme(V,timeStep,result), a(a),b(b),nu(nu) {}

 CIR(randomVar<>& V, const std::vector<double>& timeStep) : scheme(V,timeStep) {}

  double nextStep(const double& deltaTime, const double& deltaW) const; 
  virtual double nextStep();
  
  std::string* getName() {name.assign("CIR");return &name;}
 private:
  double a = 1.0,b = 0.5,nu = 0.5;
};


// Heston : dXt/Xt = mu*dt + sqrt(sigma)dWt avec with sigma ~ CIR, with possibly correlated browniens
class heston : public scheme {
 public:
 heston(randomVar<>& V, CIR& sigma, double mu, const std::vector<double>& timeStep, std::vector<double>& result) : scheme(V,timeStep,result), sigma(&sigma), mu(mu) {name.assign("Heston");}

 heston(randomVar<>& V, CIR& sig) : scheme(V,*sig.getTimeStep()), sigma(&(sig)) {name.assign("Heston");};

  
  std::string* getName() {name.assign("Heston");return &name;}
  virtual double nextStep();

 private:
  CIR* sigma;
  double mu = 1.0;
}; 

#endif
