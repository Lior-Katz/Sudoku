#include <iostream>
#include "Game.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <windows.h>

using namespace std;

vector<vector<Cell>> createBoard(const string& desc);

void testSolver(vector<tuple<int, int> (*)(const string& fileName)> tests);

vector<string> get_all_files_names_within_folder(const string& folder);

tuple<int, int> test1(const string& folder);

tuple<int, int> test2(const string& folder);

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
			out << "correct solution" << endl << "This puzzle has no solution. expexted solved puzzle to be identical"
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

tuple<int, int> test1(const string& folder)
{
	vector<string> sudokuFilesNames = get_all_files_names_within_folder(folder + "\\sudokus");
	vector<string> solutionFiles = get_all_files_names_within_folder(folder + "\\solutions");
	
	int total = 0, failure = 0;
	
	for (string& sudokuFileName : sudokuFilesNames)
	{
		++total;
		ifstream puzzleFile(folder + "\\sudokus" + "\\" + sudokuFileName);
		string solutionFileName = sudokuFileName;
		solutionFileName.insert(sudokuFileName.size() - 4, "_s");
		ifstream solutionFile(folder + "\\solutions" + "\\" + solutionFileName);
		
		string line, puzzleStr, solutionStr;
		while (getline(puzzleFile, line))
		{
			line.erase(remove_if(line.begin(), line.end(), [](char c) {
				return (c == '\r' || c == '\t' || c == ' ' || c == '\n');
			}), line.end());
			puzzleStr += line;
		}
		while (getline(solutionFile, line))
		{
			if (line == "")
			{
				break;
			}
			line.erase(remove_if(line.begin(), line.end(), [](char c) {
				return (c == '\r' || c == '\t' || c == ' ' || c == '\n' || c == '|' || c == '-');
			}), line.end());
			line = line.substr(0, line.find('='));
			solutionStr += line;
		}
		if (!runTest(puzzleStr, solutionStr, total))
		{
			++failure;
		}
	}
	return {total, failure};
}

tuple<int, int> test2(const string& folder)
{
	int failure = 0;
	int total = 0;
	ifstream puzzlesFile(folder + "\\test_puzzles.txt");
	string line;
	
	while (getline(puzzlesFile, line))
	{
		++total;
		
		string puzzleStr, solutionStr;
		
		stringstream ss(line);
		getline(ss, puzzleStr, ':');
		getline(ss, solutionStr, ':');
		replace(puzzleStr.begin(), puzzleStr.end(), '.', '0');
		replace(solutionStr.begin(), solutionStr.end(), '.', '0');
		
		if (!runTest(puzzleStr, solutionStr, total))
		{
			++failure;
		}
		
	}
	return {total, failure};
}

tuple<int, int> test3(const string& folder)
{
	int failure = 0;
	int total = 0;
	ifstream puzzlesFile(folder + "\\tests.csv");
	string line;
	string temp;
	getline(puzzlesFile, temp);
	while (getline(puzzlesFile, line) && total < 1500000)
	{
		++total;
		
		string puzzleStr, solutionStr;
		
		stringstream ss(line);
		getline(ss, temp, ',');
		total = stoi(temp);
		getline(ss, puzzleStr, ',');
		getline(ss, solutionStr, ',');
		replace(puzzleStr.begin(), puzzleStr.end(), '.', '0');
		replace(solutionStr.begin(), solutionStr.end(), '.', '0');
		
		if (!runTest(puzzleStr, solutionStr, total))
		{
			++failure;
		}
		if (total % 16384 == 0)
		{
			cout << "test " << total << endl << "failures: " << failure << endl;
		}
		
	}
	return {total, failure};
}

void testSolver(vector<tuple<int, int> (*)(const string& fileName)> tests)
{
	ofstream out("results");
	int testNum = 1;
	for (auto func : tests)
	{
		int total = 0, failure = 0;
		tie(total, failure) = func("Test" + to_string(testNum));
		out << "Test " << testNum << " results:" << endl;
		out << "Total games played:" << total << endl;
		out << "Failed: " << failure << endl << endl;
		++testNum;
	}
	
}

vector<string> get_all_files_names_within_folder(const string& folder)
{
	vector<string> names;
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

int main()
{
	vector<tuple<int, int> (*)(const string& fileName)> tests = {test1, test2, test3};
	testSolver(tests);
	return 0;
}

/*
.5..83.17...1..4..3.4..56.8....3...9.9.8245....6....7...9....5...729..861.36.72.4:652483917978162435314975628825736149791824563436519872269348751547291386183657294
2.6.3......1.65.7..471.8.5.5......29..8.194.6...42...1....428..6.93....5.7.....13:256734198891265374347198652514683729728519436963427581135942867689371245472856913
..45.21781...9..3....8....46..45.....7.9...128.12.35..4.......935..6.8.7.9.3..62.:964532178187694235235817964629451783573986412841273596416728359352169847798345621
59....147...9....8.72....3.7...4.29..2..3.8.68..17..5...5764..9.36..5...1..8....2:598326147314957628672481935753648291421539876869172453285764319936215784147893562
9...84.6.6.4..52.7.3..7..8.76...15...53.....1...4.96.31.5.26.9...2.4....8....371.:927384165684915237531672489769231548453768921218459673175826394392147856846593712
68.9.5.....3...5.84.21.87.339.72.8.........1..45..69...6.8.4..2..1..2.757...13...:687935241913247568452168793396721854278459316145386927569874132831692475724513689
...34...2..6.82.737..1..45..82..5.14....983..67......514.7.....9.5.3..2..3....8.6:851347692496582173723169458382675914514298367679413285148726539965834721237951846
6...5.....73..8.2.854.27...2.17..53.4...69..7.8....9...273.1.84.6.54...93.......1:612453798973618425854927163291784536435269817786135942527391684168542379349876251
..75..9.4....823.5..16....28...36.7..16..42..43.19..5.54...8....29.71.3.......6.9:287513964964782315351649782895236471716854293432197856543968127629471538178325649
........8..3...4...9..2..6.....79.......612...6.5.2.7...8...5...1.....2.4.5.....3:621943758783615492594728361142879635357461289869532174238197546916354827475286913
........2..8.1.9..5....3.4....1.93...6..3..8...37......4......53.1.7.8..2........:639847512478512963512693748724189356965234187183765294847921635351476829296358471
..2...7...1.....6.5......18....37.......49.....41.23....3.2.9...8.....5.6.......2:832416795417985263596273418951837624328649571764152389173528946289364157645791832
........7..4.2.6..8.....31......29...4..9..3...95.6....1......8..6.5.2..7......6.:963814527154327689827965314371482956645791832289536741512673498496158273738249165
..4..3....7..8....2.81....6..3....9..8..2....1..7....3......45....8..9....9..5..8:594263871671584329238197546763418295985326714142759683816932457357841962429675138
..6..1....5..3....9..4....7..1....2..3..9....4..5....13.....68....3..2....2..8..3:826971354754836192913425867571643928238197546469582731347219685185364279692758413
........3..1..9.6..5..8.4.....9...8...867.....1....2....6..7.2..3.8..5..4.......8:862714953741359862953286471374921685298675134615438297586147329137892546429563718
........5..6..87..3......9....1.7.4...7...8...4...6....9..8...3..16..4..5...2....:714963285926518734385274691238197546657342819149856327492785163871639452563421978
.....5..3..9....4..81.4.......7.......4..2..68...14.3.......2...4...6..79...5..1.:427165893539278641681349725216793458394582176875614932758431269143926587962857314
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
