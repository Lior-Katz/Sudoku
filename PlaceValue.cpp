//
// Created by Lior on 26/10/2023.
//

#include "PlaceValue.h"

PlaceValue::PlaceValue(Board& board, Cell& cell, int value) :
		board(board),
		cell(cell),
		value(value)
{

}

void PlaceValue::execute()
{
	cell.setValue(this->value);
	
	updateRowAvailables();
	updateColumnAvailables();
	updateBoxAvailables();
}

void PlaceValue::undo()
{
	while (!deductions.empty())
	{
		deductions.top().undo();
		deductions.pop();
		
	}
	cell.setValue(0);
	
}

void PlaceValue::updateRowAvailables()
{
	for (int x = 0; x < board.getBoardSize(); ++x)
	{
		if (board[x][cell.getY()].getValue() == 0)
		{
			DeleteAvailable changeAvailable(board[x][cell.getY()], value);
			if (changeAvailable.execute())
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
			DeleteAvailable changeAvailable(board[cell.getX()][y], value);
			if (changeAvailable.execute())
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
				DeleteAvailable changeAvailable(board[x][y], value);
				if (changeAvailable.execute())
				{
					deductions.push(changeAvailable);
				}
			}
		}
	}
}



