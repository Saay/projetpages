#include "scheme.h"
#include <iostream>
#include "utility.h"
#include <cmath>

std::vector<double>*        scheme::getResult()    {return (&result);}
std::vector<double>*        scheme::getBrownien()  {return (brownien);}
std::vector<double>*        scheme::getTimeStep()  {return (timeStep);}
bool          scheme::isSimulationFinished() const {return simulationFinished;}
std::string * scheme::getName()                    {return &name;}
double        heston::getDrift()                   {return mu;}
double        scheme::getRho()                     {return rho;}
double        scheme::getDrift()                   {return 0.0;}
randomVar<> * scheme::getRandomVar()               {return &V;}

void          scheme::setRho(double r) {rho = r;}
void          scheme::setTimeStep(std::vector<double>* Ts,
				  std::vector<double>* Ts2) {
  timeStep = Ts;
}
void          scheme::setBrownien(std::vector<double>* w1, 
				  std::vector<double>* w2){
  brownien = w1;
}


void          heston::setTimeStep(std::vector<double>* Ts,
				  std::vector<double>* Ts2) {
  timeStep = Ts;
  sigma->setTimeStep(Ts2);
}

double CIR::nextStep(const double& deltaTime,const  double& deltaW) const {
  return std::abs((current + a*(b - current) * deltaTime + nu * std::sqrt(current * deltaTime) *deltaW));
}


double CIR::nextStep() {
  double deltaTime = (*timeStep)[index], deltaW = (*brownien)[index];
  current = nextStep(deltaTime, deltaW);
  result[index] = current;
  if (index == (int)timeStep->size() -1) {
    simulationFinished = true;
    index = 0;
  } else {
    index += 1;
  }
  return current;
}


void scheme::fullSimulation(bool generateBrownien) {

  resetParameters();

  if (generateBrownien) {
    V.generateArray(*brownien, timeStep->size());
  }
  while (not simulationFinished)  {
      nextStep();
    }
}

void heston::fullSimulation(bool generateBrownien) {
  resetParameters();

  sigma->fullSimulation(generateBrownien);
  
  sigmaResult = sigma->getResult();
  if (generateBrownien) {
    V.generateArray(*brownien, timeStep->size());
    utl::correlateGaussian(*(sigma->getBrownien()), *brownien, rho);
  }

    while (not simulationFinished)
    {
      nextStep();
    }
}


void scheme::resetParameters() {
  index = 0;
  current = x0;
  simulationFinished=false;
  if (result.size() < timeStep->size()) {result.resize(timeStep->size());}
  if (brownien->size() < timeStep->size()) {brownien->resize(timeStep->size());}
}

void heston::resetParameters() {
  sigma->resetParameters();
  scheme::resetParameters();
}

double heston::nextStep() {

  double sig = (*sigmaResult)[index];

  double deltaTime = (*timeStep).at(index), deltaW = (*brownien).at(index);
  current = current + current*mu*deltaTime + current*std::sqrt(sig * deltaTime) * deltaW;
  result.at(index) = current;
  if (index == (int)timeStep->size() -1) {
    simulationFinished = true;
    index = 0;
  } else {
    index ++;
  }
  return current;
}

double hestonPP::nextStep() {

  double sig = (*sigmaResult)[index];
  double deltaTime = timeStep->at(index), deltaW =brownien->at(index);

  current = current + current*mu*deltaTime + std::sqrt(sig * deltaTime) * deltaW;
  result[index] = current;
  if (index == (int)timeStep->size() -1) {
    simulationFinished = true;
    index = 0;
  } else {
    index ++;
  }
  return current;
}

double hestonPP::retrieveSt(int iTime) {
  double t = 0.0;
  for (int i=0; i<= iTime; ++i) {
    t += (*timeStep)[i];
  }

  std::vector<double>* resultSigma = sigma->getResult();
  double a = sigma->getA(); double b = sigma->getB(); double nu = sigma->getNu();


  intY = utl::integrale(result,*timeStep,0,iTime);
  intSigma = utl::integrale(*resultSigma, *timeStep, 0, iTime);
  delta = ((*resultSigma)[iTime] - (*resultSigma)[0] - a*b*t + a * intSigma) / nu; 
  double w = result[iTime] - result[0] + intY;
  double res = x0* std::exp(mu*t -   intSigma/2 + rho * delta + std::sqrt(1 - rho*rho) * w);
  return res;
}
void hestonPP::retrieveSt() {
  return;
}

void hestonPP::fullSimulation(bool generateBrownien) {
  resetParameters();

  if (generateBrownien) {
    V.generateArray(*sigma->getBrownien(), timeStep->size());
  }

  sigma->fullSimulation(generateBrownien);
  sigmaResult = sigma->getResult();

  if (generateBrownien) {
    V.generateArray(*brownien, timeStep->size());
  }

  while (not simulationFinished)
    {
      nextStep();
    }

  /*for (int i = 0; i < (int)result.size();++i) {
    result[result.size() - 1 - i] = retrieveSt(result.size() - 1 - i);
    } */
  result[result.size() - 1] = retrieveSt(result.size() -1);
}


void heston::setBrownien(std::vector<double>* w1, std::vector<double>* w2) {
  brownien = w1;
  sigma->setBrownien(w2);
}
