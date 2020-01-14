#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include "box.hpp"
#include "algorithms.hpp"

using namespace std;

void print_map(vector <vector<Box>> &map);
int load_map(string file_name, vector <vector<Box>> &map);
int solve_map(vector <vector<Box>> &map);

int main (int argc, char * argv[]) {
	string mapname;
	if(argc > 1) {
		mapname = argv[1];
		cout << "mapname: " <<  mapname << endl;
	} else {
		cout << "No mapname specified. Exiting." << endl;
		return 0;
	}

	vector <vector<Box>> map;	//map initialization
	map.resize(9);
	for (int i = 0; i < 9; i++)
		map[i].resize(9);

	chrono::time_point <chrono::system_clock> starttime, endtime;
	chrono::duration <double> eta;

	//testmap2 won't work unless better algorithms are implemented
	if(load_map(mapname, map) == -1)
		return 0;

	print_map(map);
	cout << "Solved input to below: " << endl;
	starttime = chrono::system_clock::now();
	solve_map(map);
	endtime = chrono::system_clock::now();

	print_map(map);

	eta = endtime - starttime;

	cout << "eta: " << eta.count() << endl;
	return 0;
}

int load_map(string file_name, vector <vector<Box>> &map) {
	string line;
	ifstream mapfile (file_name);
	if (!mapfile.is_open()) {
		cout << "failed to open file" << endl;
		return -1;
	}

	int y = 0;
	while (getline(mapfile, line)) {
		if (line.compare(0, 1, "/") == 0)
			break;

		for (int x = 0; x < 9; x++) {
			char c = line[x];
			map[x][y].number(atoi(&c));
		}
		y++;
	}
	mapfile.close();
	return 0;
}
//vector <int> riehiesjs;
void print_map(vector <vector<Box>> &map) {
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			cout << map[x][y].number();
			if ((x+1) % 3 == 0)
				cout << " ";
		}
		cout << endl;
		if ((y+1) % 3 == 0)
			cout << endl;
	}
}

int solve_map(vector <vector<Box>> &map) {
	int unsolved_boxes = 81;

	while (unsolved_boxes > 0) {
		int unsolved_boxes_last = unsolved_boxes;

		unsolved_boxes = 0;
		for (int y = 0; y < 9; y++) {
			for (int x = 0; x < 9; x++) {
				if (map[x][y].number() == 0)
					unsolved_boxes++;
			}
		}
		cout << "Unsolved Boxes: " << unsolved_boxes << endl;

		check_lines(map);
		//check_diagonal(map); //on or off switch must be implemented for special diagonal-including sudokus
		check_fields(map);
		special_row_exclusion(map);
		insert_numbers(map);



		if (unsolved_boxes_last == unsolved_boxes)
			return -1;
	}//while

	return 0;
}
