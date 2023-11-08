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
	
	Cell& cell; // cell that this command acts upon
	
	int value; // value to put in cell
	
	std::stack<DeleteAvailable> deductions; // FILO log of all possible value deletions following this placement
	
	/**
	 * removes value from the list of possible values of all cells in the same row
	 */
	void updateRowAvailables();
	
	/**
	 * removes value from the list of possible values of all cells in the same column
	 */
	void updateColumnAvailables();
	
	/**
	 * removes value from the list of possible values of all cells in the same block
	 */
	void updateBoxAvailables();

public:
	PlaceValue(Board& board, Cell& cell, int value);
	
	/**
	 * places value in cell and updates possible value list in every affected cell
	 */
	void execute();
	
	/**
	 * undo value placement and all consequent deductions
	 */
	void undo();
};


#endif //SUDOKU_PLACEVALUE_H
