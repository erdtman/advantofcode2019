/*Day 2*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

string remove_all_pairs(string str) {
	string par1;
	string par2;
	string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	bool found = true;
	while (found) {
		found = false;
		for (auto upper_c : alpha) {
			char lower_c = char(upper_c + 32);
			par1 = string() + lower_c + upper_c;
			par2 = string() + upper_c + lower_c;

			size_t small_large = str.find(par1);
			while (small_large < str.length()) {
				str.erase(small_large, 2);
				small_large = str.find(par1);
				found = true;
			}
			size_t large_small = str.find(par2);
			while (large_small < str.length()) {
				str.erase(large_small, 2);
				large_small = str.find(par2);
				found = true;
			}
		}
	}
	return str;
}

int main(int argc, const char * argv[]) {

	
	if (argc < 2) {
		cout << "Usage:" << endl;
		cout << "day4 <input>" << endl;
		return 1;
	}
	
	string file = argv[1];
	string line;

	{
		cout << "Start with input file '" << file << "'" << std::endl;
		ifstream infile(file);
		if (infile.fail()) {
			cout << "Problem with the file" << endl;
			return 1;
		}

		infile >> line;
	}

	{
		string part1 = remove_all_pairs(line);
		cout << "part1: " << part1.length() << endl;
	}

	// Part 2
	{
		map<char, int> m_remaning_length;
		string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		string str;
		string str_reduced = remove_all_pairs(line);
		//cout << str_reduced << endl;
		bool removed = false;
		for (auto upper_c : alpha) {
			str = str_reduced;
			removed = false;
			char lower_c = char(upper_c + 32);
			
			size_t found_lower = str.find_first_of(lower_c);
			while (found_lower != string::npos)
			{
				//cout << str.substr(found_lower, 1) << endl;
				str.erase(found_lower,1);
				found_lower = str.find_first_of(lower_c, found_lower);
				removed = true;
			}
			size_t found_upper = str.find_first_of(upper_c);
			while (found_upper != string::npos)
			{
				//cout << str.substr(found_upper, 1) << endl;
				str.erase(found_upper, 1);
				found_upper = str.find_first_of(upper_c, found_upper);
				removed = true;
			}
			//cout << lower_c << " " << str << endl;
			if (removed) {
				str=remove_all_pairs(str);
				m_remaning_length[lower_c] = str.length();
				//cout << lower_c << " " << str << endl;
			}
			//cout << lower_c << " is done." << endl;
		}

		cout << "Part2: select the minumum number in the list below:\n";
		for (auto m : m_remaning_length) {
			cout << m.first << " : " << m.second << endl;
		}
	}
    return 0;
}