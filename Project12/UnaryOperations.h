#pragma once

#include <map>
#include <string>

#include "functions.h"

using std::map;
using std::string;

template <typename T, typename P = T>
class UnaryOperations;

template <typename T, typename P>
class UnaryOperations {
public:
	using value_type = T;
	using function_type = unary_function_type<T, P>;

	using iterator = typename map<string, function_type>::iterator;
	using const_iterator = typename map<string, function_type>::const_iterator;

	std::pair<iterator, bool> insert(const string& s, function_type op) { return oper.insert(std::pair{ s, op }); }
	void remove(const string& s) { oper.erase(s); }

	const map<string, function_type>& operations() const { return oper; }
	int size() const { return oper.size(); }
	bool contains(const string& s) const { return oper.contains(s); }

private:
	map<string, function_type> oper;
};


