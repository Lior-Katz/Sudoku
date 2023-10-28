//
// Created by Lior on 27/10/2023.
//

#ifndef SUDOKU_BOARD_H
#define SUDOKU_BOARD_H

#include <vector>
#include "stdexcept"
#include "Cell.h"

class Board
{
private:
	int boardSize;
	
	int boxSize;
	
	std::vector<std::vector<Cell>> board;

public:
	Board(std::vector<std::vector<Cell>>& board, int boxSize, int boardSize);
	
	int getBoardSize() const;
	
	int getBoxSize() const;
	
	const std::vector<Cell>& operator[](int x) const;
	
	std::vector<Cell>& operator[](int x);
	
	class Iterator
	{
	private:
		Board& itBoard;
		
		int x, y;
		
		explicit Iterator(Board& itBoard, int x, int y) :
				itBoard(itBoard),
				x(x),
				y(y)
		{
		}
		
		friend class Board;
	
	public:
		Cell& operator*();
		
		Iterator& operator++();
		
		bool operator!=(const Iterator& iterator) const;
		
		Iterator() = delete;
	};
	
	Iterator begin()
	{
		return Iterator(*this, 0, 0);
	}
	
	Iterator end()
	{
		return Iterator(*this, boardSize, boardSize);
	}
	
};


#endif //SUDOKU_BOARD_H
