#pragma once

#include <vector>

#include "Experiment.h"
#include "BinaryOperations.h"
#include "UnaryOperations.h"

enum class OperationType;

template <typename T>
class Experiment;

template <typename T, typename P>
class UnaryOperations;

template <typename T, typename P1, typename P2>
class BinaryOperations;

template <typename T>
class GroupExperiment {
public:
	using value_type = T;
	using unary_function_type = typename UnaryOperations<T, T>::function_type;
	using binary_function_type = typename BinaryOperations<T, T, T>::function_type;
	
	GroupExperiment(int64_t iter = 100000, int64_t exp = 10);
	GroupExperiment(const BinaryOperations<T, T, T>&, int64_t iter = 100000, int64_t exp = 10);
	GroupExperiment(const UnaryOperations<T, T>&, int64_t iter = 100000, int64_t exp = 10);
	GroupExperiment(const UnaryOperations<T, T>& , const BinaryOperations<T, T, T>&, int64_t iter = 100000, int64_t exp = 10);

	GroupExperiment(const GroupExperiment<T>&) = default;
	GroupExperiment<T>& operator=(const GroupExperiment<T>&) = default;
	~GroupExperiment() = default;

	GroupExperiment<T>& operator+=(int64_t t) {
		for (auto& x : experiments)
			x += t;
		return *this;
	}
	GroupExperiment<T>& operator-=(int64_t t) {
		for (auto& x : experiments)
			x -= t;
		return *this;
	}
	const Experiment<T>& operator[](int pos) const { return experiments[pos]; }
	Experiment<T>& operator[](int pos) { return experiments[pos]; }

	const std::vector<Experiment<T>>& operator()() const { return experiments; }
	int64_t getNumberOfIterations() const { return experiments.at(0).getNumberOfIterations(); }
	int64_t getNumberOfExperiments() const { return experiments.at(0).getNumberOfExperiments(); }

	void addOperation(const string& s, binary_function_type op) { binary.insert(s, op); }
	void addOperation(const string& s, unary_function_type op) { unary.insert(s, op); }
	void removeOperation(const string& s, OperationType type) {
		return (type == OperationType::BinaryOperation) ? binary.remove(s) : unary.remove(s);  
	}

	void evaluate();

private:
	BinaryOperations<T, T, T> binary;
	UnaryOperations<T, T> unary;
	std::vector<Experiment<T>> experiments;

	int64_t numOfIterations;
	int64_t numOfExperiments;

};

template <typename T>
GroupExperiment<T>::GroupExperiment(int64_t iter, int64_t exp): numOfIterations(iter), numOfExperiments(exp) {

}

template <typename T>
GroupExperiment<T>::GroupExperiment(const UnaryOperations<T, T>& un, int64_t iter, int64_t exp) : 
	unary(un), numOfIterations(iter), numOfExperiments(exp) {

}

template <typename T>
GroupExperiment<T>::GroupExperiment(const BinaryOperations<T, T, T>& bin, int64_t iter, int64_t exp) : 
	binary(bin), numOfIterations(iter), numOfExperiments(exp) {

}

template <typename T>
GroupExperiment<T>::GroupExperiment(const UnaryOperations<T, T>& un, const BinaryOperations<T, T, T>& bin, int64_t iter, int64_t exp) : 
	unary(un), binary(bin), numOfIterations(iter), numOfExperiments(exp) {

}

template <typename T>
void GroupExperiment<T>::evaluate() {
	for (auto it = unary.begin(); it != unary.end(); ++it)
		experiments.push_back(Experiment<T>(it->second, it->first, numOfIterations, numOfExperiments));
	for (auto it = binary.begin(); it != binary.end(); ++it)
		experiments.push_back(Experiment<T>(it->second, it->first, numOfIterations, numOfExperiments));
	for (auto& exp : experiments)
		exp.evaluate();
}










