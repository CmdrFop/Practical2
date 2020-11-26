#include "InputParser.hpp"

// Parses a string to form a vector of arguments. The seperator is a space char (' ').
vector<int> InputParser::splitString(const string& str) {
	vector<int> retval;
	for (size_t pos = 0; pos < str.length(); ) {
		// look for the next space
		size_t found = str.find(' ', pos);
		// if no space was found, this is the last word
		if (found == string::npos) {
			retval.push_back(stoi(str.substr(pos)));
			break;
		}
		// filter out consequetive spaces
		if (found != pos)
			retval.push_back(stoi(str.substr(pos, found - pos)));
		pos = found + 1;
	}
	return retval;
}