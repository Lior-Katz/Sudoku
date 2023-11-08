//
// Created by Lior on 25/10/2023.
//

#include "Cell.h"

Cell::Cell(int x, int y, int boardSize) :
		x(x),
		y(y),
		availableValues(std::vector<int>(boardSize)),
		value(0)
{
	if (x < 0 || x >= boardSize || y < 0 || y >= boardSize)
	{
		throw std::invalid_argument("invalid cell coordinates, must be between 0 and boardSize");
	}
	std::iota(availableValues.begin(), availableValues.end(), 1);
}

Cell::Cell(int x, int y, int boardSize, int value) :
		x(x),
		y(y),
		availableValues(std::vector<int>(boardSize)),
		value(value)
{
	if (x < 0 || x >= boardSize || y < 0 || y >= boardSize)
	{
		throw std::invalid_argument("invalid cell coordinates, must be between 0 and boardSize");
	}
	if (value < 0 || value > boardSize)
	{
		throw std::invalid_argument("invalid value, must be between greater or equal to 0 and smaller than "
									"boardSize");
	}
	std::iota(availableValues.begin(), availableValues.end(), 1);
}

int Cell::getValue() const
{
	return this->value;
}

void Cell::setValue(int newValue)
{
	if (value < 0)
	{
		throw std::invalid_argument("invalid value, must be between greater than or equal to 0 ");
	}
	this->value = newValue;
}

int Cell::getX() const
{
	return this->x;
}

int Cell::getY() const
{
	return this->y;
}

bool Cell::removeAvailableValue(int valueToDelete)
{
	for (auto it = this->availableValues.begin(); it != this->availableValues.end(); ++it)
	{
		if (*it == valueToDelete)
		{
			this->availableValues.erase(it);
			return true;
		}
	}
	return false;
}

void Cell::addAvailableValue(int valueToAdd)
{
	if (value < 0)
	{
		throw std::invalid_argument("invalid value, must be between greater than or equal to 0 ");
	}
	for (int num : this->availableValues)
	{
		if (num == valueToAdd)
		{
			return;
		}
	}
	
	availableValues.push_back(valueToAdd);
}

std::vector<int> Cell::getAvailableValues() const
{
	return availableValues;
}

bool operator<(const Cell& first, const Cell& second)
{
	return first.availableValues.size() < second.availableValues.size();
}

bool operator!=(const Cell& first, const Cell& second)
{
	return first.getValue() != second.getValue();
}

std::ostream& operator<<(std::ostream& os, const Cell& cell)
{
	os << cell.getValue() << " ";
	return os;
}


