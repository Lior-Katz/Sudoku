//
// Created by Lior on 31/01/2024.
//

#include "TestParser.h"
#include <string>
#include <vector>
#include <tuple>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <windows.h>

using namespace std;

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

vector<tuple<string, string>> getTestCases1()
{
	string folder = "Test1";
	vector<string> sudokuFilesNames = get_all_files_names_within_folder(folder + "\\sudokus");
	vector<string> solutionFiles = get_all_files_names_within_folder(folder + "\\solutions");
	vector<tuple<string, string>> testCases;
	for (string& sudokuFileName : sudokuFilesNames)
	{
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
		testCases.insert(testCases.end(), {puzzleStr, solutionStr});
	}
	return testCases;
};

vector<tuple<string, string>> getTestCases2()
{
	string folder = "Test2";
	vector<tuple<string, string>> testCases;
	ifstream puzzlesFile(folder + "\\test_puzzles.txt");
	string line;
	while (getline(puzzlesFile, line))
	{
		
		string puzzleStr, solutionStr;
		
		stringstream ss(line);
		getline(ss, puzzleStr, ':');
		getline(ss, solutionStr, ':');
		replace(puzzleStr.begin(), puzzleStr.end(), '.', '0');
		replace(solutionStr.begin(), solutionStr.end(), '.', '0');
		
		testCases.insert(testCases.end(), {puzzleStr, solutionStr});
	}
	return testCases;
}

vector<tuple<string, string>> getTestCases3()
{
	const int MAX_TESTS = 100;
	string folder = "Test3";
	vector<tuple<string, string>> testCases;
	
	ifstream puzzlesFile(folder + "\\tests.csv");
	string line;
	string temp;
	getline(puzzlesFile, temp);
	int total = 0;
	
	while (getline(puzzlesFile, line) && total < MAX_TESTS)
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
		
		testCases.insert(testCases.end(), {puzzleStr, solutionStr});
	}
	return testCases;
}

vector<tuple<string, string>> getTestCases(int testNum)
{
	vector<vector<tuple<string, string>> (*)()> tests = {getTestCases1, getTestCases2, getTestCases3};
	return tests[testNum - 1]();
}