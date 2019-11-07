#pragma once

#include <map>
#include <string>

#include "functions.h"

using std::map;
using std::string;

template <typename T, typename P1, typename P2>
class BinaryOperations {
public:
	using value_type = T;
	using function_type = std::function<T(P1, P2)>;

	using iterator = typename map<string, function_type>::iterator;
	using const_iterator = typename map<string, function_type>::const_iterator;

	std::pair<iterator, bool> insert(const string& s, function_type op) { return oper.insert(std::pair{ s, op }); }
	void remove(const string& s) { oper.erase(s); }

	int size() const { return oper.size(); }
	bool contains(const string& s) const { return oper.contains(s); }

	const function_type& operator[](const string& s) const { return oper[s]; }
	function_type& operator[](const string& s) { return oper[s]; }

	iterator begin() { return oper.begin(); }
	const_iterator begin() const { return oper.begin(); }
	const_iterator cbegin() const { return oper.cbegin(); }

	iterator end() { return oper.end(); }
	const_iterator end() const { return oper.end(); }
	const_iterator cend() const { return oper.cend(); }

private:
	map<string, function_type> oper;
};







