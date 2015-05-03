#ifndef RANDOMVAR_H
#define RANDOMVAR_H

#include<random>
#include<cmath>
#include<iostream>

template <class genType = std::mt19937>
  class randomVar {
 public:
 randomVar (genType & gen,double current=0.0): gen(gen), current(current) {}
 
 virtual double operator()() = 0;

 virtual void generateArray(std::vector<double>& array, int size)
 {
   array.resize(size);

   for (int i = 0; i < size; ++i) {
     array.at(i) = operator()();
   }

 }
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




#endif
