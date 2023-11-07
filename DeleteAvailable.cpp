//
// Created by Lior on 26/10/2023.
//

#include "DeleteAvailable.h"

DeleteAvailable::DeleteAvailable(Cell& cell, int value) :
		Command(cell, value)
{

}

bool DeleteAvailable::execute()
{
//	std::ofstream out("results", std::ios::app);
	
	if (cell.removeAvailableValue(value))
	{
//		out << "delete available value " << value << " in " << "(" << cell.getX() << ", " << cell.getY() << ")"
//			<< std::endl;
		return true;
	}
	return false;
	
	
}

void DeleteAvailable::undo()
{
//	std::ofstream out("results", std::ios::app);
	
	cell.addAvailableValue(value);
//	out << "add available value " << value << " in " << "(" << cell.getX() << ", " << cell.getY() << ")" <<
//			  std::endl;
}

