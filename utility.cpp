#include "utility.h"
#include <vector>
#include <cmath>

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



  void correlateGaussian(const std::vector<double>& W1, std::vector<double>& W2, const double rho){
    int size = W1.size();
    for (int i = 0; i < size; ++i) {
      W2.at(i) = W1.at(i) * rho + std::sqrt(1-rho*rho) * W2.at(i);
    }
      
  }


  void generateTimeStep(double T, int nbStep, double gamma, std::vector<double> & timeStep) {
    timeStep.resize(nbStep);
    double sum = 0.0;
    for (int i = 0; i < nbStep ; ++i) {
      timeStep[i] = 1 / std::pow((double)i+1,gamma);
      sum += timeStep[i];
    }
    for (int i = 0; i < nbStep ; ++i) {
      timeStep[i] = timeStep[i] / sum * T;
    }    
  }

  void generateCstTimeStep(double T, int nbStep, std::vector<double>& timeStep) {
    timeStep.resize(nbStep);
    for (int i = 0; i < nbStep; ++i) {
      timeStep[i] = T / (double)nbStep;
    }
  }


} //namespace utl
