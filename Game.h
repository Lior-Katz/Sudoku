//
// Created by Lior on 25/10/2023.
//

#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H

#include <vector>
#include <stack>
#include <memory>
#include "Cell.h"
#include "Command.h"
#include <iostream>
#include "PlaceValue.h"
#include "Board.h"
#include "DeleteAvailable.h"
#include <algorithm>


class Game
{
private:
	Board board;
	
	std::vector<Cell*> freeCells;
	
	std::stack<std::shared_ptr<Command>> commandLog;
	
	bool isSolved(int min = 0, int current = 0);
	
	void initializeGame();
	
public:
	
	
	explicit Game(std::vector<std::vector<Cell>> startingBoard) :
			board(startingBoard)
	{
	};
	
	
	Game() = delete;
	
	bool solve(int min = 0, int current = 0);
	
	const Board& getBoard() const;
	
};


#endif //SUDOKU_GAME_H
