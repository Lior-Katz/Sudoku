#include <iostream>
#include "Game.h"
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

vector<vector<Cell>> createBoard(const string& desc);

vector<string> readFile(const string& fileName);

bool testSolver(const string& fileName);

vector<vector<Cell>> createBoard(const string& desc)
{
	vector<vector<Cell>> board;
	int size = 0;
	while (size * size != desc.size())
	{
		++size;
	}
	
	
	for (int column = 0; column < size; ++column)
	{
		vector<Cell> colVec;
		for (int row = 0; row < size; ++row)
		{
			int value = desc[row * size + column] - '0';
			if (value == '.' - '0')
			{
				value = 0;
			}
			colVec.push_back(Cell(column, row, size, value));
		}
		board.push_back(colVec);
	}
	
	return board;
}

vector<string> readFile(const string& fileName)
{

}

bool testSolver(const string& fileName)
{
	int failure = 0;
	int total = 0;
	ifstream puzzlesFile(fileName);
	string line;
	
	while (getline(puzzlesFile, line))
	{
		++total;
		if(total > 10) return false;
		
		vector<string> desc(2);
		
		stringstream ss(line);
		getline(ss, desc[0], ':');
		getline(ss, desc[1], ':');
		
		vector<vector<Cell>> puzzle = createBoard(desc[0]);
		vector<vector<Cell>> solution = createBoard(desc[1]);
		Game game(puzzle);
		game.solve(10, total);
		if (game.getBoard() != Board(solution))
		{
			cout << "Failed test: " << total << endl;
			cout << "solved puzzle:" << endl << game.getBoard() << endl;
			cout << "correct solution" << endl << Board(solution) << endl << endl;
			++failure;
		}
	}
	
	cout << "Total games played:" << total << endl;
	cout << "Failed: " << failure << endl;
	
}

int main()
{
	
	//testSolver("test_puzzles.txt");
	
//	vector<vector<Cell>> board1 = {{Cell(0, 0, 4), Cell(0, 1, 4, 4), Cell(0, 2, 4),    Cell(0, 3, 4)},
//								   {Cell(1, 0, 4), Cell(1, 1, 4),    Cell(1, 2, 4, 3), Cell(1, 3, 4)},
//								   {Cell(2, 0, 4), Cell(2, 1, 4, 2), Cell(2, 2, 4),    Cell(2, 3, 4)},
//								   {Cell(3, 0, 4), Cell(3, 1, 4),    Cell(3, 2, 4, 1), Cell(3, 3, 4)}};
//
//	vector<string> descs = readFile("test_puzzles.txt");
//
//	vector<vector<Cell>> board2 = createBoard(descs[0]);
//
//	Board board(board2);
//	cout << board;

//	Game game(board1, 4, 2);
//	game.solve();
//	cout << "Hello, World!" << endl;
	return 0;
}

/*
1...5.2.9..7.......6.......2...........5.1..2....2.39.3.4.9...15...1...3...8...4.
.2....7..4....9.3.6..723.4...83.........1....9....4.6..94....5.5.....6.3.....5...
.......8...6.8.1..7....3..2.47..5...5..32............53....4..7......9...1.9...6.
....5....4....92....9....1.2..6.39....6.....79....43...94...8.......8.9.8......23
....9..5..1.....3...23..7....35...7.8.....2.......64...9..1.....8..6......54....7
1....67.9.5.........9.....8....9..3.....1....9..6..8.1..27.....7..8...4.8...6.1.7
1...5.2.9..71......6.......2...........5.1..2....2.39.3...9...15...1...3...8...4.
..3......4...8..37..8...1...4..6..73...9...1......2.....4.7..686....4...7.....5..
.23.....94.....1...9..3..4.2..91...4.....78..9...4...23...9...1.6..........5.....
1....6.8....7......9..5.......56..3.3.............38.15....1.6.....2.4..8.2..5.1.
 */
