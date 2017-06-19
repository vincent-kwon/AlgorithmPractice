#include <iostream>

using namespace std;

int main() {
	int i[] = { 1, 2, 4, 5, 6, 7 };
	int x2 = 1;
	for (int k = 2; k <= 7; k++) {
		x2 ^= k;
	}

	int x1 = i[0];
	for (int k = 1; k < 7 - 1; k++) {
		x1 ^= i[k];
	}

	int ret = x2 ^ x1;

	cout << ret << endl;
	return 0;
}
