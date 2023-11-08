//
// Created by Lior on 26/10/2023.
//

#include "DeleteAvailable.h"

DeleteAvailable::DeleteAvailable(Cell& cell, int value) :
		cell(cell),
		value(value)
{
}

bool DeleteAvailable::execute()
{
	if (cell.removeAvailableValue(value))
	{
		return true;
	}
	return false;
}

void DeleteAvailable::undo()
{
	cell.addAvailableValue(value);
}

