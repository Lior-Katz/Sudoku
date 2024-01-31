To run the sudoku solver, a command-line argument must be passed specifying the number of tests to run.
In the Testing directory, 3 default tests are provided. By default, only the first 2 will run, as the third test contains a very large number of tests and as such will cause an unreasonable runtime.

It is possible to provide custom tests. This requires providing an implementation of the getTestCases function in a TestParser.cpp file. This ensures that any format of puzzle representation can be handled.
Note that this function must return a vector of (puzzle, solution) tuples, where both the puzzle and the solution are strings that describe the board row by row, from top to bottom and from left to right. Empty spaces are represented by 0.
Furthermore, the size of the puzzle must be a perfect square, meaning that the length of each string must be a whole 4th power.

An example of a 9x9 sudoku puzzle is as follows:

Puzzle:
050083017000100400304005608000030009090824500006000070009000050007290086103607204 

Solution:
652483917978162435314975628825736149791824563436519872269348751547291386183657294
