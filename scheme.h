#ifndef SCHEME_H
#define SCHEME_H

#include <vector>
#include <cmath>
#include "randomvar.h"
#include <string>


class scheme {
 public:
 scheme(randomVar<>& V, const std::vector<double>& timeStep, 
	std::vector<double> & result): 
  V(V), timeStep(timeStep), result(result), index(0) {}
  
 scheme(randomVar<>& V, const std::vector<double>& timeStep): 
  V(V), timeStep(timeStep) {
    result.resize(timeStep.size());
  };
  
  virtual void fullSimulation(bool asiatPayoff=false); 
  virtual double nextStep() = 0;
  

  void resetParameters();
  std::vector<double>*         getResult();
  std::vector<double> const *  getTimeStep() const ;
  virtual std::string*         getName();
  virtual double               getDrift();

  bool isSimulationFinished() const;


 protected:
  randomVar<>& V;
  std::vector<double> const & timeStep;
  std::vector<double> result;


  double current = 1.0;
  double x0 = 1.0;
  int index = 0;
  std::string name;

  bool simulationFinished = false;
};


// CIR : dXt = a(b - Xt) dt + nu * sqrt(Xt)dWt
class CIR : public scheme {
 public:
 CIR(randomVar<>& V, double a, double b, double nu, 
     const std::vector<double>& timeStep, std::vector<double>& result): 
  scheme(V,timeStep,result), a(a),b(b),nu(nu) {}

 CIR(randomVar<>& V, const std::vector<double>& timeStep) : scheme(V,timeStep) {}

  double         nextStep(const double& deltaTime, const double& deltaW) const; 
  virtual double nextStep();
  
  std::string* getName() {name.assign("CIR");return &name;}
  double getA()  {return a;};
  double getB()  {return b;};
  double getNu() {return nu;};

 private:
  double a = 1.0,b = 0.5,nu = 0.5;
};


// Heston : dXt/Xt = mu*dt + sqrt(sigma)dWt avec with sigma ~ CIR, with possibly correlated browniens
class heston : public scheme {
 public:
 heston(randomVar<>& V, CIR& sigma, double mu, 
	const std::vector<double>& timeStep, std::vector<double>& result) : 
  scheme(V,timeStep,result), sigma(&sigma), mu(mu) {
    name.assign("Heston"); 
  }

 heston(randomVar<>& V, CIR& sig) : 
  scheme(V,*sig.getTimeStep()), sigma(&(sig)) {
    name.assign("Heston");
   };

  
  virtual double nextStep();

  virtual double getDrift();
  virtual void resetParameters();
  CIR * getSigma() {return sigma;}
protected:
  CIR* sigma;
  double mu = 0.1;
}; 


//Heston as described in the paper of Panloup and Pagès.
class hestonPP : public heston {
 public: 
 hestonPP(correlGaussian<> & V, CIR & sigma, const std::vector<double>& timeStep,
	  std::vector<double>& result): 
  heston(V,sigma,-1.0, timeStep,result), V(V) {
    name.assign("HestonPP");
  }
 hestonPP(correlGaussian<>& V, CIR& sig) : 
  heston(V,sig), V(V) {
    mu = 0.1;
    name.assign("HestonPP");
  };
  virtual double nextStep();
  virtual void fullSimulation(bool asiatPayoff=false);
  double retrieveSt(int time);
  void retrieveSt();
 private:
  correlGaussian<> & V;
  double delta = 0.0;
  double intY = 0.0;
  double intSigma = 0.0;

};




#endif
