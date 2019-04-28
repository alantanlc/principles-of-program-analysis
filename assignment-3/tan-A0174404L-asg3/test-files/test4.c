#include <assert.h>

int main() {
	int x, a;
	a = 10;
	int b = 5;
	if (a > 0)
		x = 3 + b;
	else
		x = 3 - b;
	assert (x >= 0);
	return x;
}
