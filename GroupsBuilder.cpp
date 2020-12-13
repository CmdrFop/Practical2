#include "GroupsBuilder.hpp"
#include <limits>
#include <tuple>

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

	find_all_savings(number_of_products, all_costs);
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

vector<tuple<string, int, int, string, string>> GroupsBuilder::find_all_savings(int number_of_products, vector<int> all_costs) {
	// tuple<group, saving, minium dividers needed, group before this group, group after this group>
	string all_products = "";
	for (int i = 0; i < number_of_products; i++) {
		all_products += to_string(i);
	}

	vector<tuple<string, int, int, string, string>> all_savings;
	for (int i = 0; i < number_of_products; i++) {
		string current_group = to_string(i);
		int total_cost = all_costs[i];
		int saving = total_cost - round(total_cost);
		tuple <string, int, int, string, string> group = make_tuple(current_group, saving, 1, all_products.substr(0,i), all_products.substr(i + 1,number_of_products - 1));
		all_savings.push_back(group);

		for (int j = i + 1; j < number_of_products; j++) {
			current_group += to_string(j);
			total_cost += all_costs[j];
			int saving = total_cost - round(total_cost);
			tuple <string, int, int, string, string> group;

			if (i == 0 && j == number_of_products - 1) {		// abcd
				group = make_tuple(current_group, saving, 0, "", "");
			} else if (i > 0 && j == number_of_products - 1) { // | bcd
				group = make_tuple(current_group, saving, 2, all_products.substr(0,i), "");
			} else if (i > 0 && j < number_of_products - 1) { // | bc |
				group = make_tuple(current_group, saving, 2, all_products.substr(0,i), all_products.substr(j + 1,number_of_products - 1));
			} else { // abc |
				group = make_tuple(current_group, saving, 2, "", all_products.substr(j + 1,number_of_products - 1));
			}

			all_savings.push_back(group);
		}
	}
	return all_savings;
}

// step2: get best group
// void get_best_group(tuple<string, int, int, string, string>> groups) {
// 	int mincost = getmincost(groups[0]);
// 	for (int i = 1; i < groups.size(); i++){
// 		int cost = getmincost(groups[i]);
// 		if (cost < mincost)
// 			mincost = cost;
// 	}
// }

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