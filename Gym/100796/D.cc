/* Author: Ankit Sultana
 * * * * * * * * * * * * * * * */
#include <iostream>
#include <queue>
#include <vector>
#define F first
#define S second
#define LL long long
#define pii pair<int, int>
#define point pair<pii, int>
#define MAXN 503

using namespace std;
string grid[MAXN];
bool vis[MAXN][MAXN];
int no_rows, no_cols, a, b;
int del_r[] = {0, 0, 1, -1};
int del_c[] = {-1, 1, 0, 0};

inline bool valid(int i, int j) {
	return i >= 0 && i < no_rows && j >= 0 && j < no_cols && grid[i][j] != '#';
}
int main() {
	std::ios_base::sync_with_stdio(false);
	cin >> no_cols >> no_rows;
	cin >> a >> b;
	for(int i = 0; i < no_rows; i++) {
		cin >> grid[i];
	}
	queue<pii> q;
	int dist[MAXN][MAXN] = {0};
	q.push({0, 0});
	dist[0][0] = 0;
	while(!q.empty()) {
		auto f = q.front();
		q.pop();
		if(vis[f.F][f.S])	continue;
		vis[f.F][f.S] = true;
		if(f.F == no_rows - 1 && f.S == no_cols - 1)	break;
		for(int i = 0; i < 4; i++) {
			int alt_r = del_r[i] + f.F, alt_c = del_c[i] + f.S;
			if(valid(alt_r, alt_c) && !vis[alt_r][alt_c]) {
				dist[alt_r][alt_c] = dist[f.F][f.S] + 1;
				q.push({alt_r, alt_c});
			}
		}
	}
	if(!vis[no_rows-1][no_cols-1]) {
		cout << "IMPOSSIBLE\n";
	} else {
		int one = dist[no_rows-1][no_cols-1]/2, two = dist[no_rows-1][no_cols-1] - one;
		cout << one * a + two * b << '\n';
	}
	return 0;
}
