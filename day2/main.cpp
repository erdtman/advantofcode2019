/*Day 2*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;
const int MAX_CHAR = 256;


int main(int argc, const char * argv[]) {
	if (argc < 2) {
		cout << "Usage:" << endl;
		cout << "day1 <input>" << endl;
 		return 1;
	}

	// Common data storage
	vector<string> v_input;

	{ // Read input
		cout << "Start with input file '" << argv[1] << "'" <<std::endl;
		ifstream infile(argv[1]);
		string line = "";
		while (infile >> line) {
			// TODO should we use references or move instead of value?
			v_input.push_back(line);
		}
	}
	
	{ // Solve part one
		int nr_of_2 = 0;
		int nr_of_3 = 0;
		for(auto &line : v_input) {
			map<char, bool> visited;
			bool visited_2 = false;
			bool visited_3 = false;
			for (char& c : line) {
				if (visited[c]) { 
					continue; 
				}

				visited[c] = true;
				int n = count(line.begin(), line.end(), c);
				if (n == 2 && !visited_2) {
					++nr_of_2;
					visited_2 = true;
				} 
				if (n == 3 && !visited_3) {
					++nr_of_3;
					visited_3 = true;
				}
				
			}
		}
		
		cout << "Part one: " << nr_of_2 * nr_of_3 << endl;
	}

	{ // Solve part two
		string equalpart;
		int nr_diff = 0;
		
		for (auto it = v_input.begin(); nr_diff != 1 && it != v_input.end(); ++it) {
			string current = *it;
			for (auto it_comp = it + 1; nr_diff != 1 && it_comp != v_input.end(); ++it_comp) {
				string comp = *it_comp;
				nr_diff = 0;
				equalpart = "";

				for (int i = 0; i < current.length() && nr_diff<2; ++i) {
					if (current[i] == comp[i]) {
						equalpart += current[i];
					} else {
						++nr_diff;
					}
				}
			}
		}
		cout << "Part two: " << equalpart << endl;
	}
    return 0;
}