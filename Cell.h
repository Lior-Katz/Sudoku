//
// Created by Lior on 25/10/2023.
//

#ifndef SUDOKU_CELL_H
#define SUDOKU_CELL_H

#include <vector>
#include <numeric>
#include <ostream>

class Cell
{
private:
	const int x; // x coordinate
	
	const int y; // y coordinate
	
	std::vector<int> availableValues; // possible values that the cell can have, in accordance to other cells in the
	// row, column, and block
	
	int value; // value that the cell holds

public:
	/**
	 * constuctor for Cell
	 * @param x x coordinate, must be > 0 and < boardSize
	 * @param y y coordinate, must be > 0 and < boardSize
	 * @param boardSize
	 * @throw std::invalid_argument if one or more of the coordinates doesn't fit the restrictions
	 */
	explicit Cell(int x, int y, int boardSize);
	
	/**
	 * constuctor for Cell
	 * @param x x coordinate, must be > 0 and < boardSize
	 * @param y y coordinate, must be > 0 and < boardSize
	 * @param boardSize
	 * @param value value that the cell has, must be >=0 and <= boardSize
	 * @throw std::invalid_argument if one or more of the arguments doesn't fit the restrictions
	 */
	Cell(int x, int y, int boardSize, int value);
	
	/**
	 *
	 * @return current value of the cell
	 */
	int getValue() const;
	
	/**
	 *
	 * @return x coordinate of the cell
	 */
	int getX() const;
	
	/**
	 *
	 * @return y coordinate of the cell
	 */
	int getY() const;
	
	/**
	 *
	 * @return int array containing all the possible value options for this cell
	 */
	std::vector<int> getAvailableValues() const;
	
	/**
	 * changes the value of the cell
	 * @param newValue must be >= 0, assumed to be smaller than or equal to boardSize
	 * @throws std::invalid_argument if value doesn't fit the restrictions
	 */
	void setValue(int newValue);
	
	/**
	 * deletes valueToDelete from the list of possible value options
	 * @param valueToDelete
	 * @return true if the value existed in the list before deletion, false otherwise
	 */
	bool removeAvailableValue(int valueToDelete);
	
	/**
	 * adds value to list of possible value options
	 * @param valueToAdd must be greater than or equal to 0, assumed to be smaller than or equal to boardSize
	 */
	void addAvailableValue(int valueToAdd);
	
	/**
	 *
	 * @param first
	 * @param second
	 * @return true if the lhs has less available values than the rhs, false otherwise.
	 */
	friend bool operator<(const Cell& first, const Cell& second);
};

/**
 * output operator
 * prints the value of the cell
 * @param os output stream
 * @param cell
 * @return reference to os
 */
std::ostream& operator<<(std::ostream& os, const Cell& cell);

/**
 * inequality operator
 * @param first
 * @param second
 * @return true if the cells have different value, false otherwise
 */
bool operator!=(const Cell& first, const Cell& second);

#endif //SUDOKU_CELL_H
