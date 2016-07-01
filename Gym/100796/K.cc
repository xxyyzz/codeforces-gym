/* Author: Ankit Sultana
 * * * * * * * * * * * * * * * */
#include <iostream>
#include <queue>
#include <map>
#define LL long long

using namespace std;
map<LL, bool> isit;
LL fact[21];

void factorial() {
	fact[0] = 1;
	for(int i = 1; i < 21; i++)	fact[i] = fact[i-1]*i;
}

void go() {
	queue<LL> q;
	q.push(1);
	while(not q.empty()) {
		LL f = q.front();
		q.pop();
		if(isit[f])	continue;
		isit[f] = true;
		for(int i = 0; i < 21; i++) {
			if(double(f) * double(fact[i]) > 1e18)	break;
			if(isit[f*fact[i]])	continue;
			q.push(f*fact[i]);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	factorial();
	go();
	int t;
	cin >> t;
	while(t--) {
		LL n;
		cin >> n;
		if(isit[n])
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}
