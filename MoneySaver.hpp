#pragma once
#include <iostream>
#include <vector>
#include "InputReader.hpp"
#include "GroupsBuilder.hpp"

using namespace std;

class MoneySaver {
private:
	int number_of_products;
	int number_of_dividers;
	vector<int> all_costs;
public:
	void run();
	void process_input();
};