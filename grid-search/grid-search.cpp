// CS3560 Lab #1 - Kenny Taylor 9/11/18
//
// This is part #2 of the lab, which includes the grid search function
// The user is prompted for a start and end value for the search.
// The search will proceed in 0.1 steps 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
using namespace std;

/*
*	Function that reads data from a CSV into a 2-D array.
*/
template <size_t rows, size_t cols>
void readCSV(double(&array)[rows][cols], char* filename) {
	std::ifstream file(filename);

	for (size_t row = 0; row < rows; ++row)
	{
		std::string line;
		std::getline(file, line);

		if (!file.good())
			break;

		std::stringstream iss(line);

		for (size_t col = 0; col < cols; ++col)
		{
			std::string val;
			std::getline(iss, val, ',');

			std::stringstream convertor(val);
			convertor >> array[row][col];
		}
	}

    cout << "Read " << rows << " lines from file." << endl << endl;
}

/*
*	Function that displays data values
*/
template <size_t rows, size_t cols>
void displayValues(double(&array)[rows][cols]) {
    cout << "Array contains:" << endl;
    for (size_t row = 0; row < rows; ++row)
	{
		for (size_t col = 0; col < cols; col++) {
			std::cout << "  " << array[row][col];
		}

		std::cout << std::endl;
	}
}

// Function that evaluates ruleset and writes predicted labels back to column 3 of the 2-D array
template <size_t rows, size_t cols>
void executeRuleset(double(&array)[rows][cols], double threshold) {
    // Run the rule against each data row:  if petal length > threshold,
    // then assign label 2, else assign label 1
    for (size_t i = 0; i < rows; i++) {
        if (array[i][0] > threshold)
            array[i][2] = 2;
        else
            array[i][2] = 1;
    }
}

// Function that counts the percentage of correct predicted labels
template <size_t rows, size_t cols>
double percentCorrect(double(&array)[rows][cols]) {
    double correct = 0;
    for (size_t i = 0; i < rows; i++) {
        if (array[i][1] == array[i][2])
            correct++;
    }

	return correct * 100 / rows;
}

int main()
{
    // Set the rule threshold here
    // const float threshold = 1.45;
    
    double start, end, threshold;

    // Create a 2-D array (100 rows x 3 columns)
    //   Column 1:  Petal length
    //   Column 2:  Ground state
    //   Column 3:  Predicted label
    double data[100][3];

    // Prompt the user for the search range
    cout << "This program will perform a search of threshold values for the expert system code against iris.csv (steps of 0.1)" << endl << endl;
    cout << "Enter the start value:  ";
    cin >> start;
    cout << "Enter the end value:  ";
    cin >> end;
    cout << endl;

    // Read the file
    readCSV(data, "iris.csv");

    for (threshold = start; threshold <= end; threshold += 0.1) {
        // Execute the ruleset
        executeRuleset(data, threshold);

        // Print the correct percentage
        cout << "Using threshold of " << threshold << ", the expert system rules predicted " << percentCorrect(data) << "% successfully" << endl;
    }
   
    return 0;
}
