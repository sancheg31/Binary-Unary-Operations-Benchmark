#pragma once

#include <chrono>
#include <functional>
#include <iostream>
#include <type_traits>
#include <vector>

#include "UnaryOperations.h"
#include "BinaryOperations.h"

template <typename T>
class Experiment {
public:

	enum class OperationType { None = 0, UnaryOperation = 1, BinaryOperation = 2 };

	using value_type = T;
	using unary_function_type = typename UnaryOperations<T, T>::function_type;
	using binary_function_type = typename BinaryOperations<T, T, T>::function_type;

	Experiment(unary_function_type, int64_t = 100000, int64_t = 10);
	Experiment(binary_function_type, int64_t = 100000, int64_t = 10);
	Experiment(int64_t = 100000, int64_t = 10);

	Experiment(const Experiment<T>&) = default;
	Experiment& operator=(const Experiment<T>&) = default;
	~Experiment() = default;

	const int64_t& operator[](int i) const { time.at(i); }
	int64_t& operator[](int i) { time.at(i); }
	const std::vector<int64_t>& operator()() const { return time; }

	Experiment<T>& operator+=(int64_t t) {
		for (auto& x : time)
			x += t;
		return *this;
	}

	Experiment<T>& operator-=(int64_t t) {
		for (auto& x : time)
			x -= t;
		return *this;
	}

	void setOperation(binary_function_type op) {
		type = OperationType::BinaryOperation;
		binaryOp = op;
	}

	void setOperation(unary_function_type op) {
		type = OperationType::UnaryOperation;
		unaryOp = op;
	}

	void setNumberOfIterations(int64_t num) { numberOfIterations = num; }
	void setNumberOfExperiments(int64_t num) { numberOfExperiments = num; }

	void evaluate();

	int64_t getAvgTime() const { return avgTime; }
	int64_t getNumberOfIterations() const { return numberOfIterations; }
	int64_t getNumberOfExperiments() const { return numberOfExperiments; }
	int64_t getEmptyCycleTime() const { return emptyCycleTime; }

private:

	int64_t evaluateTime(int64_t numOfIterations, int64_t numOfExperiments) const;
	int64_t countEmptyCycle(int64_t numOfIterations) const;
	int64_t countAvgTime() const;

	OperationType type;

	unary_function_type unaryOp;
	binary_function_type binaryOp;

	std::vector<int64_t> time;
	
	int64_t avgTime;
	int64_t emptyCycleTime;
	
	int64_t numberOfIterations;
	int64_t numberOfExperiments;

};


template <typename T>
Experiment<T>::Experiment(int64_t iter, int64_t exp) : numberOfIterations(iter), numberOfExperiments(exp) {
	time.resize(numberOfExperiments);
}
template <typename T>
Experiment<T>::Experiment(unary_function_type op, int64_t iter, int64_t exp) :
	type(OperationType::UnaryOperation), unaryOp(op), numberOfIterations(iter), numberOfExperiments(exp) {
	time.resize(numberOfExperiments);
}

template <typename T>
Experiment<T>::Experiment(binary_function_type op, int64_t iter, int64_t exp) : 
	type(OperationType::BinaryOperation), binaryOp(op), numberOfIterations(iter), numberOfExperiments(exp) {
	time.resize(numberOfExperiments);
}

template <typename T>
void Experiment<T>::evaluate() {
	emptyCycleTime = countEmptyCycle(numberOfIterations);
	for (int i = 0; i < numberOfExperiments; ++i) {
		time.push_back(evaluateTime(numberOfIterations, numberOfExperiments));
	}
	avgTime = countAvgTime();
}

template <typename T>
int64_t Experiment<T>::countAvgTime() const {
	double sum{};
	for (auto & it : time) {
		sum += it;
	}
	return int64_t(sum / time.size());
}

#pragma optimize("", off)
template <typename T>
int64_t Experiment<T>::evaluateTime(int64_t numOfIterations, int64_t numOfExperiments) const {
	value_type a(9187364), b(12387), c(409871324);
	value_type d, e, f;
	if (type == OperationType::BinaryOperation) {
		auto startPoint = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < numberOfIterations; ++i) {
			d = binaryOp(a, b); e = binaryOp(b, c); f = binaryOp(a, b);
		}
		auto endPoint = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::nanoseconds>(endPoint - startPoint).count();
	}
	else if (type == OperationType::UnaryOperation) {
		auto startPoint = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < numberOfIterations; ++i) {
			d = unaryOp(a); e = unaryOp(b); f = unaryOp(c);
		}
		auto endPoint = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::nanoseconds>(endPoint - startPoint).count();
	}
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
