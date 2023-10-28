//
// Created by Lior on 26/10/2023.
//

#ifndef SUDOKU_DELETEAVAILABLE_H
#define SUDOKU_DELETEAVAILABLE_H

#include "Command.h"

class DeleteAvailable : public Command
{
public:
	DeleteAvailable(Cell& cell, int value);
	
	void execute() override;
	
	void undo() override;
};


#endif //SUDOKU_DELETEAVAILABLE_H
