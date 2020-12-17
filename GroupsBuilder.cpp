#include "GroupsBuilder.hpp"
#include <limits>

using namespace std;

void GroupsBuilder::create_groups(int number_of_products, int number_of_dividers, vector<int> all_costs) {
	// minimum_cost = numeric_limits<int>::max();
	// vector<int> groups;
	// for (int position_first_divider = 1; position_first_divider < all_costs.size() - 1; position_first_divider++) {
	// 	int total_cost_first_group = 0;

	// 	for (int index_element_first_group = 0; index_element_first_group < position_first_divider; index_element_first_group++)
	// 		total_cost_first_group += all_costs[index_element_first_group];

	// 	int total_cost_second_group = 0;
	// 	for (int index_element_second_group = position_first_divider; index_element_second_group < all_costs.size(); index_element_second_group++)
	// 		total_cost_second_group += all_costs[index_element_second_group];

	// 	total_cost_first_group = round(total_cost_first_group);
	// 	total_cost_second_group = round(total_cost_second_group);
	// 	int total = total_cost_first_group + total_cost_second_group;

	// 	if (total < minimum_cost) {
	// 		minimum_cost = total;
	// 	}
	// }

	find_all_groups(number_of_products, all_costs);
}

// step1: find all savings for each group (bottom-up) 
// and determine which division causes highest saving
					// group saving minium dividers needed
// a	, -, 1, "" , "bcd"			<"0123" , 1, 	3>
// ab	, -, 1, "" , "cd"			<"01234", 4, 	2>
// abc	, -, 1, "" , "d"			<"012"  , 2, 	1>
// abcd	, -, 0, "" , ""			<"12"   , 1, 	5, "0", "3">		"123" 
// b	, -, 2, "a", 
// bc	:
// bcd	:
// c	:
// cd	:

// a | b | c | d			k = 1

// input: 
// 5  1
// 10 23 43 637 45

vector<Group> GroupsBuilder::find_all_groups(int number_of_products, vector<int> all_costs) {
	string all_products = "";
	for (int i = 0; i < number_of_products; i++) {
		all_products += to_string(i);
	}

	string current_group = "";
	int total_cost;
	int saving;
	int minimum_dividers;
	string group_before = "";
	string group_after = "";

	vector<Group> all_groups;
	for (int i = 0; i < number_of_products; i++) {
		for (int j = i; j < number_of_products; j++) {
			if (i == j) {
				current_group = to_string(i);
				total_cost = all_costs[i];
				saving = total_cost - round(total_cost);
				minimum_dividers = (i == 0 || i == number_of_products - 1) ? 1 : 2;
				group_before = all_products.substr(0, i);
				group_after = all_products.substr(i + 1, number_of_products - 1);
			}
			else {
				current_group += to_string(j);
				total_cost += all_costs[j];
				int saving = total_cost - round(total_cost);

				if (i == 0 && j == number_of_products - 1) {		// abcd
					minimum_dividers = 0;
					group_before = "";
					group_after = "";
				}
				else if (i > 0 && j == number_of_products - 1) { // | bcd
					minimum_dividers = 1;
					group_before = all_products.substr(0, i);
					group_after = "";
				}
				else if (i > 0 && j < number_of_products - 1) { // | bc |
					minimum_dividers = 2;
					group_before = all_products.substr(0, i);
					group_after = all_products.substr(j + 1, number_of_products - 1);
				}
				else { // abc |
					minimum_dividers = 1;
					group_before = "";
					group_after = all_products.substr(j + 1, number_of_products - 1);
				}
			}

			Group group = Group(current_group, total_cost, saving, minimum_dividers, group_before, group_after);
			all_groups.push_back(group);
		}
	}
	return all_groups;
}
int get_local_cost(string group){
	if (group == "")
		return 0;
	else if (group.size() == 1)
		return 1; // return group.savings
	else {
		int best_savings = 1; // 1 = group.savings
		// divide group to find best division of items.
		int saving_first_half = get_local_cost( group.substr( 0, group.size())); // this division does not cover all possible divisions yet
		int saving_second_half = get_local_cost( group.substr( group.size() + 1, -1));
	}
	return 1;
}

int get_min_cost(Group group){
	return group.get_saving() + get_local_cost(group.get_group_before()) + get_local_cost(group.get_group_before());
}

// step2: get best group
void get_best_group(vector<Group> groups) {
	int mincost = get_min_cost(groups[0]);
	Group mingroup = groups[0];
	for (int i = 1; i < groups.size(); i++){
		int cost = get_min_cost(groups[i]);
		if (cost < mincost){
			mincost = cost;
			mingroup = groups[i];
		}
	}
}

/*
			
*/

int GroupsBuilder::round(int cost) {
	string string_cost = to_string(cost);
	int last_number = stoi(string_cost.substr(string_cost.size() - 1, string_cost.size() - 1));
	
	string result = string_cost;

	if (last_number > 0 && last_number < 3) {
		result = string_cost.substr(0, string_cost.size() - 1) + "0";
	}
	else if (last_number > 2 && last_number < 8) {
		result = string_cost.substr(0, string_cost.size() - 1) + "5";
	}
	else if (last_number == 8 || last_number == 9) {
		int new_cost = stoi(string_cost.substr(0, string_cost.size() - 1));
		new_cost++;
		result = to_string(new_cost) + "0";
	}

	return stoi(result);
}