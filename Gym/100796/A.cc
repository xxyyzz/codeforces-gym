/* Author: Ankit Sultana
 * * * * * * * * * * * * * * * */
#include <iostream>
#define LL long long

using namespace std;

int main() {
	std::ios_base::sync_with_stdio(false);
	LL a, b, res = 0, ten = 1;
	cin >> a >> b;
	while(a && b) {
		res += ten * abs((a % 10) - (b % 10));
		ten = ten * 10;
		a /= 10, b /= 10;
	}
	cout << res << '\n';
	return 0;
}
