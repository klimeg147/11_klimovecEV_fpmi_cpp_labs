#include <iostream>
#include <ctime>
#include <cstdlib>

using std::cin;
using std::cout;

bool islinesMatch(const int* line1, const int* line2, int columns) {
	bool PolnoeSovp = true;
	for (int i = 0; i < columns; i++) {
		if (line1[i] != line2[i]) {
			PolnoeSovp = false;
			break;
		}
	}
	if (PolnoeSovp) return true;

	for (int sdvig = 1; sdvig < columns; sdvig++) {
		bool sovp = true;
		for (int i = 0; i < columns; i++) {
			if (line1[i] != line2[(i + sdvig) % columns]) {
				sovp = false;
				break;
			}
		}
		if (sovp) return true;
	}

	return false;
}

bool wasPrinted(int** matrice, int currentIndex, int lines, int columns) {
	for (int i = 0; i < currentIndex; i++) {
		if (islinesMatch(matrice[i], matrice[currentIndex], columns)) {
			return true;
		}
	}
	return false;
}

int countOnes(const int* line, int columns) {
	int count = 0;
	for (int i = 0; i < columns; i++) {
		if (line[i] == 1) count++;
	}
	return count;
}

int main() {


	char vibor_vvoda;
	int columns, lines;
	cout << "Enter the number of columns: ";
	if (!(cin >> columns) || (columns < 0)) {
		cout << "Wrong input";
		std::exit(1);
	}
	cout << '\n';
	cout << "Enter number of lines: ";
	if (!(cin >> lines) || (lines < 0)) {
		cout << "Wrong input";
		std::exit(1);
	}
	cout << '\n';
	int** matrice;
	matrice = new int* [lines];
	for (int i = 0; i < lines; i++) {
		matrice[i] = new int[columns];
	}
	cout << "Select how the array elements will be created: manually entered - x, randomly - y:";
	cin >> vibor_vvoda;
	if (vibor_vvoda == 'x') {
		for (int i = 0; i < lines; i++) {
			for (int j = 0; j < columns; j++) {
				cin >> matrice[i][j];
				if ((matrice[i][j] != 0) && (matrice[i][j] != 1)) {
					cout << "Wrong input (must be 0 or 1)";
					std::exit(1);
				}
			}
		}
	}
	if (vibor_vvoda == 'y') {
		srand(time(0));
		for (int i = 0; i < lines; i++) {
			for (int j = 0; j < columns; j++) {
				matrice[i][j] = (rand() % 2);
			}
		}
	}
	cout << "original matrix:" << '\n';
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++) {
			cout << matrice[i][j];
		}
		cout << '\n';
	}
	cout << "------------------------------------------------------\n";
	cout << "matching lines by groups: \n";
	bool iffoundgroups = 0;
	for (int i = 0; i < lines; i++) {
		if (wasPrinted(matrice, i, lines, columns)) {
			continue;
		}
		bool found_Match = 0;
		for (int j = i + 1; j < lines; j++) {
			if (islinesMatch(matrice[i], matrice[j], columns)) {
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
	cout << "------------------------------------------------------\n";
	int maxnumOnes = 0, linewithmaxoOnes = 0;
	for (int i = 0; i < lines; i++) {
		int numones = countOnes(matrice[i], columns);
		if (numones > maxnumOnes) {
			maxnumOnes = numones;
			linewithmaxoOnes = i;
		}
	}
	if (maxnumOnes == 0) {
		cout << "there are no ones in the matrix" << '\n';
	}
	else {
		cout << "Line with max number of ones is: " << (linewithmaxoOnes + 1) << '\n';
	}

	for (int i = 0; i < lines; ++i) {
		delete[] matrice[i];
	}
	delete[] matrice;
}
