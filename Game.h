//
// Created by Lior on 25/10/2023.
//

#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H

#include "vector"
#include "stack"
#include "memory"
#include "Cell.h"
#include "Command.h"
#include "Board.h"


class Game
{
private:
	Board board;
	
	std::vector<Cell*> freeCells;
	
	std::stack<std::shared_ptr<Command>> commandLog;
	
	bool isSolved();
	
public:
	
	
	explicit Game(std::vector<std::vector<Cell>> startingBoard, int size, int boxSize) :
			board(startingBoard, boxSize, size)
	{
	};
	
	
	Game() = delete;
	
	void initializeGame();
	
	bool solve();
	
	
	
	
};


#endif //SUDOKU_GAME_H
