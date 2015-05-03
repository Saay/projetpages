#include "montecarlo.h"
#include <iostream>
#include "utility.h"
void monteCarlo::setQuantile(double quant) {quantile=quant;}
std::vector<double>* monteCarlo::getRawResult() {return &rawResult;}
double monteCarlo::getConfidenceInterval() {
  computeVariance();
  confidenceInterval = quantile*std::sqrt(variance/nbAlreadySimulated);
  return confidenceInterval;
}

void monteCarlo::resetAll() {
  result = 0.0;
  confidenceInterval = 1.0;
  nbAlreadySimulated = 0;
  rawResult.clear();
  variance = 0.0;
}


double monteCarlo::doSimulations(int nbSimulation) {
  for (int i = 0; i<nbSimulation; ++i) {
    oneStep();
  }
  return result/(double)nbSimulation;
}


double monteCarlo::doSimulationsWithPrecision(double precision, int maxIteration) {
  int batchSize = 1000;
  result = 0.0;
  nbAlreadySimulated = 0;
  oneStep();
  do {
    for (int i = 0; i < batchSize; ++i) {
    oneStep();
    }
    computeVariance();
    confidenceInterval = quantile*std::sqrt(variance/nbAlreadySimulated);
  } while (confidenceInterval  > precision && (nbAlreadySimulated < maxIteration));
  return result/ (double) nbAlreadySimulated;
}

inline void monteCarlo::oneStep() {
  S.fullSimulation();
  
  payoff(*(S.getResult()),*(S.getTimeStep()));
  result += payoffResult;

  rawResult.push_back(payoffResult);
  nbAlreadySimulated ++;
}

double monteCarlo::computeVariance() {
  double mean = result / (double)nbAlreadySimulated;
  double var = 0.0;
  for (int i = 0; i < nbAlreadySimulated; ++i) {
    var += (rawResult[i] - mean)*(rawResult[i] - mean);
  }
  variance = var / ((double) nbAlreadySimulated -1);
  return variance;
}



double vanillePricing::payoff(const std::vector<double>& path, const std::vector<double>& timeStep) {
  //TODO caluler t et le remplacer dans l'exponetiel
  payoffResult = std::exp(-S.getDrift() * 1) * std::max(path.at(timeStep.size()-1)-K,0.0);
  return payoffResult;
}

double asiatPricing::payoff(const std::vector<double>& path, const std::vector<double>& timeStep) {
  double result = 0.0;
  for (int i = 0; i < (int)path.size(); ++i) {
    result += path[i] * timeStep[i];
  }
  payoffResult = result;
  return payoffResult;
}


double monteCarlo::doTwoStepRR(int nbSimulation) {
  std::vector<double>* timeStepSave = S.getTimeStep();
  std::vector<double>* brownienSave = S.getBrownien();
  std::vector<double>* brownienSigmaSave = new std::vector<double>;
  std::vector<double> timeStep1 = *(S.getTimeStep());
  std::vector<double> timeStep2(timeStep1.size() * 2);
  std::vector<double> brownien1 (timeStep1.size());
  std::vector<double> brownien2(timeStep2.size());
  std::vector<double> brownienSigma1 (timeStep1.size());
  std::vector<double> brownienSigma2 (timeStep2.size());
  for (int i = 0; i < (int)timeStep1.size(); ++i) {
    timeStep2[2*i] = timeStep1[i] / 2;
    timeStep2[2*i+1] = timeStep1[i] / 2;
  }


  for (int simu = 0; simu < nbSimulation; ++simu) {
    V->generateArray(brownien2, brownien2.size());
    V->generateArray(brownienSigma2, brownienSigma2.size());
    utl::correlateGaussian(brownienSigma2, brownien2, S.getRho());
    S.setBrownien(&brownien2, &brownienSigma2);
    S.setTimeStep(&timeStep2, &timeStep2);
    S.fullSimulation(false);
    double payoffResult2 = payoff(*S.getResult(), timeStep2);

    //rescale brownien
    for (int j = 0; j < (int)brownien1.size(); ++j) {
      brownien1[j] = 1/std::sqrt(2)* (brownien2[2*j] + brownien2[2*j+1]);
      brownienSigma1[j] = 1/std::sqrt(2) * (brownienSigma2[2*j] + brownienSigma2[2*j+1]);
    }

    S.setBrownien(&brownien1, &brownienSigma1);
    S.setTimeStep(&timeStep1, &timeStep1);
    S.fullSimulation(false);
    payoffResult = payoff(*S.getResult(), timeStep1);


    payoffResult = 2 * payoffResult2 - payoffResult;
    result += payoffResult;
    rawResult.push_back(payoffResult);
    nbAlreadySimulated++;
  }

  S.setTimeStep(timeStepSave, timeStepSave);
  S.setBrownien(brownienSave, brownienSigmaSave);
  result = result/nbAlreadySimulated;
  computeVariance();
  return result;
}


std::vector<double>* monteCarlo::computeRawVariance(){
  double mean =result / (double) nbAlreadySimulated;
  rawVariance.resize(rawResult.size());
  rawVariance[0] = (rawResult[0] - mean) * (rawResult[0] - mean);
  for (int i = 1; i < (int)rawResult.size(); ++i) {
    rawVariance[i] = rawVariance[i-1] + (rawResult[i] - mean) * (rawResult[i] - mean);
  }
  for (int i = 1; i < (int)rawResult.size(); ++i) {
     rawVariance[i] = rawVariance[i] / i;
   }
   return &rawVariance;
}
