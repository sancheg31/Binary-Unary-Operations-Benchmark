#pragma once
#include <functional>
#include <type_traits>
#include <utility>
#include <vector>

using std::enable_if_t;
using std::is_arithmetic;
using std::is_pod;

template <typename P, typename T1, typename T2 = T1>
class Operation {
public:
	using result_type = P;
	using first_argument_type = T1;
	using second_argument_type = T2;
};

template <typename T>
class Addition: public Operation<T, T, T> {
public:
	using value_type = T;
	using base_type = Operation<T, T, T>;
	Addition() = default;
	inline T operator()(T a, T b) const {
		return a + b;
	}
};

template <typename T>
class Substraction: public Operation<T, T, T> {
public:
	using value_type = T;
	using base_type = Operation<T, T, T>;
	Substraction() = default;
	inline T operator()(T a, T b) const {
		return a - b;
	}
};

template <typename T>
class Multiplication: public Operation<T, T, T> {
public:
	using value_type = T;
	using base_type = Operation<T, T, T>;
	Multiplication() = default;

	inline T operator()(T a, T b) const {
		return a * b;
	}
};


template <typename T>
class Division: public Operation<T, T, T> {
public:
	using value_type = T;
	using base_type = Operation<T, T, T>;
	Division() = default;
	inline T operator()(T a, T b) const {
		return a / b;
	}

};

template <typename T>
class LogicalAnd: public Operation<T, T, T> {
public:
	using value_type = T;
	using base_type = Operation<T, T, T>;
	LogicalAnd() = default;
	inline T operator()(T a, T b) const {
		return (int)a & (int)b;
	}
};

template <typename T>
class LogicalOr: public Operation<T, T, T> {
	using value_type = T;
	using base_type = Operation<T, T, T>;
	LogicalOr() = default;
	inline T operator()(T a, T b) const {
		return (int)a | (int)b;
	}
};

template <typename T>
class ArithmeticalOperations {
public:
	using value_type = T;
	using function_type = std::pair<std::function<T(T, T)>, char>;

	static bool addOperation(std::function<T(T, T)>, char = '.');
	static const std::vector<function_type>& operations() { return oper; }
private:
	static std::vector<function_type> oper;
};

template <typename T>
std::vector<typename ArithmeticalOperations<T>::function_type> ArithmeticalOperations<T>::oper{ std::pair{Addition<T>(), '+'},
																	std::pair{Substraction<T>(), '-'},
																	std::pair{Multiplication<T>(), '*'},
																	std::pair{Division<T>(), '/'} };

template <typename T>
bool ArithmeticalOperations<T>::addOperation(std::function<T(T, T)> op, char c) {
	oper.push_back(std::make_pair(op, c));
	return true;
}


