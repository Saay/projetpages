#include "test.h"
#include <chrono>
#include <string>
void test::printPath(scheme& S) {
  std::string fileName = *S.getName();
  fileName = fileName + std::to_string(counter) + ".dat";
  std::fstream f(fileName,std::fstream::out);
  std::vector<double>* res = S.getResult();
  std::vector<double>* ts  = S.getTimeStep();
  double totalTime = 0.0;
  for (int i =0; i< (int)ts->size(); ++i) {
    totalTime += (*ts)[i];
    f << totalTime << " " << (*res)[i] << std::endl;
  }
  counter++;
  f.close();
}


void test::printMonteCarlo(monteCarlo& mc, std::string s) {
  std::string fileName = s + std::to_string(counter) + ".dat";
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

using namespace std::chrono; 
  using namespace std; 
void test::presentResult(monteCarlo & MC, int nbSimulation) {

  cout <<   "Doing " << nbSimulation << " simulations with two-step Richardson-Ronberg..." << endl;
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  double result = MC.doTwoStepRR(nbSimulation);
  cout << "    Result : " << result << " done in ";
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
  cout << time_span.count() << "s" << endl;
  cout << "    Confidence interval : " << MC.getConfidenceInterval() << endl;
  printMonteCarlo(MC, "twoStepRR");
  printRawVariance(MC, "twoStepRR");
  
  MC.resetAll();

  cout <<   "Doing " << nbSimulation << " simulations with naive monte-carlo..." << endl;
  t1 = high_resolution_clock::now();
  result = MC.doSimulations(nbSimulation);
  cout << "    Result : " <<  result << " done in ";
  t2 = high_resolution_clock::now();
  time_span = duration_cast<duration<double>>(t2 - t1);
  cout << time_span.count() << "s" << endl;
  cout << "    Confidence interval : " << MC.getConfidenceInterval() << endl;
  printMonteCarlo(MC, "MCnaive" + std::to_string(nbSimulation));
  printRawVariance(MC, "MCnaive" + std::to_string(nbSimulation));

  MC.resetAll();

  cout <<   "Doing " << 2*nbSimulation << " simulations with naive monte-carlo..." << endl;
  t1 = high_resolution_clock::now();
  result = MC.doSimulations(2 * nbSimulation);
  cout << "    Result : " << result << " done in ";
  t2 = high_resolution_clock::now();
  time_span = duration_cast<duration<double>>(t2 - t1);
  cout << time_span.count() << "s" << endl;
  cout << "    Confidence interval : " << MC.getConfidenceInterval() << endl;
  printMonteCarlo(MC, std::to_string(2*nbSimulation) + "naive");
  printRawVariance(MC, "MCnaive" + std::to_string(2*nbSimulation));
}


void test::printRawVariance(monteCarlo & MC, std::string s) {
  std::vector<double> RV = *(MC.computeRawVariance());
  std::string fileName = "RawVariance" + s   + std::to_string(counter) + ".dat";
  std::fstream f(fileName,std::fstream::out);

  for (int i = 0; i < (int)RV.size(); ++i) {
    f << RV[i] << endl;
  }
  counter++;
  f.close();
}
