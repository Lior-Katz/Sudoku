//
// Created by Lior on 27/10/2023.
//

#ifndef SUDOKU_BOARD_H
#define SUDOKU_BOARD_H

#include <vector>
#include "stdexcept"
#include "Cell.h"
#include "ostream"

class Board
{
private:
	int boardSize; // number of cells across the board
	
	int blockSize; // number of cells acroos each block
	
	std::vector<std::vector<Cell>> board; // 2D array representing the sudoku

public:
	
	/**
	 * Constructor for Board
	 * Creates a Board object
	 * @param board 2D array of Cells that represents the sudoku, assumed to be square
	 */
	explicit Board(std::vector<std::vector<Cell>>& board);
	
	/**
	 *
	 * @return size of sudoku
	 */
	int getBoardSize() const;
	
	/**
	 *
	 * @return size of each block
	 */
	int getBlockSize() const;
	
	/**
	 * const subscript operator
	 * @param x 0-based horizontal coordinate in of the board
	 * @return a const array of Cells representing a column of the board
	 */
	const std::vector<Cell>& operator[](int x) const;
	
	/**
	 * subscript operator
	 * @param x 0-based horizontal coordinate in of the board
	 * @return an array of Cells representing a column of the board
	 */
	std::vector<Cell>& operator[](int x);
	
	class Iterator
	{
	private:
		Board& itBoard;
		
		int x, y;
		
		/**
		 * Iterator constructor
		 * creates a new instance of Iterator that points to a cell with co'ords (x, y) in itBoard
		 * @param itBoard Board that the iterator iterates through
		 * @param x x co'ord
		 * @param y y co'ord
		 */
		explicit Iterator(Board& itBoard, int x, int y);
		
		friend class Board;
	
	public:
		/**
		 * dereference operator
		 * @return a reference to the cell the iterator points to
		 */
		Cell& operator*();
		
		/**
		 * prefix increment operator
		 * increments to the next cell in the current row, and loops back to the first cell in the next row
		 * @return this after increment
		 */
		Iterator& operator++();
		
		/**
		 * inequality operator
		 * a comparison is valid only if both iterators are of the same board
		 * @param iterator Iterator to compare
		 * @return true if iterators point to different cells (by coordinates) or only one iterator points to the end
		 * 			false if both iterators point to the same cell (by coordinates or both point to the end od the board
		 */
		bool operator!=(const Iterator& iterator) const;
		
		Iterator() = delete;
	};
	
	/**
	 *
	 * @return an Iterator to the first cell of the board with coordinates (0, 0)
	 */
	Iterator begin()
	{
		return Iterator(*this, 0, 0);
	}
	
	/**
	 *
	 * @return an Iterator to the past-the-end element of the board
	 */
	Iterator end()
	{
		return Iterator(*this, boardSize, boardSize);
	}
	
	class ConstIterator
	{
	private:
		const Board& itBoard;
		
		int x, y;
		
		/**
		 * ConstIterator constructor
		 * creates a new instance of ConstIterator that points to a cell with co'ords (x, y) in itBoard
		 * @param itBoard Board that the iterator iterates through
		 * @param x x co'ord
		 * @param y y co'ord
		 */
		explicit ConstIterator(const Board& itBoard, int x, int y) :
				itBoard(itBoard),
				x(x),
				y(y)
		{
		}
		
		friend class Board;
	
	public:
		/**
		 * dereference operator
		 * @return a const reference to the cell the iterator points to
		 */
		const Cell& operator*() const;
		
		/**
		 * prefix increment operator
		 * increments to the next cell in the current row, and loops back to the first cell in the next row
		 * @return this after increment
		 */
		ConstIterator& operator++();
		
		/**
		 * inequality operator
		 * a comparison is valid only if both iterators are of the same board
		 * @param iterator ConstIterator to compare
		 * @return true if iterators point to different cells (by coordinates) or only one iterator points to the end
		 * 			false if both iterators point to the same cell (by coordinates or both point to the end od the board
		 */
		bool operator!=(const ConstIterator& iterator) const;
		
		ConstIterator() = delete;
	};
	
	/**
	 *
	 * @return a ConstIterator to the first cell of the board with coordinates (0, 0)
	 */
	ConstIterator begin() const
	{
		return ConstIterator(*this, 0, 0);
	}
	
	/**
	 *
	 * @return a ConstIterator to the past-the-end element of the board
	 */
	ConstIterator end() const
	{
		return ConstIterator(*this, boardSize, boardSize);
	}
	
};

/**
 * output operator
 * prints the current state of the board, with vertical lines and dashes separating blocks, and 0 for empty cells
 * For example, a 4x4 board will be printed as following:
 * 0 1 | 3 0
 * 2 0 | 4 1
 * ---------
 * 0 0 | 2 0
 * 0 3 | 1 0
 * ---------
 * @param os output stream
 * @param board Board to print
 * @return reference to os for concatenation
 */
std::ostream& operator<<(std::ostream& os, const Board& board);

/**
 * equality operator
 * @param first const refernce to a Board
 * @param second const refernce to a Board
 * @return true if both boards have the same value in every cell, false otherwise
 * @throw std::invalid_argument if boards are of different sizes
 */
bool operator==(const Board& first, const Board& second);

/**
 * inequality operator
 * @param first const refernce to a Board
 * @param second const refernce to a Board
 * @return true if the boards differ in the value of at least one cell, false otherwise
 * @throw std::invalid_argument if boards are of different sizes
 */
bool operator!=(const Board& first, const Board& second);

#endif //SUDOKU_BOARD_H
