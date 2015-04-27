#include <vector>


namespace utl {

  double integrale(const std::vector<double>& integrand, const std::vector<double>& timeStep, double start, double end);
  double integrale(const std::vector<double>& integrand, const std::vector<double>& timeStep, int iStart, int iEnd);



} //namespace utl
