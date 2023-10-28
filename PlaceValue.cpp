//
// Created by Lior on 26/10/2023.
//

#include "PlaceValue.h"

void checkRow(Board& board, Cell& cell, std::stack<std::shared_ptr<Command>>& commandLog);

void checkColumn(Board& board, Cell& cell, std::stack<std::shared_ptr<Command>>& commandLog);

void checkBox(Board& board, Cell& cell, std::stack<std::shared_ptr<Command>>& commandLog);

PlaceValue::PlaceValue(Board& board, Cell &cell, int value) :
		Command(cell, value),
		board(board)
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
		deductions.top()->undo();
		deductions.pop();
		cell.removeAvailableValue(value);
		cell.setValue(0);
	}
}

void PlaceValue::updateRowAvailables()
{
	for (int x = 0; x < board.getBoardSize(); ++x)
	{
		if (board[x][cell.getY()].getValue() == 0)
		{
			std::shared_ptr<Command> changeAvailable(new DeleteAvailable(board[x][cell.getY()], value));
			changeAvailable->execute();
			deductions.push(changeAvailable);
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
			changeAvailable->execute();
			deductions.push(changeAvailable);
		}
	}
}

void PlaceValue::updateBoxAvailables()
{
	for (int i = 0; i < board.getBoxSize(); ++i)
	{
		for (int j = 0; j < board.getBoxSize(); ++j)
		{
			int x = cell.getX() - cell.getX() % board.getBoxSize() + i;
			int y = cell.getY() - cell.getY() % board.getBoxSize() + j;
			
			if (board[x][y].getValue() == 0)
			{
				std::shared_ptr<Command> changeAvailable(new DeleteAvailable(board[x][y], value));
				changeAvailable->execute();
				deductions.push(changeAvailable);
			}
		}
	}
}



