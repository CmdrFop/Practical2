#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Group {
private:
	int total_cost;
	int saving;
	int minimum_dividers;
	string members;
	string group_before;
	string group_after;
public:
	Group() {};
	Group(string _members, int _total_cost, int _saving, int _minimum_dividers, string _group_before, string _group_after) :
		total_cost(_total_cost), 
		saving(_saving),
		minimum_dividers(_minimum_dividers),
		members(_members), 
		group_before(_group_before),
		group_after(_group_after) {}
	int get_total_cost() { return total_cost; }
	int get_saving() { return saving; }
	int get_minimum_dividers() { return minimum_dividers; }
	string get_members() { return members; }
	string get_group_before() { return group_before; }
	string get_group_after() { return group_after; }
};