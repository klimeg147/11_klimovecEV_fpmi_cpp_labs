#include <iostream>
#include <random>
using std::cin;
using std::cout;


void FillArrManually(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        if (!(cin >> arr[i])) {
            cout << "Wrong input, need to be entered NUMBER (integer or real)" << "\n";
            delete[] arr;
            std::exit(1);
        }
    }
}

void FillArrRandomly(int* arr, int n) {

    int a, b, random_number;
    cout << "Enter numbers a and b (boundaries of random elements): " << "\n";
    cin >> a >> b;
    if (a > b) {
        int temp = b;
        b = a;
        a = temp;
    }
    std::mt19937 gen(time(0));
    for (int i = 0; i < n; i++) {
        std::uniform_int_distribution<int> dist(a, b);
        random_number = dist(gen);
        arr[i] = random_number;
    }
}

void ArrCout(int* arr, int n) {

    for (int i = 0; i < n; i++) {
        cout << arr[i] << "\n";
    }
}

void ProductEvenNum(int* arr, int n) {

    long long proisv = 1;
    int ost;
    for (int i = 1; i < n; i += 2) {
        proisv *= arr[i];
    }
    cout << "the product of array elements with even numberss is: " << proisv << "\n";
    return;
}

void SumNumFirstLastPlus(int* arr, int n) {

    int sum = 0;
    int fst_plus_ind, lst_plus_ind;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            lst_plus_ind = i;
        }
    }
    for (int i = (n - 1); i >= 0; i--) {
        if (arr[i] > 0) {
            fst_plus_ind = i;
        }
    }
    for (int i = (fst_plus_ind + 1); i < lst_plus_ind; i++) {
        sum += arr[i];
    }
    cout << "The sum of the array elements located between the first and last positive elements is:" << sum << "\n";
}

void SortArr(int* arr, int n) {

    int j, cur;
    for (int i = 1; i < n; i++) {
        if (arr[i] < 0) {
            cur = arr[i];
            j = i - 1;
            while (j >= 0 && arr[j] >= 0) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = cur;
        }
    }
}

int main() {

    int n;
    char vibor_vvoda;
    cout << "Enter the natural number n: ";
    if (!(cin >> n) || (n < 0)) {
        cout << "Wrong input, need to enter integer number, >= 0";
        std::exit(1);
    }
    cout << "\n";
    int* arr = new int[n];
    cout << "Select how the array elements will be created: manually entered - x, randomly - y:";
    cin >> vibor_vvoda;
    if (vibor_vvoda == 'x') {
        FillArrManually(arr, n);
    }
    else if (vibor_vvoda == 'y') {
        FillArrRandomly(arr, n);
    }
    else {
        cout << "wrong input, need to be entered symbol x or y" << "\n";
        delete[] arr;
        std::exit(1);
    }
    cout << "---------------------------------------------------" << "\n";
    cout << "Source array:" << "\n";
    ArrCout(arr, n);
    cout << "---------------------------------------------------" << "\n";
    ProductEvenNum(arr, n);
    cout << "---------------------------------------------------" << "\n";
    SumNumFirstLastPlus(arr, n);
    cout << "----------------------------------------------------" << "\n";
    SortArr(arr, n);
    cout << "Result array:" << "\n";
    ArrCout(arr, n);
    delete[] arr;
    return 0;
}