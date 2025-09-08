#include <iostream>
#include <cmath>
#define PI 3.14159265358979
using namespace std;

int main() {
	int x1, y1, r1, x2, y2, r2;
	double d, angle, tangent, l1, l2, A, L;
	cin >> x1 >> y1 >> r1;
	cin >> x2 >> y2 >> r2;
	d = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
	angle = acos(abs(r1 - r2) / sqrt(d));
	if (r1 > r2) {
		l1 = (2 * PI - 2 * angle) * r1;
		l2 = 2 * angle * r2;
	}
	else {
		l1 = 2 * angle * r1;
		l2 = (2 * PI - 2 * angle) * r2;
	}
	tangent = sqrt(d - (r1 - r2) * (r1 - r2));
	L = 2*tangent + l1 + l2;
	A = (r1 + r2) * tangent + ((r1 * l1) + (r2 * l2)) / 2;
	cout << floor(A) << " " << floor(L);
}