#ifndef SCHEME_H
#define SCHEME_H

#include <vector>
#include <cmath>
#include "randomvar.h"
#include <string>


class scheme {
 public:
  
 scheme(randomVar<>& V, std::vector<double>& timeStep): 
  V(V), timeStep(&timeStep) {
    result.resize(timeStep.size());
    brownien = new std::vector<double>;
  };
  
  ~scheme() {}

  virtual void fullSimulation(bool generateBrownien = true); 
  virtual double nextStep() = 0;
  

  void resetParameters();

  std::vector<double>*         getBrownien();
  std::vector<double>*         getResult();
  std::vector<double> *        getTimeStep();
  virtual std::string*         getName();
  virtual double               getDrift();
  randomVar<>*                 getRandomVar();
  virtual double               getRho();
  bool isSimulationFinished() const;


  virtual void setRho(double r);
  virtual void setTimeStep(std::vector<double>* Ts, std::vector<double>* Ts2 = NULL);
  virtual void setBrownien(std::vector<double>* w1, std::vector<double>* W2 = NULL);

 protected:
  randomVar<>& V;
  std::vector<double> * timeStep;
  std::vector<double> * brownien;
  std::vector<double> result;


  double current = 1.0;
  double x0 = 1.0;
  int index = 0;
  std::string name;

  double rho = 0.5;
  bool simulationFinished = false;
};


// CIR : dXt = a(b - Xt) dt + nu * sqrt(Xt)dWt
class CIR : public scheme {
 public:
 CIR(randomVar<>& V, double a, double b, double nu, 
     std::vector<double>& timeStep): 
  scheme(V,timeStep), a(a),b(b),nu(nu) {
    x0 = b;}

 CIR(randomVar<>& V, std::vector<double>& timeStep) : scheme(V,timeStep) {
    x0 = b;}

  double         nextStep(const double& deltaTime, const double& deltaW) const; 
  virtual double nextStep();
  

  std::string* getName() {name.assign("CIR");return &name;}
  double getA()  {return a;};
  double getB()  {return b;};
  double getNu() {return nu;};
  void   setA(double aa) {a = aa;}
  void   setB(double bb)  {b = bb;}
  void   setNu(double nunu) {nu = nunu;}
 private:
  double a = 1.0,b = 1.0,nu = 1.0;
};


// Heston : dXt/Xt = mu*dt + sqrt(sigma)dWt avec with sigma ~ CIR, with possibly correlated browniens
class heston : public scheme {
 public:
 heston(randomVar<>& V, CIR& sigma, double mu, 
	std::vector<double>& timeStep) : 
  scheme(V,timeStep), sigma(&sigma), mu(mu) {
    name.assign("Heston"); 
  }

 heston(randomVar<>& V, CIR& sig) : 
  scheme(V,*sig.getTimeStep()), sigma(&(sig)) {
    name.assign("Heston");
   };


  virtual void fullSimulation(bool generateBrownien = true); 
  virtual double nextStep();



  virtual void setBrownien(std::vector<double>* w1, std::vector<double>* W2 = NULL);
  virtual void setTimeStep(std::vector<double>* Ts, std::vector<double>* Ts2 = NULL);

  virtual double getDrift();
  void setDrift(double d) {mu = d;}
  virtual void resetParameters();
  CIR * getSigma() {return sigma;}

protected:  
  CIR* sigma;
  std::vector<double>* sigmaResult;
  double mu = 0.1;
}; 


//Heston as described in the paper of Panloup and Pagès.
class hestonPP : public heston {
 public: 
 hestonPP(randomVar<> & V, CIR & sigma, std::vector<double>& timeStep): 
  heston(V,sigma,-1.0, timeStep) {
    name.assign("HestonPP");
    x0 = 1.0;
  }

 hestonPP(randomVar<>& V, CIR& sig) : 
  heston(V,sig) {
    mu = 0.1;
    name.assign("HestonPP");
    x0 = 1.0;
  };

  virtual double nextStep();
  virtual void fullSimulation(bool generateBrownien = true);
  double retrieveSt(int time);
  void retrieveSt();


 private:
  double delta = 0.0;
  double intY = 0.0;
  double intSigma = 0.0;

};




#endif
