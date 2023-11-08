//
// Created by Lior on 25/10/2023.
//

#include "Game.h"

void Game::initializeGame()
{
	for (Cell& cell : board)
	{
		if (cell.getValue() == 0)
		{
			freeCells.push_back(&cell);
		}
		else
		{
			PlaceValue placeValue(this->board, cell, cell.getValue());
			placeValue.execute();
		}
	}
	
	std::sort(freeCells.begin(), freeCells.end(), [](const Cell* pCell1, const Cell* pCell2) {
		return pCell1->getAvailableValues().size() < pCell2->getAvailableValues().size();
	});
}

bool Game::solve()
{
	initializeGame();
	
	return isSolved();
}

bool Game::isSolved()
{
	if (freeCells.empty())
	{
		return true;
	}
	
	Cell& cell = *freeCells.front();
	if (cell.getAvailableValues().empty())
	{
		return false;
	}
	
	freeCells.erase(freeCells.begin());
	for (int value : cell.getAvailableValues())
	{
		PlaceValue placeValue(board, cell, value);
		placeValue.execute();
		commandLog.push(placeValue);
		std::sort(freeCells.begin(), freeCells.end(), [](const Cell* pCell1, const Cell* pCell2) {
			return pCell1->getAvailableValues().size() < pCell2->getAvailableValues().size();
		});
		
		if (isSolved())
		{
			return true;
		}
		
		commandLog.top().undo();
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