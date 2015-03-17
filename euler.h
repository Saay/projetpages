#ifndef EULER_H
#define EULER_H


#include <vector>
#include <cmath>
#include<random>
#include<functional>


typedef  std::_Bind<std::normal_distribution<>(std::reference_wrapper<std::mt19937>)> gentype;


class euler{
public:
 euler(double mu, double sigma, double start, gentype& G): mu(mu), sigma(sigma),current(start), G(G) {}
  void simulate(std::vector<double>& timestep, std::vector<double>& result);
private:
  double current;
  gentype G;
  double mu, sigma;
};



#endif
