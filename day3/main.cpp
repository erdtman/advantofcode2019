/*Day 2*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct patch {
	patch(unsigned int i=0,int c_x=0,int c_y=0,int s_x=0,int s_y=0):
		id(i),coord_x(c_x), coord_y(c_y), size_x(s_x), size_y(s_y) {}

	unsigned int id;
	int coord_x;
	int coord_y;
	int size_x;
	int size_y;
	string to_str() {
		string s = "#" + to_string(id) +" @ " + to_string(coord_x) +','+ to_string(coord_y) +": "+ to_string(size_x) +'x'+ to_string(size_y);
		return s;
	}
};

int main(int argc, const char * argv[]) {
	if (argc < 2) {
		cout << "Usage:" << endl;
		cout << "day3 <input>" << endl;
		return 1;
	}
	cout << "Start" << endl;
	string file = argv[1];
	
	vector<patch> v_input;

	
	// initate fabric
	const int SIZE = 1000; // use argv
	char fabric[SIZE][SIZE];
	
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			fabric[i][j] = 'x';
		}
	}
	
	// Read input
	{
		cout << "Start with input file '" << file << "'" << std::endl;
		ifstream infile(file);
		string line = "";
		string::size_type sz;
		int id, c_x, c_y, s_x, s_y;
		while (getline(infile, line)){
			string temp;
			int nr;
			//cout << line << endl;
			//cout << "id: " << line.substr(1, line.find_first_of(' ')-1) << endl;
			id = stoi(line.substr(1, line.find_first_of(' ') - 1), &sz);
			line = line.substr(line.find_first_of('@') + 2, line.size());
			
			//cout << "coord x: " << line.substr(0, line.find_first_of(',')) << endl;
			c_x = stoi(line.substr(0, line.find_first_of(',')));

			line = line.substr(line.find_first_of(',') + 1, line.size());
			//cout << "coord y: " << line.substr(0, line.find_first_of(':')) << endl;
			c_y = stoi(line.substr(0, line.find_first_of(':')));

			line = line.substr(line.find_first_of(':') + 2, line.size());
			//cout << "size x: " << line.substr(0, line.find_first_of('x')) << endl;
			s_x = stoi(line.substr(0, line.find_first_of('x')));

			line = line.substr(line.find_first_of('x') + 1, line.size());
			//cout << "size y: " << line << endl;
			s_y = stoi(line);
			
			//patch p(id, c_x, c_y, s_x, s_y);
			//cout << "p: " << p.to_str() << endl;
			v_input.push_back(patch(id, c_x, c_y, s_x, s_y));
		}
	}
	
	// Fill in of the fabrix
	{
		auto itv = v_input.begin();
		while (itv != v_input.end()) {
			patch p = (*itv);
			// add value
			for (int i = p.coord_x; i < p.coord_x + p.size_x; ++i) {
				for (int j = p.coord_y; j < p.coord_y + p.size_y; ++j) {
					if (fabric[i][j] == 'x') {
						fabric[i][j] = 'u'; // used

					}
					else {
						fabric[i][j] = 'o'; // overlapping
					}
				}
			}
			itv++;
		}
	}

	// Part one
	{
		int sum_overlap = 0;
		for (int j = 0; j < SIZE; ++j) {
			for (int i = 0; i < SIZE; ++i) {
				//cout << fabric[i][j];
				if (fabric[i][j] == 'o') {
					++sum_overlap;
				}
			}
			//cout << endl;
		}
		cout << "sum_overlap: " << sum_overlap << endl;
	}

	// Part two
	{
		auto itv = v_input.begin();
		bool overlap = false;

		while (itv != v_input.end()) {
			patch p = (*itv);
			// add value
			overlap = false;
			for (int i = p.coord_x; i < p.coord_x + p.size_x && !overlap; ++i) {
				for (int j = p.coord_y; j < p.coord_y + p.size_y && !overlap; ++j) {
					if (fabric[i][j] == 'o') {
						overlap = true;
					}
				}
			}
			if (!overlap) {
				cout << "Patch not overlapping: "<< p.to_str() << endl;
				break;
			}
			itv++;
		}
	}
	
	
    return 0;
}