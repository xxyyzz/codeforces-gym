/* Author: Ankit Sultana
 * * * * * * * * * * * * * * * */
#include <iostream>
#define LL long long

using namespace std;

int main() {
	std::ios_base::sync_with_stdio(false);
	LL n, m, h, v;
	cin >> n >> m;
	v = n * (m+1);
	h = m * (n+1);
	cout << min(h, v) << '\n';
	return 0;
}
