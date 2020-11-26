#pragma once
#include <iostream>
#include <vector>
#include "./InputParser.hpp"

using namespace std;

struct InputReader {
private:
	int number_of_products;
	int number_of_dividers;
	vector<int> costs;
public:
	void read_input();
	vector<int> get_all_costs() { return costs; }
	int get_number_of_products() { return number_of_products; }
	int get_number_of_dividers() { return number_of_dividers; }
};