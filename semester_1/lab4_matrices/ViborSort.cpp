#include <iostream>

using std::cout;
using std::cin;


bool ascending(int a, int b) {
	return a > b;
}

bool descending(int a, int b) {
	return a < b;
}

void BubbleSort(int* arr, int cols, bool (*comp)(int, int)) {
	for (int i = 0; i < cols - 1; i++) {
		for (int j = 0; j < cols - i - 1; j++) {
			if (comp(arr[j], arr[j + 1])) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void CountingSort(int* arr, int maxValue, bool (*comp)(int, int)) {

}

//////////////////////////////////

int main() {

	char choose_sort, choose_comp;
	bool (*comp)(int, int) = nullptr;
	int lines, cols;
	int** matrice;

	cout << "Enter Number of Lines: ";
	cin >> lines;
	cout << '\n';
	cout << "Enter Number of Columns: ";
	cin >> cols;
	cout << '\n';
	matrice = new int* [lines];
	for (int i = 0; i < lines; i++) {
		matrice[i] = new int[cols];
	}

	cout << "Enter matrix elements: " << '\n';
	for (int i = 0; i < lines; ++i) {
		for (int j = 0; j < cols; ++j) {
			cin >> matrice[i][j];
		}
	}

	cout << "original matrix:" << '\n';
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < cols; j++) {
			cout << matrice[i][j] << " ";
		}
		cout << '\n';
	}

	cout << "Choose sort type: Bubble sort - b, " << '\n';
	cin >> choose_sort;
	cout << "Choose comp type: ascending - '>', descending - '<'" << '\n';
	cin >> choose_comp;

	if (choose_comp == '>') {
		comp = ascending;
	}
	else if (choose_comp == '<') {
		comp = descending;
	}
	else {
		cout << "Wrong input" << '\n';
		std::exit(1);
	}

	switch (choose_sort) {
	case 'b':
		for (int i = 0; i < lines; ++i) {
			BubbleSort(matrice[i], cols, comp);
		}
		break;

		////////////////////////////

	default:
		cout << "Wrong input" << '\n';
	}

	cout << "original matrix:" << '\n';
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < cols; j++) {
			cout << matrice[i][j] << " ";
		}
		cout << '\n';
	}

	for (int i = 0; i < lines; ++i) {
		delete[] matrice[i];
	}
	delete[] matrice;
}