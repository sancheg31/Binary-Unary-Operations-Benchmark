#include <chrono>
#include <functional>
#include <iostream>
#include <type_traits>
#include <vector>

#include "experiment.h"
#include "groupExperiment.h"
#include "functions.h"
#include "operations.h"

using namespace std::chrono;
using namespace std;

void test() {
	ArithmeticalOperations<int>::addOperation([](int a, int b) { return a | b; }, '|');
	ArithmeticalOperations<int>::addOperation([](int a, int b) { return a & b; }, '&');

	ArithmeticalOperations<bool>::addOperation([](bool a, bool b) { return a | b; }, '|');
	ArithmeticalOperations<bool>::addOperation([](bool a, bool b) { return a & b; }, '&');
	ArithmeticalOperations<bool>::addOperation([](bool a, bool b) { return a ^ b; }, '^');

	int64_t numIterations{ static_cast<int64_t>(1e5) }, numExperiments{ 10 };

	GroupExperiment<bool> boolGroup(numIterations, numExperiments);
	GroupExperiment<int> intGroup(numIterations, numExperiments);
	GroupExperiment<char> charGroup(numIterations, numExperiments);
	GroupExperiment<long> longGroup(numIterations, numExperiments);
	GroupExperiment<float> floatGroup(numIterations, numExperiments);
	GroupExperiment<double> doubleGroup(numIterations, numExperiments);
	
	auto minAvg = minAvgTime(charGroup, intGroup, longGroup, floatGroup, doubleGroup);
	outputGroups(minAvg, charGroup, intGroup, longGroup, floatGroup, doubleGroup);
	outputGroup(minAvgTime(boolGroup), boolGroup);
}

int main() {

	auto startPoint = high_resolution_clock::now();
	test();
	auto endPoint = high_resolution_clock::now(); 
	cout.precision(3);
	cout << "Program worked " << duration_cast<nanoseconds>(endPoint - startPoint).count() / (1e9) << " seconds\n";
	system("pause");
	return 0;

}
