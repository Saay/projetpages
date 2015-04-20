#include <iostream>
#include <random>
#include <functional>
#include <typeinfo>
#include "randomvar.h"
#include "scheme.h"
#include "montecarlo.h"


using namespace std;



int main (int argc, char** argv)
{
  mt19937 gen;
  correlGaussian<> CG(gen,0.5);
  vector<double> timeStep(1000,0.001);
  CIR vol(CG, timeStep);
  heston H(CG, vol);
  vanillePricing MC(H);
  MC.nSimulations(1000);

  return 0;
}
