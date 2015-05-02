#include "utility.h"
#include <vector>


namespace utl {
  double integrale(const std::vector<double>& integrand,const std::vector<double>& timeStep, double start, double end) {
    double time = 0.0, result = 0.0;
    int indice = 0;
    while (time < start) {
      time += timeStep[indice];
      indice ++;
    }

    while (time<end) {
      time += timeStep[indice];
      result += integrand[indice] * timeStep[indice];
      indice++;
    }
    return result;
  }

  double integrale(const std::vector<double>& integrand, const std::vector<double>& timeStep, int iStart, int iEnd) {
    double result = 0.0;
    for (int i = iStart; i< iEnd +1; ++i) {
      result += integrand[i] * timeStep[i];
    }
    return result;
  }


} //namespace utl
