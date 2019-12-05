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

template <typename T, typename P1, typename P2>
BinaryOperations<T, P1, P2> createBinaryOperations() {
	BinaryOperations<T, P1, P2> bin;
	bin.insert(string("+"), [](auto a, auto b) { return a + b; });
	bin.insert(string("-"), [](auto a, auto b) { return a - b; });
	bin.insert(string("*"), [](auto a, auto b) { return a * b; });
	bin.insert(string("/"), [](auto a, auto b) { return a / b; });
	return bin;
}

template <typename T, typename P>
UnaryOperations<T, P> createUnaryOperations() {
	UnaryOperations<T, P> un;

	return un;
}

void test() {

	int64_t numIterations{ static_cast<int64_t>(1e6) }, numExperiments{ 5 };

	GroupExperiment<char> groupChar(createBinaryOperations<char, char, char>(), numIterations, numExperiments);
	GroupExperiment<int> groupInt(createBinaryOperations<int, int, int>(), numIterations, numExperiments);
	GroupExperiment<long> groupLong(createBinaryOperations<long, long, long>(), numIterations, numExperiments);
	GroupExperiment<float> groupFloat(createBinaryOperations<float, float, float>(), numIterations, numExperiments);
	GroupExperiment<double> groupDouble(createBinaryOperations<double, double, double>(), numIterations, numExperiments);
	groupChar.evaluate(); groupInt.evaluate(); groupLong.evaluate(); groupFloat.evaluate(); groupDouble.evaluate();
	outputGroups(minAvgTime(groupChar, groupInt, groupLong, groupFloat, groupDouble), groupChar, groupInt, groupLong, groupFloat, groupDouble);

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
