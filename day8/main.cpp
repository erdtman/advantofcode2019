/*Day 8*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int read_node(ifstream &in) {

	int nr_child_nodes = 0;
	int nr_meta_values = 0;
	int sum = 0;
	in >> nr_child_nodes;
	in >> nr_meta_values;

	for (int i = 0; i < nr_child_nodes; ++i) {
		sum += read_node(in);
	}

	for (int i = 0; i < nr_meta_values; ++i) {
		int value = 0;
		in >> value;
		sum += value;
	}

	return sum;
}
int read_node_2(ifstream &in) {

	int nr_child_nodes = 0;
	int nr_meta_values = 0;
	int sum = 0;
	in >> nr_child_nodes;
	in >> nr_meta_values;
	map<int,int> v_child;

	for (int i = 0; i < nr_child_nodes; ++i) {
		v_child[i+1] = read_node_2(in);
	}

	for (int i = 0; i < nr_meta_values; ++i) {
		int value = 0;
		in >> value;
		
		if (nr_child_nodes == 0) {
			sum += value;
		} else if (v_child[value]) {
			sum += v_child[value];
		}
	}

	return sum;
}

int main(int argc, const char * argv[]) {
	if (argc < 2) {
		cout << "Usage:" << endl;
		cout << "day8 <input>" << endl;
		return 1;
	}

	string file = argv[1];
	
	// Part 1
	{
		cout << "Start with input file '" << file << "'" << std::endl;
		ifstream infile(file);
		int sum = read_node(infile);
		cout << "Part 1: " << sum << endl;
	}
	
	// Part 2
	{
		cout << "Start with input file '" << file << "'" << std::endl;
		ifstream infile(file);
		int sum = read_node_2(infile);
		cout << "Part 2: " << sum << endl;
	}

    return 0;
}