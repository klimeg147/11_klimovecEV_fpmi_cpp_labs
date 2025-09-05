#include <iostream>
using namespace std;

int main() {
	int num1, num2, d1, d2;
	cin >> num1 >> num2;
	int k = min(num1, num2);
	int n = max(num1, num2);
	for (int delit = 1; delit <= k; ++delit) {
		d1 = k % delit;
		d2 = n % delit;
		if (d1 == 0 && d2 == 0) {
			cout << delit << "\n";
		}
	}
}