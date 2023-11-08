//
// Created by Lior on 26/10/2023.
//

#ifndef SUDOKU_PLACEVALUE_H
#define SUDOKU_PLACEVALUE_H

#include "vector"
#include "stack"
#include "Board.h"
#include "DeleteAvailable.h"
#include "memory"

class PlaceValue
{
private:
	Board& board;
	
	Cell& cell;
	
	int value;
	
	std::stack<DeleteAvailable> deductions;
	
	void updateRowAvailables();
	
	void updateColumnAvailables();
	
	void updateBoxAvailables();

public:
	PlaceValue(Board& board, Cell& cell, int value);
	
	bool execute();
	
	void undo();
};


#endif //SUDOKU_PLACEVALUE_H
