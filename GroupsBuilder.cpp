#include "GroupsBuilder.hpp"
#include <limits>

using namespace std;

void GroupsBuilder::create_groups(int number_of_products, int number_of_dividers, vector<int> all_costs) {
	string total_group = "";
	vector<string> elements = {};
	int total_cost = 0;
	for (int index = 0; index < number_of_products; index++) {
		total_group += to_string(index);
		elements.push_back(to_string(index));
		total_cost += all_costs[index];
	}

	tuple<int, vector<string>, int, string, int,  string > result = recursion_solution(total_group, all_costs, number_of_dividers, elements, total_cost, 0, "");

	std::cout << to_string(get<0>(result)) << endl;
	for (int i; i < get<1>(result).size(); i++){
		std::cout << get<1>(result)[i] << endl;
	}

	// ik weet niet zeker of line 18 in een keer kan, misschien moet je het opsplitsen in:
	// vector<s

	// 5 1
	// 10 23 43 637 45
	// 5  1
	// 10 23 43 637 45
			
}
int GroupsBuilder::round(int cost) {
    if (cost >= 0 && cost < 3)
        return 0;
    if (cost > 2 && cost < 8)
        return 5;
    if (cost > 7 && cost < 10)
        return 10;

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

tuple<int, vector<string>, int, string, int, string>GroupsBuilder::recursion_solution(string group, vector<int> cost, int max_divisions, vector<string> elements, int group_cost, int other_item_cost, string not_in_group) { //, int previous_cost
	// If we meet the base case we return the cost for this single item
	if (group.size() == 1) {
		vector<string> single_group = { group };
		return make_tuple(round(cost[stoi(group)]), single_group, 0, not_in_group , other_item_cost,  "");
	}

	// Create 2 sub_groups from the supe group in such a way all possible groups are covered
	string rec_group1 = group.substr(0, group.size() - 1);
	string rec_group2 = group.substr(1, group.size());

	string not_in_group1 = not_in_group + group.substr(group.size() - 1, group.size());
	string not_in_group2 = not_in_group + group.substr(0, 1);
	
	//to remove cost of first element:
	int group_cost1 = group_cost - cost[stoi(elements[elements.size()-1])];

	int other_item_cost1 = other_item_cost + cost[stoi(elements[elements.size()-1])];
	//to remove cost of last element:
	int group_cost2 = group_cost - cost[stoi(elements[0])];
	int other_item_cost2 = other_item_cost + cost[stoi(elements[0])];
	vector<string> elements1 = elements;
	elements1.pop_back();
	vector<string> elements2 = elements;
	elements2.erase(elements2.begin());	// element [1,2,3,4] rec_group = '1234'
										// bij elements moet je elements nemen dus een subvector van elements

	// Recursion, we split up the group unitl it reaches it atoms (base case) , on the way we compute the best cost
	// and combination of groups
	tuple<int, vector<string>, int, string, int, string> result = recursion_solution(rec_group1, cost, max_divisions, elements1, group_cost1, other_item_cost1,not_in_group1);
	int cost_group1 = get<0>(result);
	vector<string> group1 = get<1>(result);
	int division1 = get<2>(result);
	string previous_group1 = get<3>(result);
	int previous_item_cost1 = get<4>(result);

	result = recursion_solution(rec_group2, cost, max_divisions, elements2, group_cost2, other_item_cost2, not_in_group2);
	int cost_group2 = get<0>(result);
	vector<string> group2 = get<1>(result);
	int division2 = get<2>(result);
	string previous_group2 = get<3>(result);
	int previous_item_cost2 = get<4>(result);

	int alternative_cost;
	vector<string> right_groups;
	string other_group;
	int division;
	int compare;

	//If groups overlap add the best one
	if (group.size() > 2) {
		// group1 = 0
		// group = 01
		// other_item_cost = 1234
		// previous_item_cost = 234
		// if (cost_group1 + round(other_item_cost) < 
		// else if cost_group1 + round(cost[stoi(elements2[elements2.size() - 1])]) + round(previous_item_cost) < 
		if (cost_group1 + round(previous_item_cost1) < cost_group1 + round(cost[stoi(elements2[elements2.size() - 1])]) + round(other_item_cost)
		&& cost_group1 + round(previous_item_cost1) < cost_group2 + round(cost[stoi(elements1[0])]) + round(other_item_cost)
		&& cost_group1 + round(previous_item_cost1) < cost_group2 + round(previous_item_cost2)){
			alternative_cost = cost_group1; //+ round(cost[stoi(elements2[elements2.size() - 1])]); //+ round(previous_item_cost1); // remove end later
			compare = cost_group1 + round(previous_item_cost1);
			right_groups = group1;
			other_group = (previous_group1);
			division = right_groups.size() - 1;
		}
		else if (cost_group2 + round(previous_item_cost2) < cost_group1 + round(cost[stoi(elements2[elements2.size() - 1])]) + round(other_item_cost)
		&& cost_group2 + round(previous_item_cost2) < cost_group2 + round(cost[stoi(elements1[0])]) + round(other_item_cost)
		&& cost_group2 + round(previous_item_cost2) < cost_group1 + round(previous_item_cost1)){
			alternative_cost = cost_group2; //+ round(cost[stoi(elements1[0])]); //+ round(previous_item_cost2); // remove end later
			compare = cost_group2 + round(previous_item_cost2);
			right_groups = group1;
			other_group = (previous_group2);
			division = right_groups.size() - 1;
		}
		// else (cost_group2 + round(cost[stoi(elements1[0])]) + round(previous_item_cost)) <
		if (cost_group1 + round(cost[stoi(elements2[elements2.size() - 1])]) < cost_group2 + round(cost[stoi(elements1[0])])) { // cost_group1 < cost_group2
			alternative_cost = cost_group1 + round(cost[stoi(elements2[elements2.size() - 1])]);
			compare = cost_group1 + round(cost[stoi(elements2[elements2.size() - 1])]) + round(other_item_cost);
			right_groups = group1;
			right_groups.push_back(elements2[elements2.size() - 1]);
			other_group = (not_in_group);
			division = right_groups.size() - 1;
		}
		else {
			alternative_cost = cost_group2 + round(cost[stoi(elements1[0])]);
			compare = cost_group2 + round(cost[stoi(elements1[0])]) + round(other_item_cost);
			right_groups = group2;
			right_groups.push_back(elements1[0]);
			other_group = (not_in_group);
			division = right_groups.size() - 1;
		}
	}
	else {
		if (cost_group1 + round(previous_item_cost1) < cost_group2 + round(previous_item_cost2 ) && cost_group1 + round(previous_item_cost1) < cost_group1 + cost_group2 + round(other_item_cost)){
				alternative_cost = cost_group1; //+ round(previous_item_cost1);
				compare =  cost_group1 + round(previous_item_cost1);
				right_groups = group1;
				other_group = previous_group1;
				division = right_groups.size() - 1;
		}
		else if (cost_group2 + round(previous_item_cost2) < cost_group1 + round(previous_item_cost1) && cost_group2 + round(previous_item_cost2) < cost_group1 + cost_group2 + round(other_item_cost)){
				alternative_cost = cost_group2; //+ round(previous_item_cost2);
				right_groups = group2;
				other_group = previous_group2;
				division = right_groups.size() - 1;
		}
		else {
			alternative_cost = cost_group1 + cost_group2;
			compare = cost_group1 + cost_group2 + round(other_item_cost);
			right_groups = group1;
			right_groups.insert(right_groups.end(), group2.begin(), group2.end());
			division = right_groups.size() - 1;
			other_group = not_in_group;
		}
		// If they do not overlap combine the cost of these 2 groups
		
	}
	// Compare the cost of the sub group calculated in the recursion function to the cost of recomputing the combined
	// round(group_cost) + round(previous_item_cost))
	int AaaA = round(group_cost) + round(other_item_cost);
	if (round(group_cost) + round(other_item_cost) > compare && (division + 0 <= max_divisions))
		return make_tuple(alternative_cost, right_groups, division + 0, not_in_group, other_item_cost, other_group);

		// if the new computed score is better remove the sub groups and use the larger group
	//if ()
	vector<string> return_group = { group };
	return make_tuple(round(group_cost), return_group, 0, not_in_group, other_item_cost, not_in_group);

	// Nu moeten we het et wat breakpoints testen
	// okey
}