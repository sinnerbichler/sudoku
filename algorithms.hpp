//algorithms
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>
#include "box.hpp"

int check_lines(std::vector <std::vector<Box>> &map); //checks vertical and horizontal lines of the entire sudoku map for any possible exclusions to be done
int check_diagonal(std::vector <std::vector<Box>> &map); //only for sudokus that include diagonal checking
int check_fields(std::vector <std::vector<Box>> &map); //checking inside of each 3x3 field
//special case with two numbers occupying each two boxes and another these two boxes and a third not yet implemented
int insert_numbers(std::vector <std::vector<Box>> &map); //does the number inserting (the actual map changes)
int special_row_exclusion(std::vector <std::vector<Box>> &map); //when a number could be in two or three boxes stacked on top of each other or in a row, that excludes all other boxes of that line
void clear_flags_of_line(int flag, bool vertical, int coordinate, std::vector <std::vector <Box>> &map);

#endif
