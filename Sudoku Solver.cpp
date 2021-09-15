#include <bits/stdc++.h>

using namespace std;

// Sudoku Array
vector <vector<int>> arr;

// The row, column, and square sets do not need to 
// keep track of duplicate zeroes (hence they are not multisets)

// Row Sets
vector <unordered_set<int>> rowSets;

// Column Sets
vector <unordered_set<int>> columnSets;

// Square Sets
vector <unordered_set <int>> squareSets;

// Sets I use to store possible values
unordered_set <int> possibleValues;
unordered_set <int> possibleValues2;

// Temporary storage variables I use
int tmp, tmp2;
string tmpString;

// Stores the size of the sudoku as well as its square root
int size, sqrtSize;

int convertStringToInt(string str) {
	if (str == "0" || str == "1" || str == "2" || str == "3" || str == "4" || str == "5" || str == "6" || str == "7" || str == "8" || str == "9") {
		return stoi(str);
	} else if (str == "a" || str == "A") {
		return 10;
	} else if (str == "b" || str == "B") {
		return 11;
	} else if (str == "c" || str == "C") {
		return 12;
	} else if (str == "d" || str == "D") {
		return 13;
	} else if (str == "e" || str == "E") {
		return 14;
	} else if (str == "f" || str == "F") {
		return 15;
	} else if (str == "g" || str == "G") {
		return 16;
	} else {
		return -1;
	}
}

string convertIntToString(int toConvert) {
	switch (toConvert) {
		case 0: {
			return "0";
		}
		case 1: {
			return "1";
		}
		case 2: {
			return "2";
		}
		case 3: {
			return "3";
		}
		case 4: {
			return "4";
		}
		case 5: {
			return "5";
		}
		case 6: {
			return "6";
		}
		case 7: {
			return "7";
		}
		case 8: {
			return "8";
		}
		case 9: {
			return "9";
		}
		case 10: {
			return "A";
		}
		case 11: {
			return "B";
		}
		case 12: {
			return "C";
		}
		case 13: {
			return "D";
		}
		case 14: {
			return "E";
		}
		case 15: {
			return "F";
		}
		case 16: {
			return "G";
		}
		default: {
			return "-1";
		}
	}
}

void printSudokuGrid() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << convertIntToString(arr[i][j]) << " ";
			//cout << arr[i][j] << " ";
			//cout << (i - i % sqrtSize + j / sqrtSize) << " ";
		}
		cout << "\n";
	}
}

// Performs a basic search over the sudoku grid
// This search is enough to solve most sudoku puzzles
// Returns true if the sudoku is solved after running
// Returns false if the sudoku is not solved after running
bool performBasicSearch() {
	int counter = 0;
	bool evaluate = true;
	
	while (evaluate) {
		// If an iteration does not yield a new number, end the while loop
		evaluate = false;
		
		// This section checks every square
		// For each square, it checks what numbers 1-9 can fit without causing conflicts
		// If there is only one such number, it inserts the number into the array and the three sets
		
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (arr[i][j] == 0) {
					possibleValues.clear();
					for (int k = 1; k <= size; k++) {
						if (rowSets[i].count(k) == 0 && columnSets[j].count(k) == 0 && squareSets[i - i % sqrtSize + j / sqrtSize].count(k) == 0) {
							possibleValues.insert(k);
						}
					}
					if (possibleValues.size() == 1) {
						tmp = *possibleValues.begin();
						arr[i][j] = tmp;
						rowSets[i].insert(tmp);
						columnSets[j].insert(tmp);
						squareSets[i - i % sqrtSize + j / sqrtSize].insert(tmp);
						evaluate = true;
					}
				}
			}
		}
		
		// This section checks every row
		for (int i = 0; i < size; i++) {
			for (int j = 1; j <= size; j++) {
				if (rowSets[i].count(j) == 0) {
					possibleValues.clear();
					for (int k = 0; k < size; k++) {
						if (arr[i][k] == 0 && columnSets[k].count(j) == 0 && squareSets[i - i % sqrtSize + k / sqrtSize].count(j) == 0) {
							possibleValues.insert(k);
						}
					}
					if (possibleValues.size() == 1) {
						tmp = *possibleValues.begin();
						arr[i][tmp] = j;
						rowSets[i].insert(j);
						columnSets[tmp].insert(j);
						squareSets[i - i % sqrtSize + tmp / sqrtSize].insert(j);
						evaluate = true;
					}
				}
			}
		}
		
		// This section checks every column
		for (int i = 0; i < size; i++) {
			for (int j = 1; j <= size; j++) {
				if (columnSets[i].count(j) == 0) {
					possibleValues.clear();
					for (int k = 0; k < size; k++) {
						if (arr[k][i] == 0 && rowSets[k].count(j) == 0 && squareSets[k - k % sqrtSize + i / sqrtSize].count(j) == 0) {
							possibleValues.insert(k);
						}
					}
					if (possibleValues.size() == 1) {
						tmp = *possibleValues.begin();
						arr[tmp][i] = j;
						rowSets[tmp].insert(j);
						columnSets[i].insert(j);
						squareSets[tmp - tmp % sqrtSize + i / sqrtSize].insert(j);
						evaluate = true;
					}
				}
			}
		}
		
		// This section checks every square
		// Removed due to it being buggy
		/*for (int i = 0; i < size; i++) {
			for (int j = 1; j <= size; j++) {
				if (squareSets[i].count(j) == 0) {
					possibleValues.clear();
					possibleValues2.clear();
					if (counter == 0) {
						cout << i << " " << (i - i % sqrtSize) << " " << (i - i % sqrtSize + sqrtSize) << " ";
						cout << (i % sqrtSize * sqrtSize) << " " << (i % sqrtSize * sqrtSize + sqrtSize) << endl;
					}
					for (int m = i - i % sqrtSize; m < i - i % sqrtSize + sqrtSize; m++) {
						for (int n = i % sqrtSize * sqrtSize; n < i % sqrtSize * sqrtSize + sqrtSize; n++) {
							if (arr[m][n] == 0 && rowSets[m].count(j) == 0 && columnSets[n].count(j) == 0) {
								possibleValues.insert(m);
								possibleValues2.insert(n);
							}
						}
					}
					if (possibleValues.size() == 1) {
						if (counter == 0) {
							//cout << endl;
							//printSudokuGrid();
						}
						tmp = *possibleValues.begin();
						tmp2 = *possibleValues2.begin();
						arr[tmp][tmp2] = j;
						rowSets[tmp].insert(j);
						columnSets[tmp2].insert(j);
						squareSets[i].insert(j);
						if (counter == 0) {
							//cout << endl;
							//printSudokuGrid();
						}
						evaluate = true;
					}
				}
			}
		}*/
		counter++;
	}
	//cout << counter << endl;
	
	// Checks if the sudoku is not solved and returns false as expected
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (arr[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}

int main() {
	// This is the grid size
	cout << "Please enter the length of the sudoku grid\n";
	cin >> size;
	sqrtSize = (int) sqrt(size);
	
	// Setting the sizes appropriately
	rowSets.resize(size);
	columnSets.resize(size);
	squareSets.resize(size);
	arr.resize(size);
	for (int i = 0; i < size; i++) {
		arr[i].resize(size);
	}
	
	cout << "Please enter the sudoku grid, making sure to use '0' wherever there is an unknown\n";
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			// Get next sudoku grid value from user
			cin >> tmpString;
			//cout << convertIntToChar(tmpChar);
			arr[i][j] = convertStringToInt(tmpString);
			//cin >> arr[i][j];
			// Insert value into appropriate row and column sets
			rowSets[i].insert(arr[i][j]);
			columnSets[j].insert(arr[i][j]);
			// Insert value into appropriate square set
			// Square order (for a standard 9x9 sudoku) is as follows:
			// 0 0 0 1 1 1 2 2 2
			// 0 0 0 1 1 1 2 2 2
			// 0 0 0 1 1 1 2 2 2
			// 3 3 3 4 4 4 5 5 5
			// 3 3 3 4 4 4 5 5 5
			// 3 3 3 4 4 4 5 5 5
			// 6 6 6 7 7 7 8 8 8
			// 6 6 6 7 7 7 8 8 8
			// 6 6 6 7 7 7 8 8 8
			squareSets[i - i % sqrtSize + j / sqrtSize].insert(arr[i][j]);
		}
		//cout << "\n";
	}
	
	if (performBasicSearch()) {
		cout << "\nSOLVED\n";
		printSudokuGrid();
	} else {
		cout << "\nFAILED\n";
		printSudokuGrid();
	}
	
	return 0;
}
