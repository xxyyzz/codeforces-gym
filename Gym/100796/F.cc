/* Author: Ankit Sultana
 * * * * * * * * * * * * * * * */
#include <iostream>
#include <iomanip>
#define LL long long

using namespace std;

int main() {
	std::ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	while(t--) {
		LL l, r;
		cin >> l >> r;
		double res = (1.0l/l) - (1.0l/(r+1));
		cout << setprecision(10) << fixed << res << '\n';
	}
	return 0;
}
