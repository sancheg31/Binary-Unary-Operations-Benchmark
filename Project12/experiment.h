#pragma once

#include <chrono>
#include <functional>
#include <iostream>
#include <type_traits>
#include <vector>

#include "operations.h"

template <typename T>
class Experiment {
public:
	using value_type = T;
	using function_type = typename ArithmeticalOperations<T>::function_type;

	Experiment(function_type, int64_t = 100000, int64_t = 10);
	~Experiment() = default;
	const int64_t& operator[](int i) const {
		time.at(i);
	}
	int64_t& operator[](int i) {
		time.at(i);
	}
	const std::vector<int64_t>& operator()() const {
		return time;
	}

	Experiment<T>& operator+=(int64_t t) {
		for (auto & x : time)
			x += t;
		return *this;
	}
	Experiment<T>& operator-=(int64_t t) {
		for (auto & x : time)
			x -= t;
		return *this;
	}
	int64_t getAvgTime() const {
		return avgTime;
	}

	int64_t getNumberOfIterations() const {
		return numberOfIterations;
	}

	int64_t getNumberOfExperiments() const {
		return numberOfExperiments;
	}
	int64_t getEmptyCycleTime() const {
		return emptyCycleTime;
	}
	function_type getOperation() const {
		return Op;
	}

private:
	
	int64_t evaluateTime() const;
	int64_t countAvgTime() const;
	int64_t countEmptyCycle(int64_t numOfIterations) const;

	function_type Op;
	std::vector<int64_t> time;
	int64_t avgTime;
	int64_t emptyCycleTime;
	const int64_t numberOfIterations;
	const int64_t numberOfExperiments;

};

template <typename T>
Experiment<T>::Experiment(function_type f, int64_t iter, int64_t exp) : Op(f), numberOfIterations(iter), numberOfExperiments(exp) {
	time.reserve(numberOfExperiments);
	emptyCycleTime = countEmptyCycle(numberOfIterations);
	for (int i = 0; i < numberOfExperiments; ++i) {
		time.push_back(evaluateTime());
	}
	avgTime = countAvgTime();
}

template <typename T>
int64_t Experiment<T>::countAvgTime() const {
	double sum{};
	for (auto it = time.begin(); it != time.end(); ++it) {
		sum += *it;
	}
	return int64_t(sum / time.size());
}

#pragma optimize("", off)
template <typename T>
int64_t Experiment<T>::evaluateTime() const {
	value_type a(9187364), b(12387), c(409871324);
	value_type d, e, f;
	auto startPoint = std::chrono::high_resolution_clock::now();
	switch (Op.second) {
	case '+':
		for (int i = 0; i < numberOfIterations; ++i) {
			d = a + b; e = b + c; f = a + c;
		}
		break;
	case '-':
		for (int i = 0; i < numberOfIterations; ++i) {
			d = a - b; e = b - c; f = a - c;
		}
		break;
	case '*':
		for (int i = 0; i < numberOfIterations; ++i) {
			d = a * b; e = b * c; f = a * c;
		}
		break;
	case'/':
		for (int i = 0; i < numberOfIterations; ++i) {
			d = a / b; e = c / b; f = c / a;
		}
		break;
	default:
		for (int i = 0; i < numberOfIterations; ++i) {
			d = Op.first(a, b); e = Op.first(b, c); f = Op.first(a, c);
		}
		break;
	}
	auto endPoint = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(endPoint - startPoint).count();
}

#pragma optimize("", off)
template <typename T>
int64_t Experiment<T>::countEmptyCycle(int64_t numOfIterations) const {
	T a(123123), b(123123), c(123123);
	auto startPoint = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < numOfIterations; ++i) {
		a = b; b = c; a = c;
	}
	auto endPoint = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(endPoint - startPoint).count();
}