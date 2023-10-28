#include <iostream>
#include "Game.h"

int main()
{
	
	std::vector<std::vector<Cell>> board = {{Cell(0, 0, 4, 1), Cell(0, 1, 4, 4), Cell(0, 2, 4, 3), Cell(0, 3, 4)},
											{Cell(1, 0, 4, 2), Cell(1, 1, 4), Cell(1, 2, 4), Cell(1, 3, 4, 1)},
											{Cell(2, 0, 4, 3), Cell(2, 1, 4, 1), Cell(2, 2, 4), Cell(2, 3, 4, 4)},
											{Cell(3, 0, 4), Cell(3, 1, 4, 2), Cell(3, 2, 4, 1), Cell(3, 3, 4)}};
	
	Game game(board, 4, 2);
	game.solve();
	std::cout << "Hello, World!" << std::endl;
	return 0;
}
