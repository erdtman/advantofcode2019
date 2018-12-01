#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
//#include <curl/curl.h>

using namespace std;


int main(int argc, const char * argv[]) {
	cout << "Start" << '\n';
	string file = "C:\\Users\\elias\\code\\adventofcode2019\\day1_input_1_E.txt";
	//string input = "-1\n-2\n-3";
	string nr = "";
	string::size_type sz;
	//istringstream iss(input);
	ifstream infile(file);
	vector<int> v_input;
	set<int> s_visited_f;
	int twice = 0;
	bool found = false;
	s_visited_f.insert(twice);
	int frekvens = 0;

	// add input in to a vector to be able to loop through it all
	while (infile >> nr) {
		v_input.push_back(stoi(nr, &sz));
	}
	vector<int>::const_iterator itv;

	while (!found) {
		itv = v_input.begin();
		while (itv != v_input.end()) {
			frekvens += *itv;
			if (s_visited_f.count(frekvens)) {
				twice = frekvens;
				found = true;
			}
			else {
				s_visited_f.insert(frekvens);
			}
			itv++;
			if (found) break;
		}
		cout << " Frekvens: " << frekvens << " Twice: " << twice << endl;
	}

	cout << "twice: " << twice << endl;
	/*
	int i = 0;
	int total_f = 0;
	int in_f = 0;
	while (infile >> nr) {
		in_f = stoi(nr, &sz);
		total_f += in_f;

		cout << i << " total_f: " << total_f << endl;
		++i;

	}*/

    return 0;
}