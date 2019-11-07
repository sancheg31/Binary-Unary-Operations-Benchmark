#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

#include "GroupExperiment.h"
#include "Experiment.h"

using std::enable_if_t;
using std::is_arithmetic;
using std::is_arithmetic_v;
using std::conjunction_v;
using std::is_same;
using std::is_convertible;
using std::string;
using namespace std::chrono;


template <typename T>
using value_type = typename T::value_type;

template <typename P, typename T = P>
using unary_function_type = std::function<P(T)>;

template <typename P, typename T1, typename T2>
using binary_function_type = std::function<P(T1, T2)>;

template <typename T>
using is_group_experiment = is_same<GroupExperiment<value_type<T>>, T>;


int64_t fromTimeToFreq(int64_t value, int64_t numOfIterations, double timeExtent) {
	return (int64_t)(numOfIterations / (value / timeExtent));
}

template <typename ... Tp>
enable_if_t<conjunction_v<is_group_experiment<Tp>...>, void>
reduceGroups(int64_t val, Tp &... tp) {
	((tp -= val), ...);
}

template <typename ... Tp>
enable_if_t<conjunction_v<is_group_experiment<Tp>...>, void>
increaseGroups(int64_t val, Tp &... tp) {
	((tp += val), ...);
}

template <typename ... Tp>
enable_if_t<conjunction_v<is_group_experiment<Tp>...>, int64_t>
maxAvgTime(Tp &... tp) {
	int64_t maxVal{ numeric_limits<int64_t>::min() }, temp{};
	((temp = maxAvgTimeGroup(tp), maxVal = (temp > maxVal ? temp : maxVal)), ...);
	return maxVal;
}

template <typename T>
int64_t maxAvgTimeGroup(const GroupExperiment<T>& group) {
	int64_t maxVal{ numeric_limits<int64_t>::min() };
	for (auto & x : group())
		if (maxVal < x.getAvgTime())
			maxVal = x.getAvgTime();
	return maxVal;
}

template <typename ... Tp>
enable_if_t<conjunction_v<is_group_experiment<Tp>...>, int64_t>
minAvgTime(Tp & ... tp) {
	int64_t minVal{ numeric_limits<int64_t>::max() }, temp{};
	((temp = minAvgTimeGroup(tp), minVal = (temp < minVal ? temp : minVal)), ...);
	return minVal;
}

template <typename T>
int64_t minAvgTimeGroup(const GroupExperiment<T> & group) {
	int64_t minVal{ numeric_limits<int64_t>::max() };
	for (auto & x : group())
		if (minVal > x.getAvgTime())
			minVal = x.getAvgTime();
	return minVal;
}

template <typename ... Tp>
enable_if_t<conjunction_v<is_group_experiment<Tp>...>, void>
outputGroups(int64_t minValue, Tp ... tp) {
	std::cout << '\n';
	((outputGroup(minValue, tp)), ...);
}

template <typename T> 
void outputGroup(int64_t minValue, const GroupExperiment<T> & group) {
	using std::cout;
	using std::setw;
	using std::setprecision;

	for (auto & x : group()) {
		cout.unsetf(cout.right);
		cout.setf(cout.left);
		cout << setw(2) << x.getOperation();
		cout << setw(7) << typeid(typename GroupExperiment<T>::value_type{}).name();
		cout << setw(10) << setprecision(5) << (double)fromTimeToFreq(x.getAvgTime(), x.getNumberOfIterations(), 1e9) << "  ";
		auto percentage = (fromTimeToFreq(x.getAvgTime(), x.getNumberOfIterations(), 1e9) /
			(double)fromTimeToFreq(minValue, x.getNumberOfIterations(), 1e9)) * 100;

		cout << setw(22) << [percentage]() -> std::string {
			std::string s;
			for (int i = 0; i < ((percentage / 10) * 2); ++i)
				s += 'X';
			return s;
		}();
		cout.unsetf(cout.left);
		cout.setf(cout.right);
		cout << setw(4) << setprecision(3) << percentage;
		cout << setw(2) << "%\n";
	}
	cout << '\n';
}









