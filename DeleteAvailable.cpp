//
// Created by Lior on 26/10/2023.
//

#include "DeleteAvailable.h"

DeleteAvailable::DeleteAvailable(Cell& cell, int value) :
		cell(cell),
		value(value)
{
	if (value <= 0)
	{
		throw std::invalid_argument("Invalid value, must be greater than 0");
	}
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

