//
// Created by Lior on 26/10/2023.
//

#ifndef SUDOKU_PLACEVALUE_H
#define SUDOKU_PLACEVALUE_H

#include "Command.h"

class PlaceValue : public Command
{
	PlaceValue(Cell cell, int value);
	
	void execute() override;
	
	void undo() override;
};


#endif //SUDOKU_PLACEVALUE_H
