//
// Created by Lior on 31/01/2024.
//

#ifndef SUDOKU_TESTPARSER_H
#define SUDOKU_TESTPARSER_H

#include <string>
#include <vector>

/**
 * @brief Retrieves test cases for a given test number.
 *
 * This function is designed to be called in a loop from the main function,
 * where the loop iterates over the number of tests to run. For each iteration,
 * the function is called with the current test number.
 *
 * @param testNum The current test number for which test cases need to be retrieved.
 * @return A vector of (test case, solution) pairs, represented as std::tuple\<std::string, std::string\>, for the
 * specified test number.
 * @note Ensure that every input testNum between 1 and argv[1] is properly handled.
 *
 * Example Usage:
 * @code
 * int main(int argc, char* argv[]) {
 *     // Assuming the number of tests to run is passed as a command-line argument.
 *     int numTests = std::stoi(argv[1]);
 *
 *     for (int i = 1; i <= numTests; ++i) {
 *         std::vector<std::tuple<std::string, std::string>> testCases = getTestCases(i);
 *         // Perform testing using the generated test cases.
 *     }
 *
 *     return 0;
 * }
 * @endcode
 */
std::vector<std::tuple<std::string, std::string>> getTestCases(int testNum);

#endif //SUDOKU_TESTPARSER_H
