/*Day 7*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;


bool CharAtInSecond(pair<char, char> p, char c) {
	return p.second == c;
}

struct worker {
	worker(string j = "",int rt=0,bool i_f=true ):job(j),remaning_time(rt),is_free(i_f) {}
	string job;
	int remaning_time;
	bool is_free;
	void update_time(){
		if(remaning_time>0){
			--remaning_time;
			is_free = false;
		}
		else {
			is_free = true;
		}
	}
	void add_job(string s,bool test=false) {
		job = s;
		remaning_time = int(s.at(0)) - 4 - 60 * test;
	}
	bool done() {
		return remaning_time == 0;
	}
	void clear() {
		job = "";
		remaning_time = 0;
		is_free = true;
	}
};

void remove_char(vector< pair<char, char> > &v, map<char, int> &m_end, char c) {
	bool removed = true;
	while (removed) {
		removed = false;
		for (vector<pair<char, char> >::iterator pos = v.begin(); pos != v.end(); ++pos) {
			if ((*pos).first == c) {
				if (--m_end[(*pos).second] == 0) {
					m_end.erase((*pos).second);
				}

				v.erase(pos);
				removed = true;
				break;
			}
		}
	}
}

int main(int argc, const char * argv[]) {
	if (argc < 2) {
		cout << "Usage:" << endl;
		cout << "day7 <input>" << endl;
		return 1;
	}

	string file = argv[1];
	// If it is true then it removes the 60 extra seconds per job
	bool test = false;

	// For part 1 there is only one worker and part 2 there are 5 workers
	const int NR_WORKERS = 1; 

	map<char, int> m_start_char;
	map<char, int> m_end_char;
	vector< pair<char, char> > v_relation;
	
	// Read input
	{
		cout << "Start with input file '" << file << "'" << std::endl;
		ifstream infile(file);
		string str;
		while (getline(infile,str)) {
			pair<char, char> relation;
			relation.first = str.at(5);
			relation.second = str.at(36);
			
			m_start_char[relation.first]++;
			m_end_char[relation.second]++;
			v_relation.push_back(relation);

		}
	}

	vector<worker> v_worker;
	for (int i = 0; i < NR_WORKERS; ++i) {
		v_worker.push_back(worker());
	}

	string result = "";
	int time = 0;
	bool working = true;
	char last = '1'; // the char ´1' is just a character that is not used in the conditions

	while (working) {
		vector<string> v_str;
		for (auto m : m_start_char) {
			if (m_end_char.find(m.first) == m_end_char.end()) {
				v_str.push_back(string() + m.first);
			}
		}
		
		if (v_str.empty() && last!='1') {
			v_str.push_back(string() + last);
			last = '1';
		}
		sort(v_str.rbegin(), v_str.rend());

		for (auto &w : v_worker) {
			if (w.is_free) {
				
				if (v_str.empty()) {break; }

				w.add_job(v_str.back(), test);
				m_start_char.erase(v_str.back().at(0));
				v_str.pop_back();

			}
		}

		int count_done = 0;
		cout << time << "\t";
		for (auto &w : v_worker) {
			if(w.job != "") cout << w.job << "\t";
			else cout << "." << "\t";
			
			w.update_time();
			if (w.done()) {
				result += w.job;
				// remove from end and relations
				count_done++;
				if (w.job != "") { 
					if (m_end_char.size() == 1) {
						last = m_end_char.begin()->first;
					}
					remove_char(v_relation, m_end_char, w.job.at(0));
					w.clear();
				}
			}
			if (count_done == NR_WORKERS && m_end_char.empty() && last =='1') {
				working = false;
			}
		}
		cout << result << endl;

		time++;
	}
	

    return 0;
}