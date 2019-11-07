#pragma once

#include <functional>
#include <vector>
#include <type_traits>

#include "experiment.h"
#include "operations.h"

template <typename T, typename Enable = typename std::enable_if<std::is_arithmetic<T>::value>::type>
class GroupExperiment;

template <typename T>
class GroupExperiment<T> {
public:
	using value_type = T;
	using function_type = typename ArithmeticalOperations<T>::function_type;

	GroupExperiment(int64_t iter = 100000, int64_t exp = 10);
	GroupExperiment(const std::vector<function_type> &, int64_t iter = 100000, int64_t exp = 10);

	~GroupExperiment() = default;

	GroupExperiment<T>& operator+=(int64_t t) {
		for (auto &x : experiments)
			x += t;
		return *this;
	}
	GroupExperiment<T>& operator-=(int64_t t) {
		for (auto & x : experiments)
			x -= t;
		return *this;
	}
	const Experiment<T>& operator[](int pos) const {
		return experiments[pos];
	}
	Experiment<T>& operator[](int pos) {
		return experiments[pos];
	}
	
	const std::vector<Experiment<T>>& operator()() const {
		return experiments;
	}
	
	int64_t getNumberOfIterations() const {
		return experiments.at(0).getNumberOfIterations();
	}

	int64_t getNumberOfExperiments() const {
		return experiments.at(0).getNumberOfExperiments();
	}

private:
	std::vector<Experiment<T>> experiments;
};

template <typename T>
GroupExperiment<T>::GroupExperiment(int64_t iter, int64_t exp) {
			for (auto & x : ArithmeticalOperations<T>::operations())
			experiments.push_back(Experiment<T>(x, iter, exp));
}

template <typename T>
GroupExperiment<T>::GroupExperiment(const std::vector<GroupExperiment<T>::function_type> & v, int64_t iter, int64_t exp) {
	for (auto & x : v)
		experiments.push_back(Experiment<T>(x, iter, exp));
}



