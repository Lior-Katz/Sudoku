//
// Created by Lior on 25/10/2023.
//

#include "Game.h"


void checkRow(Board& board, Cell& cell, std::stack<std::shared_ptr<Command>>& commandLog);

void checkColumn(Board& board, Cell& cell, std::stack<std::shared_ptr<Command>>& commandLog);

void checkBox(Board& board, Cell& cell, std::stack<std::shared_ptr<Command>>& commandLog);

void Game::initializeGame()
{
	for (Cell& cell : board)
	{
		if (cell.getValue() == 0)
		{
			freeCells.push_back(&cell);
		}
	}
	
	for (Cell* pCell : freeCells)
	{
		checkRow(board, *pCell, commandLog);
		checkColumn(board, *pCell, commandLog);
		checkBox(board, *pCell, commandLog);
	}
	
	std::sort(freeCells.begin(), freeCells.end(), [](const Cell* pCell1, const Cell* pCell2) {
		return pCell1->getAvailableValues().size() < pCell2->getAvailableValues().size();
	});
}

bool Game::solve(int min, int current)
{
	initializeGame();
	
	return isSolved(min, current);
}

bool Game::isSolved(int min, int current)
{
	if (freeCells.empty())
	{
		//std::cout << this->board;
		return true;
	}
	if( min != 0 && current >= min)
	{
		std::cout << board<< std::endl << std::endl << std::endl;
	}
	Cell& cell = *freeCells.front();
	if (cell.getAvailableValues().empty())
	{
		return false;
	}
	
	freeCells.erase(freeCells.begin());
	for (int value : cell.getAvailableValues())
	{
		std::shared_ptr<Command> placeValue(new PlaceValue(board, cell, value));
		placeValue->execute();
		commandLog.push(placeValue);
		std::sort(freeCells.begin(), freeCells.end(), [](const Cell* pCell1, const Cell* pCell2) {
			return pCell1->getAvailableValues().size() < pCell2->getAvailableValues().size();
		});
		
		if (isSolved(min, current))
		{
			return true;
		}
		
		commandLog.top()->undo();
		commandLog.pop();
		std::sort(freeCells.begin(), freeCells.end());
	}
	freeCells.push_back(&cell);
	return false;
}

const Board& Game::getBoard() const
{
	return this->board;
}

//TODO: get rid of code duplication between checking row, column and box; in PlaceValue::execute()
void checkRow(Board& board, Cell& cell, std::stack<std::shared_ptr<Command>>& commandLog)
{
	for (int i = 0; i < board.getBoardSize(); ++i)
	{
		if (i == cell.getX())
		{
			continue;
		}
		
		if (board[i][cell.getY()].getValue() != 0)
		{
			cell.removeAvailableValue(board[i][cell.getY()].getValue());
		}
	}
}

void checkColumn(Board& board, Cell& cell, std::stack<std::shared_ptr<Command>>& commandLog)
{
	for (int i = 0; i < board.getBoardSize(); ++i)
	{
		if (i == cell.getY())
		{
			continue;
		}
		
		if (board[cell.getX()][i].getValue() != 0)
		{
			
			cell.removeAvailableValue(board[cell.getX()][i].getValue());
		}
	}
}

void checkBox(Board& board, Cell& cell, std::stack<std::shared_ptr<Command>>& commandLog)
{
	for (int i = 0; i < board.getBoxSize(); ++i)
	{
		for (int j = 0; j < board.getBoxSize(); ++j)
		{
			int x = cell.getX() - cell.getX() % board.getBoxSize() + i;
			int y = cell.getY() - cell.getY() % board.getBoxSize() + j;
			
			if (cell.getX() == x && cell.getY() == y)
			{
				continue;
			}
			
			if (board[x][y].getValue() != 0)
			{
				cell.removeAvailableValue(board[x][y].getValue());
			}
		}
	}
}
