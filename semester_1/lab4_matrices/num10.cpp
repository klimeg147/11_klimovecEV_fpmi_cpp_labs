#include <iostream>
#include <ctime>
#include <cstdlib>

using std::cin;
using std::cout;

bool IsLinesMatch(const int* line1, const int* line2, int columns) {
	bool FullSovp = true;
	for (int i = 0; i < columns; i++) {
		if (line1[i] != line2[i]) {
			FullSovp = false;
			break;
		}
	}
	if (FullSovp) return true;

	for (int shift = 1; shift < columns; shift++) {
		bool sovp = true;
		for (int i = 0; i < columns; i++) {
			if (line1[i] != line2[(i + shift) % columns]) {
				sovp = false;
				break;
			}
		}
		if (sovp) return true;
	}

	return false;
}

bool WasPrinted(int** matrice, int currentIndex, int lines, int columns) {
	for (int i = 0; i < currentIndex; i++) {
		if (IsLinesMatch(matrice[i], matrice[currentIndex], columns)) {
			return true;
		}
	}
	return false;
}

int CountOnes(const int* line, int columns) {
	int count = 0;
	for (int i = 0; i < columns; i++) {
		if (line[i] == 1) count++;
	}
	return count;
}

void ManuallyMatrInput(int** matrice, int lines, int columns) {
	try {
		for (int i = 0; i < lines; i++) {
			for (int j = 0; j < columns; j++) {
				cin >> matrice[i][j];
				if ((matrice[i][j] != 0) && (matrice[i][j] != 1)) {
					throw "Wrong input (must be 0 or 1)";
					for (int i = 0; i < lines; ++i) {
						delete[] matrice[i];
					}
					delete[] matrice;
					std::exit(1);
				}
			}
		}
	}
	catch (const char* msg) {
		std::cerr << "Error!!! " << msg << '\n';
		for (int i = 0; i < lines; ++i) {
			delete[] matrice[i];
		}
		delete[] matrice;
		std::exit(1);
	}
}

void RandomlyMatrInput(int** matrice, int lines, int columns) {

	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++) {
			matrice[i][j] = (rand() % 2);
		}
	}
}

void CoutMatr(int** matrice, int lines, int columns) {

	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++) {
			cout << matrice[i][j];
		}
		cout << '\n';
	}
}

void MatchGroups(int** matrice, int lines, int columns) {

	bool iffoundgroups = 0;
	for (int i = 0; i < lines; i++) {
		if (WasPrinted(matrice, i, lines, columns)) {
			continue;
		}
		bool found_Match = 0;
		for (int j = i + 1; j < lines; j++) {
			if (IsLinesMatch(matrice[i], matrice[j], columns)) {
				if (found_Match == 0) {
					cout << "Group: " << (i + 1);
					found_Match = 1;
					iffoundgroups = 1;
				}
				cout << ", " << j + 1;
			}
		}
		if (found_Match) {
			cout << '\n';
		}
	}
	if (iffoundgroups == 0) {
		cout << "there is no groups" << '\n';
	}
}

void FindLineWithMaxOnes(int** matrice, int lines, int columns) {

	int maxnumOnes = 0, linewithmaxOnes = 0;
	for (int i = 0; i < lines; i++) {
		int numOnes = CountOnes(matrice[i], columns);
		if (numOnes > maxnumOnes) {
			maxnumOnes = numOnes;
			linewithmaxOnes = i;
		}
	}
	if (maxnumOnes == 0) {
		cout << "there are no ones in the matrix" << '\n';
	}
	else {
		cout << "Line (first) with max number of ones is: " << (linewithmaxOnes + 1) << '\n';
	}
}

int main() {

	char choose_matrix_input;
	int columns, lines;
	cout << "Enter the number of columns: ";
	try {
		if (!(cin >> columns) || (columns < 0)) {
			throw "(Wrong input, num of columns must be > 0)";
		}
		cout << '\n';
		cout << "Enter number of lines: ";
		if (!(cin >> lines) || (lines < 0)) {
			throw "(Wrong input, num of lines must be > 0)";
		}
	}
	catch (const char* msg) {
		std::cerr << "Error!!! " << msg << '\n';
		std::exit(1);
	}
	cout << '\n';

	int** matrice;
	matrice = new int* [lines];
	for (int i = 0; i < lines; i++) {
		matrice[i] = new int[columns];
	}

	cout << "Select how the array elements will be created: manually entered - x, randomly - y:";
	try {
		cin >> choose_matrix_input;
		if (choose_matrix_input != 'x' && choose_matrix_input != 'y') {
			throw "(Wrong input, entered char must be x or y)";
		}
	}
	catch (const char* msg) {
		std::cerr << "Error!!! " << msg << '\n';
		for (int i = 0; i < lines; ++i) {
			delete[] matrice[i];
		}
		delete[] matrice;
		std::exit(1);
	}
	if (choose_matrix_input == 'x') {
		ManuallyMatrInput(matrice, lines, columns);
	}
	else {
		srand(time(0));
		RandomlyMatrInput(matrice, lines, columns);
	}
	cout << "original matrix:" << '\n';
	CoutMatr(matrice, lines, columns);
	cout << "------------------------------------------------------\n";
	cout << "matching lines by groups: \n";
	MatchGroups(matrice, lines, columns);
	cout << "------------------------------------------------------\n";
	FindLineWithMaxOnes(matrice, lines, columns);

	for (int i = 0; i < lines; ++i) {
		delete[] matrice[i];
	}
	delete[] matrice;
}