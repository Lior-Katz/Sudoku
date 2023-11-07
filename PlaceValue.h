//
// Created by Lior on 26/10/2023.
//

#ifndef SUDOKU_PLACEVALUE_H
#define SUDOKU_PLACEVALUE_H

#include "Command.h"
#include "vector"
#include "stack"
#include "Board.h"
#include "DeleteAvailable.h"
#include "memory"

class PlaceValue : public Command
{
protected:
	Board& board;
	
	std::stack<std::shared_ptr<Command>> deductions;
	
	void updateRowAvailables();
	
	void updateColumnAvailables();
	
	void updateBoxAvailables();

public:
	PlaceValue(Board& board, Cell& cell, int value);
	
	bool execute() override;
	
	void undo() override;
};


#endif //SUDOKU_PLACEVALUE_H
