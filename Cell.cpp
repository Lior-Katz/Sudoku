//
// Created by Lior on 25/10/2023.
//

#include "Cell.h"

Cell::Cell(int x, int y, int size) :
		x(x),
		y(y),
		availableValues(std::vector<int>(size)),
		value(0)
{
	std::iota(availableValues.begin(), availableValues.end(), 1);
}

Cell::Cell(int x, int y, int size, int value) :
		x(x),
		y(y),
		availableValues(std::vector<int>(size)),
		value(value)
{

}

int Cell::getValue() const
{
	return this->value;
}

void Cell::setValue(int newValue)
{
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

void Cell::removeAvailableValue(int valueToDelete)
{
	for (auto it = this->availableValues.begin(); it != this->availableValues.end(); ++it)
	{
		if (*it == valueToDelete)
		{
			this->availableValues.erase(it);
			return;
		}
	}
}

void Cell::addAvailableValue(int valueToAdd)
{
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


