//
// Created by Lior on 26/10/2023.
//

#include "PlaceValue.h"

void checkRow(Board& board, Cell& cell, std::stack<std::shared_ptr<Command>>& commandLog);

void checkColumn(Board& board, Cell& cell, std::stack<std::shared_ptr<Command>>& commandLog);

void checkBox(Board& board, Cell& cell, std::stack<std::shared_ptr<Command>>& commandLog);

PlaceValue::PlaceValue(Board& board, Cell& cell, int value) :
		Command(cell, value),
		board(board)
{

}

bool PlaceValue::execute()
{
//	std::ofstream out("results", std::ios::app);
	cell.setValue(this->value);
	
	updateRowAvailables();
	updateColumnAvailables();
	updateBoxAvailables();
	
//	out << "set value " << value << " in (" << cell.getX() << ", " << cell.getY() << ")" << std::endl;
//	out << board << std::endl << std::endl;
	
	return true;
}

void PlaceValue::undo()
{
//	std::ofstream out("results", std::ios::app);
	while (!deductions.empty())
	{
		deductions.top()->undo();
		deductions.pop();
		
	}
//	cell.removeAvailableValue(value);
//	cell.addUsedValues(value);//TODO: delete
	cell.setValue(0);
	
//	out << "undo value " << value << " in " << "(" << cell.getX() << ", " << cell.getY() << ")" << std::endl;
//	out << board << std::endl << std::endl;
}

void PlaceValue::updateRowAvailables()
{
	for (int x = 0; x < board.getBoardSize(); ++x)
	{
		if (board[x][cell.getY()].getValue() == 0)
		{
			std::shared_ptr<Command> changeAvailable(new DeleteAvailable(board[x][cell.getY()], value));
			if (changeAvailable->execute())
			{
				deductions.push(changeAvailable);
			}
		}
	}
}

void PlaceValue::updateColumnAvailables()
{
	for (int y = 0; y < board.getBoardSize(); ++y)
	{
		if (board[cell.getX()][y].getValue() == 0)
		{
			std::shared_ptr<Command> changeAvailable(new DeleteAvailable(board[cell.getX()][y], value));
			if (changeAvailable->execute())
			{
				deductions.push(changeAvailable);
			}
		}
	}
}

void PlaceValue::updateBoxAvailables()
{
	for (int i = 0; i < board.getBlockSize(); ++i)
	{
		for (int j = 0; j < board.getBlockSize(); ++j)
		{
			int x = cell.getX() - cell.getX() % board.getBlockSize() + i;
			int y = cell.getY() - cell.getY() % board.getBlockSize() + j;
			
			if (board[x][y].getValue() == 0)
			{
				std::shared_ptr<Command> changeAvailable(new DeleteAvailable(board[x][y], value));
				if (changeAvailable->execute())
				{
					deductions.push(changeAvailable);
				}
			}
		}
	}
}



