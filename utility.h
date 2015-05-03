#include <vector>


namespace utl {
  void generateTimeStep(double T, int nbStep, double gamma, std::vector<double>& timeStep);
  void generateCstTimeStep(double T, int nbStep, std::vector<double>& timeStep); //constant 


  double integrale(const std::vector<double>& integrand, const std::vector<double>& timeStep, double start, double end);
  double integrale(const std::vector<double>& integrand, const std::vector<double>& timeStep, int iStart, int iEnd);


  void correlateGaussian(const std::vector<double>& W1, std::vector<double>& W2, double rho); 


} //namespace utl
