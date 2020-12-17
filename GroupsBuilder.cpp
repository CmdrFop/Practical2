#include "GroupsBuilder.hpp"
#include <limits>

using namespace std;

//map<string,Group> groups_map;

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
	maximum_cost = 50000 * number_of_products;
	create_map(number_of_products, all_costs);
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
tuple<int, string, string> GroupsBuilder::assign_group_values(int minimum_dividers, string group_before, string group_after){
	return tuple<int, string, string> (minimum_dividers, group_before, group_after);
}

void GroupsBuilder::create_map(int number_of_products, vector<int> all_costs) {
	string all_products = "";
	for (int i = 0; i < number_of_products; i++) {
		all_products += to_string(i);
	}

	string current_group = "";
	int total_cost;
	int saving;
	tuple<int, string, string> assgin_group;

	for (int i = 0; i < number_of_products; i++) {
		for (int j = i; j < number_of_products; j++) {
			if (i == j) {
				current_group = to_string(i);
				total_cost = all_costs[i];
				saving = total_cost - round(total_cost);
				assgin_group = assign_group_values((i == 0 || i == number_of_products - 1) ? 1 : 2, all_products.substr(0, i), all_products.substr(i + 1, number_of_products - 1));
			}
			else {
				current_group += to_string(j);
				total_cost += all_costs[j];
				int saving = total_cost - round(total_cost);

				if (i == 0 && j == number_of_products - 1) {		// abcd
					assgin_group = assign_group_values(0, "", "");
				}
				else if (i > 0 && j == number_of_products - 1) { // | bcd
					assgin_group = assign_group_values(1, all_products.substr(0, i), "");
				}
				else if (i > 0 && j < number_of_products - 1) { // | bc |
					assgin_group = assign_group_values(2,  all_products.substr(0, i), all_products.substr(j + 1, number_of_products - 1));
				}
				else { // abc |
					assgin_group = assign_group_values(1, "", all_products.substr(j + 1, number_of_products - 1));
				}
			}

			Group group = Group(current_group, total_cost, saving, get<0>(assgin_group), get<1>(assgin_group), get<2>(assgin_group));
			groups_map.insert(make_pair(group.get_members(), group));			
		}
	}
}

// find best divisions for not main groups
int GroupsBuilder::get_local_cost(string group, int division ){
	int best_savings = 0; // 1 = group.savings
	auto it = groups_map.find(group);  		// O(log n)
	
	if ( it == groups_map.end() ) {  
		// not found  
		cout<<"Element not found";  
	}   
	else {  
		// found  
		// cout << "Iterator points to " << it->first << " = " << it->second << endl;  
		best_savings = it->second.get_saving();
	}

	if (group == "")
		return 0;
	else if (group.size() == 1) 		
		return best_savings; // return group.savings
		
	else {	
		// divide group to find best division of items.
		// max_size_groups = ceil((amount_of_nodes * 1.0) / division);

		int saving_first_half = get_local_cost( group.substr(0, int(group.size()/2)), division); // this division does not cover all possible divisions yet
		int saving_second_half = get_local_cost( group.substr(int(group.size()/2) + 1, -1), division);

		int saving_middle = get_local_cost( group.substr(1,-1), division);
		int saving_start = get_local_cost(group.substr(0,1), division);
		int saving_end = get_local_cost(group.substr(-2,-1), division);

		int alternate_saving;
		if  (saving_middle + saving_start + saving_end > saving_first_half + saving_second_half)
			int alternate_saving = saving_middle + saving_start + saving_end;
		else
			int alternate_saving = saving_first_half + saving_second_half;

		if (alternate_saving > best_savings )
		//  return alternate_saving
			return alternate_saving;
	}
	return best_savings;
}

//1 See if there is a group before and if it can be divided to simplify calculations in the get_local_cost function
int GroupsBuilder::see_if_edge_or_single(string group, int division){
	if (group == "")
		return division -1;
	else if (group.size() == 1)
		return division -2;
	return -1;
}

// step 2.-1 Find optimal combinations of groups
int GroupsBuilder::get_min_cost(Group group, int divisions){

	//1 See if there is a group before and if it can be divided to simplify calculations in the get_local_cost function
	int group_before_max_division = see_if_edge_or_single(group.get_group_before(), divisions);
	int group_after_max_division = see_if_edge_or_single(group.get_group_after(), divisions);

	//3 change the second argument of the get_local_cost function if simplification was found possbile in the code before ( any of the if statements were true)
	int group_before_savings =  get_local_cost(group.get_group_before(), group_before_max_division);
	int	group_after_savings =  get_local_cost(group.get_group_after(), group_before_max_division);

	return group.get_saving() + get_local_cost(group.get_group_before(), divisions) + get_local_cost(group.get_group_after(), divisions);
}

// step2: get best groups
// cycle trough all groups so we can find the best division of items
void GroupsBuilder::get_best_group(int division) {
	int mincost = maximum_cost;
	Group best_group;

	for (auto const& x : groups_map)
	{
		int cost = get_min_cost(x.second, division);

		if (cost <= mincost){
			mincost = cost;
			best_group = x.second;
		}
	}
}

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