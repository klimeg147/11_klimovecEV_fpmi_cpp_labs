
#include <iostream>
#include <random>

int main() {

    using std::cin;
    using std::cout;
    int n, a, b, random_number, sum = 0;
    char vibor_vvoda;
    long long proisv = 1;
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
    cout << "Source array:" << "\n";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << "\n";
    }
    cout << "---------------------------------------------------" << "\n";
    int ost;
    for (int i = 1; i < n; i += 2) {
        proisv *= arr[i];
    }
    cout << "the product of array elements with even numberss is: " << proisv << "\n";
    cout << "---------------------------------------------------" << "\n";
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
    cout << "----------------------------------------------------" << "\n";
    int* arr2 = new int[n]; // arr2 - future result array
    int ind = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {
            arr2[ind++] = arr[i];
        }
    }
    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0) {
            arr2[ind++] = arr[i];
        }
    }
    cout << "Result array:" << "\n";
    for (int i = 0; i < n; i++) {
        cout << arr2[i] << "\n";
    }
    delete[] arr;
    return 0;
}