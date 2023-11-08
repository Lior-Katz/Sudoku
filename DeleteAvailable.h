//
// Created by Lior on 26/10/2023.
//

#ifndef SUDOKU_DELETEAVAILABLE_H
#define SUDOKU_DELETEAVAILABLE_H

#include "Cell.h"

class DeleteAvailable
{
private:
	Cell& cell; // cell that this command acts upon
	
	int value; // value to delete from cell's possible value options

public:
	
	/**
	 * constructor for DeleteAvailable
	 * @param cell cell that this command acts upon
	 * @param value value to delete from cell's possible value options
	 * 				must be greater than 0
	 * 				assumed to be smaller than boardSize
	 * 	@throw std::invalid_argument if value is smaller than or equal to 0
	 */
	DeleteAvailable(Cell& cell, int value);
	
	/**
	 * deletes value from cell's list of possible values
	 * @return true if value appeared in the list prior to function call, false otherwise
	 */
	bool execute();
	
	/**
	 * adds value to cell's list of possible values
	 */
	void undo();
};


#endif //SUDOKU_DELETEAVAILABLE_H
