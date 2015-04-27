#ifndef RANDOMVAR_H
#define RANDOMVAR_H

#include<random>
#include<cmath>


template <class genType = std::mt19937>
  class randomVar {
 public:
 randomVar (genType & gen,double current=0.0): gen(gen), current(current) {}
 
 virtual double operator()() = 0;
 
 protected:
 genType & gen;
 double current;
};

template <class genType = std::mt19937>
class unif :  public randomVar<genType>  {
 public:
 unif (genType & gen, double lower = 0.0, double upper=1.0) : randomVar<genType>(gen), unifDistrib(lower,upper) {}
 
 double operator()() {
   randomVar<genType>::current = unifDistrib(randomVar<genType>::gen);
   return randomVar<genType>::current;
 }
 
 private:
 std::uniform_real_distribution<> unifDistrib;
};


template <class genType = std::mt19937>
class gaussian : public randomVar<genType> {
 public:
 gaussian (genType & gen, double mean = 0.0, double var = 1.0) : randomVar<genType>(gen), gaussianDistrib(mean,var) {}
 
 virtual double operator()() {
  randomVar<genType>::current = gaussianDistrib(randomVar<genType>::gen);
  return randomVar<genType>::current;
}
 private:
 std::normal_distribution<> gaussianDistrib;
};



template <class genType = std::mt19937>
  class correlGaussian : public randomVar<genType> {
 public:
 correlGaussian (genType & gen,double rho = 0.0) : randomVar<genType>(gen), rho(rho), G(gen), firstQuery(true) {
    if (rho > 1.0 or rho <-1.0) { rho = 0.0;}
  }
 
 virtual double operator()();
 
 void next();
 double w1() const {return _w1;}
 double w2() const {return _w2;}
 double getRho() const {return rho;}

 private:
 
 double rho;
 gaussian<genType> G;
 double _w1;
 double _w2;
 bool firstQuery;
};

template<class genType>
double correlGaussian<genType>::operator()() {
  if (firstQuery) {
    _w1 = G();
    _w2 = G();
    _w2 = rho*_w1 + std::sqrt(1-rho*rho)*_w2;
    firstQuery = false;
     return _w1;
  } else {
    firstQuery = true;
    return _w2;
  }
}


template<class genType>
void correlGaussian<genType>::next() {
  _w1 = G();
  _w2 = G();
  _w2 = rho*_w1 + std::sqrt(1-rho*rho)*_w2;
}

#endif
