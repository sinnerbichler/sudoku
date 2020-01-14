#include "algorithms.hpp"
#include <iostream>
using namespace std;

int check_lines(vector <vector<Box>> &map) {
	for (int i = 1; i < 10; i++) {

		//horizontal
		int occurrences = 0;
		for (int y = 0; y < 9; y++) {
			occurrences = 0;
			for (int x = 0; x < 9; x++) {
				if(map[x][y].number() == i)
					occurrences++;
			}//for x

			if(occurrences > 1)
				cout << "Multiple occurrences of " << i << " in horizontal line " << y +1 << "!" << endl;

			for (int x = 0; x < 9; x++) {
				/*if(occurrences == 0)
					map[x][y].can_be(i);*/
				if(occurrences == 1)
					map[x][y].cannot_be(i);// cout << "set " << x << y << " cannot be " << i << endl;
			}//for x
		} //for y

		//vertical
		occurrences = 0;
		for (int x = 0; x < 9; x++) {
			occurrences = 0;
			for (int y = 0; y < 9; y++) {
				if(map[x][y].number() == i)
					occurrences++;
			}//for y

			if(occurrences > 1)
				cout << "Multiple occurrences of " << i << " in vertical line " << x +1 << "!" << endl;

			for (int y = 0; y < 9; y++) {
				/*if(occurrences == 0)
					map[x][y].can_be(i);*/
				if(occurrences == 1)
					map[x][y].cannot_be(i);/*, cout << "set " << x << y << " cannot be " << i << endl*/
			} //for y
		}//for x
	} // for i
	return 0;
}

int check_diagonal(std::vector <std::vector<Box>> &map) {
	for (int i = 1; i < 10; i++) {

		//top left to bottom right
		int occurrences = 0;
		for (int j = 0; j < 9; j++) {
			if (map[j][j].number() == i)
				occurrences++;
		}//for j
		for (int j = 0; j < 9; j++) {
			/*if (occurrences == 0)
				map[j][j].can_be(i);*/
			if (occurrences == 1)
				map[j][j].cannot_be(i);
		}//for j
		if (occurrences > 1)
			cout << "Multiple occurrences of " << i << " in diagonal line tl to br!" << endl;


		//bottom left to top right
		occurrences = 0;
		for (int j = 0; j < 9; j++)
			if (map[j][8 - j].number() == i)
				occurrences++;

		for (int j = 0; j < 9; j++) {
			/*if (occurrences == 0)
				map[j][8 - j].can_be(i); */
			if (occurrences == 1)
				map[j][8 - j].cannot_be(i);
		}//for j
		if (occurrences > 1)
			cout << "Multiple occurrences of " << i << " in diagonal line bl to tr!" << endl;

	}//for i
	return 0;
}//check diagonals

int check_fields(std::vector <std::vector<Box>> &map) {
	for (int i = 1; i < 10; i++) {
		for (int fx = 0; fx < 3; fx++) //fields x and y
			for (int fy = 0; fy < 3; fy++) {
				int occurrences = 0;
				for (int bx = 0; bx < 3; bx++) 	//boxes x and y (occurrences)
					for (int by = 0; by < 3; by++) {
						if (map[(fx * 3) + bx][(fy * 3) + by].number() == i)//get number of occurrences of the number that is i
							occurrences++;
					}//for boxes y

				for (int bx = 0; bx < 3; bx++) 	//boxes x and y (setting flags)
					for (int by = 0; by < 3; by++) {
						if (occurrences == 1)
							map[(fx * 3) + bx][(fy * 3) + by].cannot_be(i);
					}
				if (occurrences > 1)
					cout << "Multiple occurrences of " << i << " in field " << fx << fy +1 << "!" << endl;
			}//for fields y
	}//for i

	return 0; //should return changes made
}//check fields

int insert_numbers(std::vector <std::vector<Box>> &map) {
	for (int i = 1; i < 10; i++) {
		for (int fx = 0; fx < 3; fx++) {//for every field do
			for (int fy = 0; fy < 3; fy++) {

				int possible_boxes = 0; //count the number of possible boxes the number that is i could be in
				for (int bx = 0; bx < 3; bx++) {
					for (int by = 0; by < 3; by++) {
						possible_boxes += map[(fx * 3) + bx][(fy * 3) + by].test_for(i);
					}//for by
				}//for bx

				for (int bx = 0; bx < 3; bx++) {
					for (int by = 0; by < 3; by++) {
						if (map[(fx * 3) + bx][(fy * 3) + by].number() == 0)
							if (possible_boxes == 1 && map[(fx * 3) + bx][(fy * 3) + by].test_for(i) == true) {
								map[(fx * 3) + bx][(fy * 3) + by].number(i);
								cout << "Inserted " << i << " in box " << (fx * 3) + bx + 1 << (fy * 3) + by + 1 << "." << endl;
							}//if
					}//for by
				}//for bx
			}//for fy
		}//for fx
	}//for i

	return 0;
}

int special_row_exclusion(std::vector <std::vector<Box>> &map) {
	for (int i = 1; i < 10; i++) {
		for (int fx = 0; fx < 3; fx++) {//for every field do
			for (int fy = 0; fy < 3; fy++) {
				vector <vector <int>> boxes_coord; 	//{ {x1, y1},
																// {x2, y2} }
				int occs_of_possibility = 0;
				for (int bx = 0; bx < 3; bx++) {
					for (int by = 0; by < 3; by++) {
						if (map[(fx * 3) + bx][(fy * 3) + by].test_for(i) == 1) {
							occs_of_possibility++;

							vector <int> coord = {(fx * 3) + bx, (fy * 3) + by};
							boxes_coord.push_back(coord);
						}//if
					}//for by
				}//for bx

				//if(occs_of_possibility == 3)
				//	occs_of_possibility = 0;

				vector <int> dir_vec (2, 0);
				if (occs_of_possibility == 2) {
					dir_vec[0] = boxes_coord[1][0] - boxes_coord[0][0];
					dir_vec[1] = boxes_coord[1][1] - boxes_coord[0][1];

					if (dir_vec[0] == 0)
						clear_flags_of_line(i, true, boxes_coord[0][0], map);

					if (dir_vec[1] == 0)
						clear_flags_of_line(i, false, boxes_coord[0][1], map);

					map[ boxes_coord[0][0] ] [ boxes_coord[0][1] ].can_be(i);
					map[ boxes_coord[1][0] ] [ boxes_coord[1][1] ].can_be(i);
				} // in case of 2

				if (occs_of_possibility == 3) {
					dir_vec.at(0) = 44;//initialize the dir_vec to something else than { {0, 0}, {0, 0}}
					dir_vec.at(1) = 44;

					if (boxes_coord[0][0] == boxes_coord[1][0] && boxes_coord[0][0] == boxes_coord[2][0])
						dir_vec[0] = 0;

					if (boxes_coord[0][1] == boxes_coord[1][1] && boxes_coord[0][1] == boxes_coord[2][1]) {
						dir_vec[1] = 0;
					}

					if (dir_vec[0] == 0) {
						clear_flags_of_line(i, true, boxes_coord[0][0], map);
						cout << "Special row exclusion (3 boxes) triggered for number " << i << " vertical line: " << boxes_coord[0][0] + 1 << endl;
						cout << "Boxes: " << boxes_coord[0][0] + 1 << boxes_coord[0][1] + 1 << ", " << boxes_coord[1][0] + 1 << boxes_coord[1][1] + 1 << ", " << boxes_coord[2][0] + 1 << boxes_coord[2][1] + 1 << endl;
					}


					if (dir_vec[1] == 0) {
						clear_flags_of_line(i, false, boxes_coord[0][1], map);
						cout << "Special row exclusion (3 boxes) triggered for number " << i << " horizontal line: " << boxes_coord[0][1] + 1 << endl;
						cout << "Boxes: " << boxes_coord[0][0] + 1 << boxes_coord[0][1] + 1 << ", " << boxes_coord[1][0] + 1 << boxes_coord[1][1] + 1 << ", " << boxes_coord[2][0] + 1 << boxes_coord[2][1] + 1 << endl;
					}


					map[ boxes_coord[0][0] ] [ boxes_coord[0][1] ].can_be(i);
					map[ boxes_coord[1][0] ] [ boxes_coord[1][1] ].can_be(i);
					map[ boxes_coord[2][0] ] [ boxes_coord[2][1] ].can_be(i);
				}//in case of 3
			}//for fy
		} //for fx
	}//for i
	return 0;
}

void clear_flags_of_line(int flag, bool vertical, int coordinate, std::vector <std::vector <Box>> &map) {
	for (int i = 0; i < 9; i++) {
		if (vertical)
			map[coordinate][i].cannot_be(flag);
		if (!vertical)
			map[i][coordinate].cannot_be(flag);
	}
}
