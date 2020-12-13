#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include "Group.hpp"

using namespace std;

class GroupsBuilder {
	int minimum_cost;
public:
	void create_groups(int number_of_products, int number_of_dividers, vector<int> all_costs);
	int get_minimum_cost() { return minimum_cost; }
	int round(int cost);
	vector<Group> find_all_groups(int number_of_products, vector<int> all_costs);
};