#include <iostream>

int main() {

    using std::cout;
    using std::cin;
    const int MAX_ARR = 1000;
    int n;
    cout << "Enter the number n of array elements: ";
    cin >> n;
    if (n > MAX_ARR) {
        cout << "Wrong input";
        std::exit(1);
    }
    cout << "\n";
    double arr[MAX_ARR];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    return 0;
}