#include "euler.h"

void euler::simulate(std::vector<double>& timestep, std::vector<double> &result) {
  int N = timestep.size();
  int R = result.size();
  if (R != N) {result.resize(N);}
  result[0] = current;
  for (int t = 1; t<N;++t)
    {
      double deltat = (timestep[t] - timestep[t-1]);
      double sqdeltat = sqrt(deltat);
      current = current +  mu * current * deltat +   current * sigma * sqdeltat * G();
      result[t] = current;
    }
}
