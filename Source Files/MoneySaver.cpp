#include "./Header Files/MoneySaver.hpp"

void MoneySaver::run() {
	process_input();
	GroupsBuilder groups_builder;
	groups_builder.create_groups(number_of_products, number_of_dividers, all_costs);
	cout << groups_builder.get_minimum_cost() << endl;
}

void MoneySaver::process_input() {
	InputReader input_reader;
	input_reader.read_input();

	number_of_products = input_reader.get_number_of_products();
	number_of_dividers = input_reader.get_number_of_dividers();
	all_costs = input_reader.get_all_costs();
}