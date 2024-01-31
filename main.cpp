#include <iostream>
#include "Game.h"
#include "Testing/TestParser.h"
#include <vector>
#include <fstream>

using namespace std;

vector<vector<Cell>> createBoard(const string& desc);

tuple<int, int> testSolver(int testNum);

vector<string> get_all_files_names_within_folder(const string& folder);

bool runTest(const string& puzzleStr, const string& solutionStr, int total);

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
			if (!(value >= 0 && value <= 9))
			{
				value = desc[row * size + column] - 'A' + 10;
			}
			colVec.push_back(Cell(column, row, size, value));
		}
		board.push_back(colVec);
	}
	
	return board;
}

bool runTest(const string& puzzleStr, const string& solutionStr, int total)
{
	ofstream out("results", ios::app);
	
	vector<vector<Cell>> puzzle = createBoard(puzzleStr);
	vector<vector<Cell>> solution = createBoard(solutionStr);
	Game game(puzzle);
	game.solve();
	
	if (solutionStr.empty())
	{
		if (game.getBoard() != Board(puzzle))
		{
			out << "Failed test: " << total << endl;
			out << "solved puzzle:" << endl << game.getBoard() << endl;
			out << "correct solution" << endl << "This puzzle has no solution. Expected solved puzzle to be identical"
												 " to initial condition:" << Board(puzzle) << endl << endl;
			return false;
		}
		return true;
	}
	if (game.getBoard() != Board(solution))
	{
		out << "Failed puzzle: " << total << endl;
		out << "solved puzzle:" << endl << game.getBoard() << endl;
		out << "correct solution" << endl << Board(solution) << endl << endl;
		return false;
	}
	return true;
}

tuple<int, int> testSolver(int testNum)
{
	int total = 0, failure = 0;
	string puzzleStr, solutionStr;
	for (tuple<string, string> testCase : getTestCases(testNum))
	{
		++total;
		tie(puzzleStr, solutionStr) = testCase;
		if (!runTest(puzzleStr, solutionStr, total))
		{
			++failure;
		}
	}
	return {total, failure};
}

int main(int argc, char* argv[])
{
	int testsToRun = 2;
	if (argc > 1)
	{
		string arg(argv[1]);
		if (arg == "help")
		{
			cout << "Must pass an integer as argument to specify number of tests to run." << endl;
			cout << "Note: TestParser.cpp file must be provided in Testing directory which implements getTestCases and "
					"can handle any parameter less than or equal to command line argument." << endl;
			return 0;
		}
		try
		{
			testsToRun = std::stoi(arg);
		} catch (const exception& e)
		{
			cout << "Invalid argument; must be \"help\" or an integer.";
		}
	}
	
	ofstream out("results");
	for (int testNum = 1; testNum <= testsToRun; ++testNum)
	{
		int total = 0, failure = 0;
		tie(total, failure) = testSolver(testNum);
		out << "Test " << testNum << " results:" << endl;
		out << "Total games played:" << total << endl;
		out << "Failed: " << failure << endl << endl;
	}
	
	return 0;
}
