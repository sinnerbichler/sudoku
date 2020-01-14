sudoku : box.o algorithms.o main.cpp
	g++ -o sudoku main.cpp box.o algorithms.o && ./sudoku

box.o : box.cpp box.hpp
	g++ -c box.cpp

algorithms : algorithms.hpp algorithms.cpp
	g++ -c algorithms.cpp
