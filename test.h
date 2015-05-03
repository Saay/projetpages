#ifndef TEST_H
#define TEST_H

#include "scheme.h"
#include "montecarlo.h"
#include <iostream>
#include <fstream>
#include <string>


class test {
 public:
  void printPath(scheme& S);
  void printMonteCarlo(monteCarlo& mc, std::string s);
  void printRawVariance(monteCarlo & MC, std::string s);

  void presentResult(monteCarlo & MC, int nbSimulation);
private:
  int counter = 1;
};


#endif
