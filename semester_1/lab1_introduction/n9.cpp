#include <iostream>
using namespace std;

int main() {
	int n1, n2 = 0, mnosh = 1000;
	cin >> n1;
	int n11 = n1;
	int ost1;
	while (n1 > 0) {
		ost1 = n1 % 10;
		n1 = n1 / 10;
		ost1 = ost1 * mnosh;
		n2 = n2 + ost1;
		mnosh = mnosh / 10;
	}
	if (n11 == n2) {
		cout << "This number is palindrom\n";
	}
	else {
		cout << "This number isn't palindrom\n";
	}
}