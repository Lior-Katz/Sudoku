//
// Created by Lior on 25/10/2023.
//

#ifndef SUDOKU_CELL_H
#define SUDOKU_CELL_H

#include "vector"
#include "numeric"
class Cell
{
private:
	const int x;
	
	const int y;
	
	std::vector<int> available;
	
	int value;

public:
	explicit Cell(int x, int y, int size);
	
	int getValue() const;
	
	int getX() const;
	
	int getY() const;
	
	void setValue(int newValue);
	
	void removeAvailable(int value);
};


#endif //SUDOKU_CELL_H
