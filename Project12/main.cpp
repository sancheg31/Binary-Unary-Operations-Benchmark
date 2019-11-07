#include <chrono>
#include <functional>
#include <iostream>
#include <type_traits>
#include <vector>

#include "Experiment.h"
#include "functions.h"

#include "BinaryOperations.h"
#include "UnaryOperations.h"

using namespace std::chrono;
using namespace std;


void test() {

	int64_t numIterations{ static_cast<int64_t>(1e5) }, numExperiments{ 10 };

	BinaryOperations<int, int, int> bin;

	bin.insert(string("+"), [](int a, int b) { return a + b; });
	bin.insert(string("-"), [](int a, int b) { return a - b; });
	bin.insert(string("*"), [](int a, int b) { return a * b; });

	GroupExperiment<int> group(bin, numIterations, numExperiments);
	group.evaluate();
	int64_t minAvg = minAvgTime(group);
	outputGroup(minAvg, group);
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
