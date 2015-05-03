#include <iostream>
#include <random>
#include <functional>
#include <typeinfo>
#include <time.h>
#include <chrono>
#include "randomvar.h"
#include "scheme.h"
#include "montecarlo.h"
#include "test.h"
#include "utility.h"
using namespace std;
using namespace std::chrono;

int main (int argc, char** argv)
{
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  test T;
  //cin >> s;
  mt19937 gen(seed);
  gaussian<> G(gen);
  vector<double> timeStepCst;
  vector<double> timeStepDec;
  utl::generateCstTimeStep(1.0, 1000, timeStepCst);
  utl::generateTimeStep(1.0, 1000,1.0, timeStepDec);
  CIR volC(G, timeStepCst);
  heston HC(G, volC);
  CIR volD(G, timeStepDec);
  heston HD(G, volD);
  //hestonPP HPP(G,vol);
  vanillePricing MCC(HC, 1.0);
  vanillePricing MCD(HD, 1.0);
  
  T.presentResult(MCC, 100000);
  T.presentResult(MCD, 100000);
  //H.fullSimulation();
    
  //  T.printPath(H);
    
  //  HPP.fullSimulation();
  
  //T.printPath(HPP);
  //T.printPath(*H.getSigma());
  
    
    return 0;
}
