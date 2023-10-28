//
// Created by Lior on 27/10/2023.
//

#include "Board.h"

Cell& Board::Iterator::operator*()
{
	if (x == itBoard.getBoardSize() || y == itBoard.getBoardSize())
	{
		throw std::runtime_error("Invalid dereference");
	}
	
	return itBoard[x][y];
}

Board::Iterator& Board::Iterator::operator++()
{
	if (this->x == itBoard.getBoardSize() || this->y == itBoard.getBoardSize())
	{
		throw std::runtime_error("");
	}
	++this->x;
	if (this->x == itBoard.getBoardSize())
	{
		this->x = 0;
		++this->y;
	}
	
	return *this;
}

bool Board::Iterator::operator!=(const Board::Iterator& iterator) const
{
	if ((this->x >= itBoard.getBoardSize() || this->y >= itBoard.getBoardSize()) && (iterator.x >= iterator.itBoard
	.getBoardSize() || iterator.y >= iterator.itBoard.getBoardSize()))
	{
		return false;
	}
	return ! (this->x == iterator.x && this->y == iterator.y);
}

Board::Board(std::vector<std::vector<Cell>>& board, int boxSize, int boardSize) :
		boardSize(boardSize),
		boxSize(boxSize),
		board(board)
{

}

int Board::getBoardSize() const
{
	return this->boardSize;
}

int Board::getBoxSize() const
{
	return this->boxSize;
}

const std::vector<Cell>& Board::operator[](int x) const
{
	return this->board[x];
}

std::vector<Cell>& Board::operator[](int x)
{
	return this->board[x];
}
