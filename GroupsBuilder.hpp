#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include "Group.hpp"
#include <map>

using namespace std;

class GroupsBuilder {
public:
	void create_groups(int number_of_products, int number_of_dividers, vector<int> all_costs);
	int round(int cost);
	tuple<int, vector<string>, int, string, int, string> recursion_solution(string group, vector<int> cost, int max_divisions, vector<string> elements, int group_cost, int other_item_cost, string not_in_group);
};