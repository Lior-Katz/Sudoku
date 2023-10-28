//
// Created by Lior on 25/10/2023.
//

#ifndef SUDOKU_CELL_H
#define SUDOKU_CELL_H

#include "vector"
#include "numeric"
class Cell
{
private:
	const int x;
	
	const int y;
	
	std::vector<int> availableValues;
	
	int value;

public:
	explicit Cell(int x, int y, int size);
	
	Cell(int x, int y, int size, int value);
	
	int getValue() const;
	
	int getX() const;
	
	int getY() const;
	
	std::vector<int> getAvailableValues() const;
	
	void setValue(int newValue);
	
	void removeAvailableValue(int valueToDelete);
	
	void addAvailableValue(int valueToAdd);
	
	friend bool operator<(const Cell& first, const Cell& second);
};


#endif //SUDOKU_CELL_H
