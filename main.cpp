#include <iostream>
#include <random>
#include <functional>
#include <typeinfo>
#include <time.h>
#include "randomvar.h"
#include "scheme.h"
#include "montecarlo.h"
#include "test.h"

using namespace std;



int main (int argc, char** argv)
{

  test T;
  mt19937 gen(0);
  mt19937 gen2(0);
  correlGaussian<> CG(gen,0.5);
  correlGaussian<> CG2(gen2,0.5);
  gaussian<> G(gen);
  vector<double> timeStep(1000,0.001);
  CIR vol(CG, timeStep);
  hestonPP HPP(CG, vol);
  heston H(CG2,vol);
  vanillePricing MC(HPP);
  vanillePricing MC2(H);


  //cout <<   MC.doSimulations(1000) << endl;
  //cout <<   MC2.doSimulations(1000) << endl;
  //T.printMonteCarlo(MC);
  //  cout << MC.doSimulations(10000) << endl;
  //T.printMonteCarlo(MC);
  HPP.fullSimulation(true);
  T.printPath(HPP);
  H.fullSimulation();
  T.printPath(H);
  T.printPath(*H.getSigma());
  return 0;
}
