#include <iostream>
#include <random>
#include <functional>
#include <typeinfo>
#include "euler.h"

using namespace std;



int main (int argc, char** argv)
{
  mt19937 gen;
  gen.seed(0);
  uniform_real_distribution<> uniform_distrib(0.0,1.0);
  normal_distribution<> gaussian_distrib(0.0,1.0);

  auto U = bind(uniform_distrib, ref(gen));
  auto G = bind(gaussian_distrib, ref(gen));
  
  euler E(1.0,1.0,1.0,G);
  int NMAX = 1000000;
  vector<double> timestep(NMAX);
  vector<double> result(1000);
  for (int i=0; i<NMAX; ++i)
    {
      timestep[i] = (double)i / (double)NMAX;
    }
  
  E.simulate(timestep,result);
  for (int i=0; i<NMAX; ++i)
    {
      cout << timestep[i] << " " << result[i] << endl;
    }
  return 0;
}
