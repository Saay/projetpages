#include "test.h"


void test::printPath(scheme& S) {
  std::string fileName = *S.getName();
  fileName = fileName + std::to_string(counter) + ".dat";
  std::fstream f(fileName,std::fstream::out);
  std::vector<double>* res = S.getResult();
  const std::vector<double>* ts  = S.getTimeStep();
  double totalTime = 0.0;
  for (int i =0; i< (int)ts->size(); ++i) {
    totalTime += (*ts)[i];
    f << totalTime << " " << (*res)[i] << std::endl;
  }
  counter++;
  f.close();
}


void test::printMonteCarlo(monteCarlo& mc) {
  std::string fileName = "monteCarlo" + std::to_string(counter) + ".dat";
  std::fstream f(fileName,std::fstream::out);
  std::vector<double>* rawResult = mc.getRawResult();
  double result = 0.0;
  for (int nbSimu = 0; nbSimu < (int)rawResult->size(); ++nbSimu) {
    result += (*rawResult)[nbSimu];
    f << nbSimu << " " << result/ ((double) nbSimu) << std::endl;
  }
  counter++;
  f.close();
}
