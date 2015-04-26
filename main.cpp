#include <iostream>
#include <random>
#include <functional>
#include <typeinfo>

#include "randomvar.h"
#include "scheme.h"
#include "montecarlo.h"
#include "test.h"

using namespace std;



int main (int argc, char** argv)
{
  test T;
  mt19937 gen;
  correlGaussian<> CG(gen,0.5);
  gaussian<> G(gen);
  vector<double> timeStep(1000,0.001);
  CIR vol(CG, timeStep);
  hestonPP HPP(CG, vol);
  vanillePricing MC(HPP);
  asiatPricing AP(HPP);


  cout <<   MC.doSimulationsWithPrecision(0.01) << endl;
  //T.printMonteCarlo(MC);
  //  cout << MC.doSimulations(10000) << endl;
  //T.printMonteCarlo(MC);
  HPP.fullSimulation();
  T.printPath(HPP);
  HPP.fullSimulation();
  T.printPath(HPP);
  return 0;
}
