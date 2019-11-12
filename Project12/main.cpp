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

int f(int a) {
	return a;
}

void test() {

	int64_t numIterations{ static_cast<int64_t>(1e6) }, numExperiments{ 5 };

	BinaryOperations<int, int, int> bin;
	UnaryOperations<int, int> un;
	UnaryOperations<double, double> un2;

	un.insert(string("+*"), [](int arg) { return arg * 2 + 3; });
	un.insert(string("f"), f);
	un2.insert(string("cos"), [](double arg) { return cos(arg); });
	un2.insert(string("sin"), [](double arg) { return sin(arg); });
	un2.insert(string("log"), [](double arg) { return log(arg); });
	un2.insert(string("exp"), [](double arg) { return exp(arg); });

	bin.insert(string("+"), [](int a, int b) { return a + b; });
	bin.insert(string("-"), [](int a, int b) { return a - b; });
	bin.insert(string("*"), [](int a, int b) { return a * b; });
	bin.insert(string("/"), [](int a, int b) { return a / b; });

	BinaryOperations<double, double, double> bin2;
	bin2.insert(string("+"), [](double a, double b) { return a + b; });
	bin2.insert(string("-"), [](double a, double b) { return a - b; });
	bin2.insert(string("*"), [](double a, double b) { return a * b; });
	bin2.insert(string("/"), [](double a, double b) { return a / b; });

	f(2);
	GroupExperiment<int> group3(un, numIterations, numExperiments);
	GroupExperiment<int> group(bin, numIterations, numExperiments);
	GroupExperiment<double> group2(un2, bin2, numIterations, numExperiments);
	group.evaluate();
	group2.evaluate();
	group3.evaluate();
	outputGroups(minAvgTime(group, group2), group, group2);
	outputGroups(minAvgTime(group3), group3);

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
