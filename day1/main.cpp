#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;


int main(int argc, const char * argv[]) {
	if (argc < 2) {
		cout << "Usage:" << endl;
		cout << "day1 <input>" << endl;
 		return 1;
	}
	
	// Common data storage
	vector<int> v_input;

	{ // Read input
		cout << "Start with input file '" << argv[1] << "'" <<std::endl;
		ifstream infile(argv[1]);
		string nr = "";
		string::size_type sz;
		while (infile >> nr) {
			v_input.push_back(stoi(nr, &sz));
		}
	}

	{ // Solve part one
		int current = 0;
		auto itv = v_input.begin();
		while (itv != v_input.end()) {
			current += *itv;
			itv++;
		}
		std::cout << "Answer part one : " << current << endl;
	}

	{ // Solve part two
		int current = 0;
		std::map<int, bool> visited;
		auto itv = v_input.begin();
		while (!visited[current]) {
			visited[current] = true;
			current += *itv;
			itv++;
			if(itv == v_input.end()) {
				itv = v_input.begin();
			}
		}
		std::cout << "Answer part two : " << current << endl;
	}

    return 0;
}