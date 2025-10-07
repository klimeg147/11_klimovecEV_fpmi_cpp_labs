#include <iostream>
#include <random>
using std::cin;
using std::cout;

void arrcout(int* arr, int n) {

    for (int i = 0; i < n; i++) {
        cout << arr[i] << "\n";
    }
}

void productevennum(int* arr, int n) {

    long long proisv = 1;
    int ost;
    for (int i = 1; i < n; i += 2) {
        proisv *= arr[i];
    }
    cout << "the product of array elements with even numberss is: " << proisv << "\n";
    return;
}

void sumnumfirstlastplus(int* arr, int n) {

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

void sortarr(int* arr, int n) {

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

    int n, a, b, random_number;
    char vibor_vvoda;
    cout << "Enter the natural number n: ";
    if (!(cin >> n) || (n < 0)) {
        cout << "Wrong input";
        std::exit(1);
    }
    cout << "\n";
    int* arr = new int[n];
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
    else {
        cout << "wrong input" << "\n";
        std::exit(1);
    }
    cout << "---------------------------------------------------" << "\n";
    cout << "Source array:" << "\n";
    arrcout(arr, n);
    cout << "---------------------------------------------------" << "\n";
    productevennum(arr, n);
    cout << "---------------------------------------------------" << "\n";
    sumnumfirstlastplus(arr, n);
    cout << "----------------------------------------------------" << "\n";
    sortarr(arr, n);
    cout << "Result array:" << "\n";
    arrcout(arr, n);
    delete[] arr;
    return 0;
}