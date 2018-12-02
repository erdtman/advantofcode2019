/*Day 2*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
const int MAX_CHAR = 256;


int main(int argc, const char * argv[]) {
	cout << "Start" << endl;
	string file = "C:\\Users\\elias\\code\\adventofcode2019\\input\\Day2_1.txt";
	ifstream infile(file);

	int part = 2;

	string s = "";


	int nr_of_2 = 0;
	int nr_of_3 = 0;
	bool counted_2 = false;
	bool counted_3 = false;

	vector<string> v_list;

	while (infile >> s) {
		/* Part one */
		if (part == 1) {
			int used_char[MAX_CHAR];
			for (int i = 0; i < MAX_CHAR; ++i) { used_char[i] = 0; }
			counted_2 = false;
			counted_3 = false;

			for (unsigned int i = 0; i < s.length(); ++i) {
				char c = s.at(i);
				if (used_char[c] != 0) { continue; }
				int n = count(s.begin(), s.end(), c);
				if (n == 2 && !counted_2) {
					++nr_of_2;
					counted_2 = true;
				}
				else if (n == 3 && !counted_3) {
					++nr_of_3;
					counted_3 = true;
				}
				++used_char[c];
			}
		}
		/* Part two */
		v_list.push_back(s);
	}
	if (part == 2){
		string equalpart;
		int nr_diff = 0;
		for (vector<string>::iterator it = v_list.begin(); it != v_list.end() && nr_diff != 1; ++it) {
			string orig = *it;
			cout << "Working with: " <<orig << endl;
			for (vector<string>::iterator it_comp = it + 1; it_comp != v_list.end(); ++it_comp) {
				nr_diff = 0;
				equalpart = "";
				string comp = *it_comp;
				//cout << orig << " compares with " << comp << endl;
				for (unsigned int i = 0; i < orig.length(); ++i) {
					if (orig.at(i) == comp.at(i)) {
						equalpart.push_back(orig.at(i));
					}
					else {
						++nr_diff;
						if (nr_diff > 1) break;
					}
				}
				if (nr_diff == 1) {
					cout << "equalpart: " << equalpart << endl;
					break;
				}
			}
			//cout << "Next comparsion\n";
		}
	}

	if(part==1) cout << "nr_of_2 * nr_of_3: " << nr_of_2 * nr_of_3 << endl;
    return 0;
}