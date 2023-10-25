//
// Created by Lior on 26/10/2023.
//

#ifndef SUDOKU_CHANGEAVAILABLE_H
#define SUDOKU_CHANGEAVAILABLE_H

#include "Command.h"

class ChangeAvailable : public Command
{
	ChangeAvailable(Cell cell, int value);
	
	void execute() override;
	
	void undo() override;
};


#endif //SUDOKU_CHANGEAVAILABLE_H
