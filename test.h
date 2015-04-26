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
  void printMonteCarlo(monteCarlo& mc);
 private:

  int counter = 1;
};


#endif
