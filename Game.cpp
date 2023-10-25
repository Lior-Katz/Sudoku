//
// Created by Lior on 25/10/2023.
//

#include "Game.h"

void checkRow(std::vector<std::vector<Cell>>& board, int size, Cell& cell);

void checkColumn(std::vector<std::vector<Cell>>& board, int size, Cell& cell);

void checkBox(std::vector<std::vector<Cell>>& board, int size, int boxSize, Cell& cell);

void Game::updateAvailables()
{
	for (Cell* pCell : freeCells)
	{
		checkRow(board, size, *pCell);
		checkColumn(board, size, *pCell);
		checkBox(board, size, boxSize, *pCell);
	}
}

void checkRow(std::vector<std::vector<Cell>>& board, int size, Cell& cell)
{
	for (int i = 0; i < size; ++i)
	{
		if( i == cell.getX())
			continue;
		
		if (board[i][cell.getY()].getValue() != 0)
		{
			cell.removeAvailable(board[i][cell.getY()].getValue());
		}
	}
}

void checkColumn(std::vector<std::vector<Cell>>& board, int size, Cell& cell)
{
	for (int i = 0; i < size; ++i)
	{
		if( i == cell.getY())
			continue;
		
		if (board[cell.getX()][i].getValue() != 0)
		{
			cell.removeAvailable(board[cell.getY()][i].getValue());
		}
	}
}

void checkBox(std::vector<std::vector<Cell>>& board, int size, int boxSize, Cell& cell)
{
	for (int i = 0; i < boxSize; ++i)
	{
		for (int j = 0; j < boxSize; ++j)
		{
			int x = cell.getX() - cell.getX() % boxSize + i;
			int y = cell.getY() - cell.getY() % boxSize + j;
			
			if(cell.getX() == x && cell.getY() == y)
				continue;
			
			if (board[x][y].getValue() != 0)
			{
				cell.removeAvailable(board[x][y].getValue());
			}
		}
	}
}
