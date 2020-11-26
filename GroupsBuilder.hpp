#pragma once
#include <iostream>
#include <vector>

using namespace std;

class GroupsBuilder {
	int minimum_cost;
public:
	void create_groups(int number_of_products, int number_of_dividers, vector<int> all_costs);
	int get_minimum_cost() { return minimum_cost; }
};