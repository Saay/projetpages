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
  vector<double> timeStep(1000,0.001);
  CIR vol(CG, timeStep);
  heston H(CG, vol);
  vanillePricing MC(H);
  asiatPricing AP(H);

  MC.doSimulations(1000);
  AP.doSimulations(1000);
  cerr << "yo" << endl;
  T.printMonteCarlo(MC);
  MC.doSimulations(1000);
  T.printMonteCarlo(MC);
  T.printPath(H);
  return 0;
}
