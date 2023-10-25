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
	std::vector<std::vector<Cell>> board;
	std::stack<Command> moves;
	
public:
	
	
	explicit Game(int size) :
			size(size)
	{
	};
	
	Game() = delete;
	
	void initializeGame();
	
	void solve();
	
};


#endif //SUDOKU_GAME_H
