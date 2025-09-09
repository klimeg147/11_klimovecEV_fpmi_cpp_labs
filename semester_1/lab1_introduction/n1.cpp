#include <iostream>

int main() {
	using std::cin;
	using std::cout;
	int a, b, d;
	if (!(cin >> a >> b >> d)) {
		cout << "Error (Wrong input)";
		std::exit(1);
	}
	if ((a < b && d < 0) || (a > b && d > 0)) {
		int temp = a;
		a = b;
		b = temp;
	}
	if (d == 0) {
		int k;
		k = a % 3;
		if (k == 0) {
			cout << a << "\n";
		}
		std::exit(1);
	}
	for (int i = a; i <= b; i += d) {
		if (i % 3 == 0) {
			cout << i << "\n";
		}
	}
}