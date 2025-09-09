#include <iostream>

int main() {
	using std::cout;
	using std::cin;
	int ost;
	long n;
	long long sum = 0;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		ost = i % 2;
		if (ost == 1) {
			sum = sum + i;
		}
	}
	cout << "Sum = " << sum << "\n";
}