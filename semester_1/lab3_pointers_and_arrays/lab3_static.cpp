#include <iostream>
#include <random>
#include <algorithm>
#include <cmath>
using std::cout;
using std::cin;

void arrcout(double arr[], int n) {

    for (int i = 0; i < n; i++) {
        cout << arr[i] << "\n";
    }
    return;
}

void sumafterminabs(double arr[], int n) {

    double min_modul = std::abs(arr[0]);
    int last_min_modul_index = 0;
    double sum = 0;
    for (int i = 1; i < n; i++) {
        double cur_modul = std::abs(arr[i]);
        if (cur_modul <= min_modul) {
            min_modul = cur_modul;
            last_min_modul_index = i;
        }
    }
    if (last_min_modul_index < (n - 1)) {
        for (int i = last_min_modul_index + 1; i < n; i++) {
            sum += arr[i];
        }
        cout << "The sum of all elements of the array after the minimum one by absolute value is equal to: " << sum << "\n";
    }
    else {
        cout << "the last element of the array is the minimum in modulus" << "\n";
    }
    return;
}

void swapmaxmin(double arr[], int n) {

    int index_max = 0, index_min = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[index_max]) {
            index_max = i;
        }
        if (arr[i] < arr[index_min]) {
            index_min = i;
        }
    }
    std::swap(arr[index_max], arr[index_min]);
    return;
}

void sortarr(double arr[], int n) {

    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {
            arr[i] = arr[i] * arr[i];
        }
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


int main() {

    const int MAX_ARR = 1000;
    int n;
    char vibor_vvoda;
    double a, b,/*a and b are the boundaries of random elements*/ random_number;
    cout << "Enter the number n of array elements: ";
    if (!(cin >> n) || (n > MAX_ARR) || (n < 0)) {
        cout << "Wrong input" << "\n";
        std::exit(1);
    }
    cout << "\n";
    double arr[MAX_ARR];
    cout << "Select how the array elements will be created: manually entered - x, randomly - y:";
    cin >> vibor_vvoda;
    if (vibor_vvoda == 'x') {
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
    }
    else if (vibor_vvoda == 'y') {
        cout << "Enter numbers a and b (boundaries of random elements): " << "\n";
        cin >> a >> b;
        if (a > b) {
            double temp = b;
            b = a;
            a = temp;
        }
        std::mt19937 gen(time(0));
        for (int i = 0; i < n; i++) {
            std::uniform_real_distribution<double> dist(a, b);
            random_number = dist(gen);
            arr[i] = random_number;
        }
    }
    else {
        cout << "wrong input" << "\n";
        std::exit(1);
    }
    cout << "-------------------------------------------------------" << "\n";
    cout << "Initial array: " << "\n";
    arrcout(arr, n);
    cout << "-------------------------------------------------------" << "\n";
    sumafterminabs(arr, n);
    cout << "-------------------------------------------------------" << "\n";
    swapmaxmin(arr, n);
    cout << "array from task 1: " << "\n";
    arrcout(arr, n);
    cout << "-------------------------------------------------------" << "\n";
    sortarr(arr, n);
    cout << "Sorted array:" << "\n";
    arrcout(arr, n);
    return 0;
}