#include <iostream>

int main() {
	using std::cout;
	using std::cin;
	int ost;
	long n;
	long long sum = 0, pr = 1;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		ost = i % 2;
		if (ost == 0) {
			sum = sum + i;
		}
		else {
			pr = pr * i;
		}
	}
	cout << "Sum = " << sum << "\n";
	cout << "Product = " << pr << "\n";
}