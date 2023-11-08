//
// Created by Lior on 25/10/2023.
//

#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H

#include <vector>
#include <stack>
#include <memory>
#include "Cell.h"
#include <iostream>
#include "PlaceValue.h"
#include "Board.h"
#include "DeleteAvailable.h"
#include <algorithm>


class Game
{
private:
	Board board;
	
	std::vector<Cell*> freeCells; // cell's that a value hasn't been placed in yet
	
	std::stack<PlaceValue> commandLog; // FILO log of all value placements that have
	
	/**
	 * backtracks through all possible ways to solve the puzzle
	 * @return true if a solution has been found, false if no possible solution exists from the current state
	 */
	bool isSolved();
	
	/**
	 * initializes list of free cells and sorts the list
	 */
	void initializeGame();

public:
	
	explicit Game(std::vector<std::vector<Cell>> startingBoard) :
			board(startingBoard)
	{
	};
	
	Game() = delete;
	
	/**
	 * solves the puzzle using backtracking algorithm
	 * @return true if the puzzle is solved, false if no solution exists
	 */
	bool solve();
	
	/**
	 * @return a const Board reference of the current state of the game
	 */
	const Board& getBoard() const;
	
};


#endif //SUDOKU_GAME_H
