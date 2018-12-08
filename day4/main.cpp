/*Day 2*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <map>

using namespace std;


int getdate_nr(string time) {
	string::size_type sz;
	int days_in_month[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int month = stoi(time.substr(5, 2), &sz);
	int mday = stoi(time.substr(8, 2), &sz);
	for (int i = 0; i < month - 1; ++i) {
		mday += days_in_month[i];

	}
	return mday;
}


struct guard_duty {
	guard_duty(int d=-1, int i=-1, int s[60]=NULL, int tsm=0) {
		day_nr = d;
		id = i;
		total_sleep_minutes = tsm;
		for (int j = 0; j < 60; ++j) {
			sleep[j] = s[j];
			total_sleep_minutes += s[j];
		}

	}

	int day_nr;
	int id;
	int sleep[60];
	int total_sleep_minutes;
	string to_str() {
		string s = to_string(day_nr) + " #" + to_string(id) + " ";
		for (int i = 0; i < 60; ++i) s += sleep[i];
		s += " Tot: " + to_string(total_sleep_minutes);
		return s;
	}
};


struct action {
	action(string t="1518-01-01 00:00",int i=-1, bool s=false):time(t),id(i),start(s), day_nr(-1), hour(-1),min(-1){
		day_nr = getdate_nr(t);
		string::size_type sz;
		hour = stoi(time.substr(11, 2), &sz);
		min = stoi(time.substr(14, 2), &sz);
		if (hour == 23) {
			min = 0;
			++day_nr;
		}
	}
	action(const action &a) {
		time = a.time;
		id = a.id;
		start = a.start;
		day_nr = a.day_nr;
		hour = a.hour;
		min = a.min;
	}
	string time;
	int id;
	bool start;
	int day_nr;
	int hour;
	int min;
	bool operator<(action a)const {
		return time < a.time;
	}
	action& operator=(const action& a) {
		time = a.time;
		id = a.id;
		start = a.start;
		day_nr = a.day_nr;
		hour = a.hour;
		min = a.min;
		return *this;
	}
	string to_str() {
		string s = to_string(day_nr) + " #" + to_string(id);
		if (start) s += " start";
		else s += " stop";
		return s;
	}
};


int main(int argc, const char * argv[]) {
	
	if (argc < 2) {
		cout << "Usage:" << endl;
		cout << "day4 <input>" << endl;
		return 1;
	}
	string file = argv[1];

	map<int, int> guard_tot_sleep;
	map<int, int[60]> guard_sleep_array;

	{
		cout << "Start with input file '" << file << "'" << std::endl;
		ifstream infile(file);
		string line = "";
		string time = "";
		string command = "";
		string::size_type sz;

		vector<action> v_action;
		bool start = false;
		int time_matrix[365][60]; for (int i = 0; i < 60; ++i) for (int j = 0; j < 365; ++j) time_matrix[j][i] = 0;
		int id = -1;

		while (getline(infile, line)) {
			id = -1;
			//cout << line << endl;
			time = line.substr(1, line.find_first_of(']') - 1);
			//cout << time.substr(11, 2) << " " << time.substr(14, 2) << endl;
			line = line.substr(line.find_first_of(']') + 2, line.length());
			command = line.substr(0, 5);
			if (command == "Guard") {
				id = stoi(line.substr(7, line.find_first_of('b') - 7), &sz);
				start = true;
			}
			else if (command == "wakes") {
				start = true;
			}
			else {
				start = false;
			}
			v_action.push_back(action(time, id, start));
		}
		// sort
		sort(v_action.begin(), v_action.end());

		// Set the ID of the guard
		for (auto &action : v_action) {
			if (action.id != -1) id = action.id;
			else action.id = id;
		}

		// Create arrays for each hour with the information if the guard sleeps or not
		action prev_action = *v_action.begin();
		vector<guard_duty> v_gd;
		for (auto it = v_action.begin(); it != v_action.end(); ++it) {
			int day = prev_action.day_nr;
			action current(*it);
			
			if (prev_action.day_nr == current.day_nr) {
				if (!prev_action.start && current.start) {
					
					for (int i = prev_action.min; i < current.min; ++i) {
						time_matrix[day][i] = 1;
					}

				}
			}
			if (current.day_nr != prev_action.day_nr || (it + 1) == v_action.end()) {
				v_gd.push_back(guard_duty(day, prev_action.id, time_matrix[day]));
			}
			prev_action = (*it);
		}

		for (auto &gd : v_gd) {
			guard_tot_sleep[gd.id] += gd.total_sleep_minutes;
			for (int i = 0; i < 60; ++i) {
				guard_sleep_array[gd.id][i] += gd.sleep[i];
			}
		}
	}
	// Part_one
	{
		int id_guard_max_sleep = -1;
		int max_sleep = -1;
		for (auto it = guard_tot_sleep.begin(); it != guard_tot_sleep.end(); ++it) {
			cout << it->first << ":" << it->second << endl;
			if (max_sleep < it->second) {
				max_sleep = it->second;
				id_guard_max_sleep = it->first;
			}
		}

		int  max_min = -1;
		int  max_value = -1;
		for (int i = 0; i < 60; ++i) {
			if (guard_sleep_array[id_guard_max_sleep][i] > max_value){
				max_value = guard_sleep_array[id_guard_max_sleep][i];
				max_min = i;
			}
			//cout << to_string((it->second)[i]);
		}

		cout << "id_guard_max_sleep: " << id_guard_max_sleep 
			<< "\nmax_sleep: " << max_sleep
			<< "\nmax_value: " << max_value
			<< "\nmax_min: " << max_min
			<< "\nmax_min * id_guard_max_sleep: " << max_min * id_guard_max_sleep << endl;
	}
	//Part two
	{
		int guard_id = -1;
		int max_min_value = -1;
		int max_minute = -1;
		for (auto it = guard_sleep_array.begin(); it != guard_sleep_array.end(); ++it) {
			for (int i = 0; i < 60; ++i) {
				if (it->second[i] > max_min_value) {
					max_min_value = it->second[i];
					guard_id = it->first;
					max_minute = i;
				}
			}
		}

		cout << "guard_id: " << guard_id
			<< "\nmax_min_value: " << max_min_value
			<< "\nmax_minute: " << max_minute
			<< "\nguard_id * max_minute: " << guard_id * max_minute << endl;
	}
	
    return 0;
}