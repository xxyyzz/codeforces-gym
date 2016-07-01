#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define MAXN 500003

using namespace std;
int n;
vector<int> adj[MAXN];
int dp[MAXN][2];
int kisse[MAXN];
vector<int> result;

void go(int r = 1) {
    if(adj[r].empty()) {
        dp[r][0] = 0;
        dp[r][1] = 0;
        return ;
    }
    int sum_max = 0;
    for(auto &elem: adj[r]) {
        go(elem);
        sum_max += max(dp[elem][0], dp[elem][1]);
    }
    dp[r][0] = sum_max;
    // compute dp[r][1]
    for(auto &c: adj[r]) {
        int temp = 1000 + dp[c][0] + sum_max - max(dp[c][0], dp[c][1]);
        if(dp[r][1] < temp) {
            dp[r][1] = temp;
            kisse[r] = c;
        }
    }
}

void backtrack(int r, bool give) {
    if(adj[r].empty())  return ;
    if(give) {
        result.push_back(kisse[r]);
        for(auto &c: adj[r]) {
            if(c == kisse[r])
                backtrack(c, false);
            else
                backtrack(c, dp[c][1] > dp[c][0]);
        }
    } else {
        for(auto &c: adj[r]) {
            backtrack(c, dp[c][1] > dp[c][0]);
        }
    }
}

int main() {
    freopen("grant.in", "rb", stdin);
    freopen("grant.out", "wb", stdout);
    int a;
    scanf("%d", &n);
    for(int i = 2; i <= n; i++) {
        scanf("%d", &a);
        adj[a].push_back(i);
    }
    go();
    printf("%d\n", max(dp[1][0], dp[1][1]));
    backtrack(1, dp[1][1] > dp[1][0]);
    sort(result.begin(), result.end());
    for(auto &elem: result) {
        printf("%d ", elem);
    } printf("\n");
    return 0;
}
