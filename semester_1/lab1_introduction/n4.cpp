#include <iostream>

int main() {
	using std::cout;
	using std::cin;
	long k;
	long long dv_fact = 1;
	cout << "Enter number k: ";
	cin >> k;
	while (k > 1) {
		dv_fact = dv_fact * k;
		k = k - 2;
	}
	cout << "The double factorial of a given number is: " << dv_fact << "\n";
}