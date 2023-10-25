//
// Created by Lior on 25/10/2023.
//

#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H

#include "vector"
#include "stack"
#include "Cell.h"
#include "Command.h"

class Game
{
private:
	int size;
	
	int boxSize;
	
	std::vector<std::vector<Cell>> board;
	
	std::vector<Cell*> freeCells;
	
	std::stack<Command> moves;
	
public:
	
	
	explicit Game(int size, int boxSize) :
			size(size),
			boxSize(boxSize)
	{
	};
	
	Game() = delete;
	
	void initializeGame();
	
	void solve();
	
	void updateAvailables();
	
};


#endif //SUDOKU_GAME_H
