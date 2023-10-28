//
// Created by Lior on 25/10/2023.
//

#ifndef SUDOKU_COMMAND_H
#define SUDOKU_COMMAND_H

#include "Cell.h"

class Command
{
protected:
	Cell& cell;
	
	int value;

public:
	Command(Cell& pCell, int value);
	
	virtual void execute() = 0;
	
	virtual void undo() = 0;
};


#endif //SUDOKU_COMMAND_H
