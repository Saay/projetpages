#include <vector>


namespace utl {
  void generateTimeStep(double T, double gamma, std::vector<double> timeStep);
  void generateTimeStep(double T, std::vector<double> timeStep); //constant 


  double integrale(const std::vector<double>& integrand, const std::vector<double>& timeStep, double start, double end);
  double integrale(const std::vector<double>& integrand, const std::vector<double>& timeStep, int iStart, int iEnd);



} //namespace utl
