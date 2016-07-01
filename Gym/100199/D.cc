#include <iostream>
#define LL long long
#define MAXN 100003

using namespace std;
LL degree[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    freopen("matrix.in", "rb", stdin);
    freopen("matrix.out", "wb", stdout);
    int n, m, a, b;
    cin >> n >> m;
    LL sum = 0;
    for(int i = 0; i < m; i++) {
        cin >> a >> b;
        degree[a]++, degree[b]++;
    }
    for(int i = 1; i <= n; i++)
        sum += degree[i]*degree[i];
    cout << sum << '\n';
    return 0;
}
