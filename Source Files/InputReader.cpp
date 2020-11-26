#include "./Header Files/InputReader.hpp"

void InputReader::read_input() {
	string input;
	getline(cin, input);
	InputParser input_parser;
	vector<int> parsed_input = input_parser.splitString(input);
	number_of_products = parsed_input[0];
	number_of_dividers = parsed_input[1];
	getline(cin, input);
	costs = input_parser.splitString(input);
}