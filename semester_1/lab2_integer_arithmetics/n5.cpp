#include <iostream>

int main() {
	using std::cin;
	using std::cout;
	int n, pal1 = 0, ost, i2; // ost - остаток от деления, pal1,2 - перевёрнутый i для проверки на палиндром
	long i3, i4, pal2 = 0; // i2, i3, i4 - запапасные i (i3, i4 - квадраты)
	cout << "Enter int n belonging to N: ";
	if (!(cin >> n)) {
		cout << "Error (Wrong input)";
		std::exit(1);
	}
	for (int i = 0; i <= n; ++i) {
		i2 = i;
		i3 = i * i;
		i4 = i3;
		while (i2) {
			ost = i2 % 10;
			i2 /= 10;
			pal1 *= 10;
			pal1 += ost;
		}
		if (pal1 == i) {
			while (i3) {
				ost = i3 % 10;
				i3 /= 10;
				pal2 *= 10;
				pal2 += ost;
			}
		}
		if (pal2 == i4) {
			cout << i << "\n";
		}
		pal1 = 0;
		pal2 = 0;
	}
}