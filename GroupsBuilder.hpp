#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include "Group.hpp"
#include <map>

using namespace std;

class GroupsBuilder {
private:
	int minimum_cost;
	int maximum_cost;
	map<string,Group> groups_map;
	int get_min_cost(Group group, int divisions);
	int get_local_cost(string group, int division);
	tuple<int, string, string> assign_group_values(int minimum_dividers, string group_before, string group_after);
	int see_if_edge_or_single(string group, int division);
public:
	void create_groups(int number_of_products, int number_of_dividers, vector<int> all_costs);
	int get_minimum_cost() { return minimum_cost; }
	int round(int cost);
	void create_map(int number_of_products, vector<int> all_costs);
	void get_best_group(int division);
};