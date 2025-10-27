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

void Merge(int* arr, int left, int mid, int right, bool (*comp)(int, int)) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* leftArr = new int[n1];
    int* rightArr = new int[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (!comp(leftArr[i], rightArr[j])) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

void MergeSortRecursive(int* arr, int left, int right, bool (*comp)(int, int)) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    MergeSortRecursive(arr, left, mid, comp);
    MergeSortRecursive(arr, mid + 1, right, comp);

    Merge(arr, left, mid, right, comp);
}

void MergeSort(int* arr, int size, bool (*comp)(int, int)) {
    MergeSortRecursive(arr, 0, size - 1, comp);
}

void InsertionSort(int* arr, int cols, bool (*comp)(int, int)) {
    for (int i = 1; i < cols; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && comp(arr[j], key)) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void FindMinMax(int* arr, int size, int& minVal, int& maxVal) {
    minVal = arr[0];
    maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }
}

void CountingSort(int* arr, int size, bool (*comp)(int, int)) {
    if (size == 0) return;

    int minVal, maxVal;
    FindMinMax(arr, size, minVal, maxVal);

    int range = maxVal - minVal + 1;
    int* count = new int[range]();

    for (int i = 0; i < size; i++) {
        count[arr[i] - minVal]++;
    }

    int index = 0;

    if (comp == descending) {
        for (int i = range - 1; i >= 0; i--) {
            while (count[i] > 0) {
                arr[index++] = i + minVal;
                count[i]--;
            }
        }
    }
    else {
        for (int i = 0; i < range; i++) {
            while (count[i] > 0) {
                arr[index++] = i + minVal;
                count[i]--;
            }
        }
    }

    delete[] count;
}

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
            if (!(cin >> matrice[i][j])) {
                cout << "wrong input!!!!";
                for (int i = 0; i < lines; ++i) {
                    delete[] matrice[i];
                }
                delete[] matrice;
                std::exit(1);
            }
        }
    }

    cout << "original matrix:" << '\n';
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrice[i][j] << " ";
        }
        cout << '\n';
    }

    cout << "Choose sort type: Bubble sort - b, Merge sort - m, InsertionSort - i, Counting sort - c" << '\n';
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

    case 'm':
        for (int i = 0; i < lines; ++i) {
            MergeSort(matrice[i], cols, comp);
        }
        break;

    case 'i':
        for (int i = 0; i < lines; ++i) {
            InsertionSort(matrice[i], cols, comp);
        }
        break;

    case 'c':
        for (int i = 0; i < lines; ++i) {
            CountingSort(matrice[i], cols, comp);
        }
        break;

    default:
        cout << "Wrong input" << '\n';
        for (int i = 0; i < lines; ++i) {
            delete[] matrice[i];
        }
        delete[] matrice;
        std::exit(1);
    }

    cout << "sorted matrix:" << '\n';
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

    return 0;
}