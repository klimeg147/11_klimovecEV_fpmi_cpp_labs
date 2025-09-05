#include <iostream>
using namespace std;

int main() {
	long k;
	long long dv_fact = 1;
	cin >> k;
	while (k > 1) {
		dv_fact = dv_fact * k;
		k = k - 2;
	}
	cout << "The double factorial of a given number is: " << dv_fact << "\n";
}