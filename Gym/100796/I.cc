/* Author: Ankit Sultana
 * * * * * * * * * * * * * * * */
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	double r, R, H, l;
	cin >> r >> R >> H;
	l = H*H + (R-r)*(R-r);
	l = sqrt(l);
	double x = R * (l + r - R);
	x = x/H;
	x = min(H/2, x);
	cout << setprecision(11) << fixed << x << "\n";
	return 0;
}
