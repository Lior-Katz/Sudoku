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
	std::vector<int> available;
	
	int value;

public:
	explicit Cell(int size);
	
	int getValue() const;
	
	void setValue(int newValue);
};


#endif //SUDOKU_CELL_H
