//
// Created by Lior on 26/10/2023.
//

#ifndef SUDOKU_DELETEAVAILABLE_H
#define SUDOKU_DELETEAVAILABLE_H

#include "Cell.h"

class DeleteAvailable
{
private:
	Cell& cell;
	
	int value;

public:
	DeleteAvailable(Cell& cell, int value);
	
	bool execute();
	
	void undo();
};


#endif //SUDOKU_DELETEAVAILABLE_H
