#include <iostream>
using namespace std;

int main() {
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