//
// Created by Lior on 27/10/2023.
//

#include "Board.h"


Board::Board(std::vector<std::vector<Cell>>& board) :
		board(board)
{
	this->boardSize = board.size();
	int size = 0;
	while (size * size != boardSize)
	{
		++size;
	}
	this->boxSize = size;
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

bool operator==(const Board& first, const Board& second)
{
	if (first.getBoardSize() != second.getBoardSize())
	{
		throw std::invalid_argument("Invalid comparison between boards of different sizes");
	}
	
	for (auto it1 = first.begin(), it2 = second.begin(); it1 != first.end(); ++it1, ++it2)
	{
		if (*it1 != *it2)
		{
			return false;
		}
	}
	
	return true;
}

bool operator!=(const Board& first, const Board& second)
{
	return !(first == second);
}

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
	if ((this->x >= itBoard.getBoardSize() || this->y >= itBoard.getBoardSize()) && (iterator.x >= iterator.itBoard.getBoardSize() || iterator.y >= iterator.itBoard.getBoardSize()))
	{
		return false;
	}
	return !(this->x == iterator.x && this->y == iterator.y);
}

const Cell& Board::ConstIterator::operator*() const
{
	if (x == itBoard.getBoardSize() || y == itBoard.getBoardSize())
	{
		throw std::runtime_error("Invalid dereference");
	}
	
	return itBoard[x][y];
}

Board::ConstIterator& Board::ConstIterator::operator++()
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

bool Board::ConstIterator::operator!=(const Board::ConstIterator& iterator) const
{
	if ((this->x >= itBoard.getBoardSize() || this->y >= itBoard.getBoardSize()) && (iterator.x >= iterator.itBoard.getBoardSize() || iterator.y >= iterator.itBoard.getBoardSize()))
	{
		return false;
	}
	return !(this->x == iterator.x && this->y == iterator.y);
}

std::ostream& operator<<(std::ostream& os, const Board& board)
{
	int row = 0, column = 0;
	for (const Cell& cell : board)
	{
		++column;
		os << cell;
		if (column == board.getBoardSize())
		{
			os << std::endl;
			column = 0;
			++row;
			if (row % board.getBoxSize() == 0)
			{
				for (int i = 0; i < board.getBoardSize(); ++i)
				{
					os << "- ";
				}
				os << std::endl;
			}
		}
		else if (column % board.getBoxSize() == 0)
		{
			os << "| ";
		}
		
	}
	return os;
}
