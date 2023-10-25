//
// Created by Lior on 25/10/2023.
//

#include "Cell.h"

Cell::Cell(int x, int y, int size) :
		x(x),
		y(y),
		available(std::vector<int>(size)),
		value(0)
{
	std::iota(available.begin(), available.end(), 1);
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

