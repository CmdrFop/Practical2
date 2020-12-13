#pragma once
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

class GroupsBuilder {
	int minimum_cost;
public:
	void create_groups(int number_of_products, int number_of_dividers, vector<int> all_costs);
	int get_minimum_cost() { return minimum_cost; }
	int round(int cost);
	vector<tuple<string, int, int, string, string>> find_all_savings(int number_of_products, vector<int> all_costs);
};