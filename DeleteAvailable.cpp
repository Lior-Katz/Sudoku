//
// Created by Lior on 26/10/2023.
//

#include "DeleteAvailable.h"

DeleteAvailable::DeleteAvailable(Cell& cell, int value) :
		Command(cell, value)
{

}

void DeleteAvailable::execute()
{
	cell.removeAvailableValue(value);
}

void DeleteAvailable::undo()
{
	cell.addAvailableValue(value);
}

