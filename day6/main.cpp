/*Day 2*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <cmath> 

using namespace std;


struct coord {
	coord(/*int i=-1,*/ int x=-1, int y=-1):/*id(i),*/x(x),y(y){}
	//int id;
	int x;
	int y;
	string to_str() {
		//string s = "#" + to_string(id) + ": " + to_string(x) + ":" + to_string(y);
		string s = "(" + to_string(x) + "," + to_string(y) +")";
		return s;
	}
};

struct point{
	point(unsigned short i = 0, unsigned short d=65000):id(i),dist(d){}
	unsigned short id;
	unsigned short dist;
};

int dist(coord point,int x, int y) {
	int diff_x = abs(point.x - x);
	int diff_y = abs(point.y - y);
	return diff_x + diff_y;
}



int main(int argc, const char * argv[]) {


	if (argc < 2) {
		cout << "Usage:" << endl;
		cout << "day4 <input>" << endl;
		return 1;
	}

	string file = argv[1];

	map<int, coord> m_input;
	const int SIZE = 350;
	const int CUT_OFF = 10000;

	// Read input
	{
		cout << "Start with input file '" << file << "'" << std::endl;
		ifstream infile(file);
		string str;
		coord coord;
		int id = 1;
		while (infile >> str) {
			size_t found_comma = str.find_first_of(',');
			string::size_type sz;

			if (found_comma != string::npos) {
				str.erase(found_comma, 1);
				coord.x = stoi(str, &sz);
			}
			else {
				coord.y = stoi(str, &sz);
				m_input[id] = coord;
				++id;
			}
		}
	}

	// Part one
	{
		point board[SIZE][SIZE];
		for (int i = 0; i < SIZE; ++i) {
			for (int j = 0; j < SIZE; ++j) {

				for (pair<int, coord> element : m_input) {
					int d = dist(element.second, i, j);
					if (board[i][j].dist == d) {
						board[i][j].id = 0;
					}
					else if (board[i][j].dist > d) {
						board[i][j].id = element.first;
						board[i][j].dist = d;
					}
				}

			}
		}
		if (SIZE < 30) {
			for (int i = 0; i < SIZE; ++i) {
				for (int j = 0; j < SIZE; ++j) {
					cout << board[j][i].id << " ";
				}
				cout << endl;
			}
		}

		// Check edge points
		set<int> s_edge;
		s_edge.insert(0);
		for (int i = 0; i < SIZE; ++i) {
			s_edge.insert(board[0][i].id);
			s_edge.insert(board[i][0].id);

			s_edge.insert(board[SIZE - 1][i].id);
			s_edge.insert(board[i][SIZE - 1].id);
		}
		map<int, int> count;
		for (int i = 0; i < SIZE; ++i) {
			for (int j = 0; j < SIZE; ++j) {
				if (s_edge.count(board[j][i].id) == 0) {
					count[board[j][i].id] += 1;
				}
			}
		}

		for (auto const& x : count) {
			cout << x.first  // string (key)
				<< ':'
				<< x.second // string's value 
				<< std::endl;
		}
	}
	// Part two
	{
		bool board[SIZE][SIZE];
		int s = 0;
		for (int i = 0; i < SIZE; ++i) {
			for (int j = 0; j < SIZE; ++j) {
				unsigned short sum= 0;
				for (pair<int, coord> element : m_input) {
					sum += dist(element.second, i, j);
				}
				board[i][j] = (sum < CUT_OFF);
				s += board[i][j];
			}
		}

		//for (int i = 0; i < SIZE; ++i) {
		//	for (int j = 0; j < SIZE; ++j) {
		//		//cout << board[j][i] << " ";
		//		//s+= board[j][i];
		//	}
		//	//cout << endl;
		//}
		cout << "sum: " << s << endl;
	}

    return 0;
}