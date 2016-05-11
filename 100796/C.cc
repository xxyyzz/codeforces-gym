#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define MAXN 100003
#define INF 1<<28

using namespace std;
vector<int> adj[MAXN];
int dp[MAXN], n, val[MAXN];
vector<int> poss;

void haikya(int r, int x, int p = -1, bool minim = true) {
    if(adj[r].size() == 0) {
        if(minim) {
            dp[r] = val[r] <= x ? 0: INF;
        } else {
            dp[r] = val[r] >= x ? 0: INF;
        }
        return ;
    }
    bool cln = adj[r].size() == 1, allzeros = true;
    for(auto &elem: adj[r]) {
        haikya(elem, x, r, minim);
        allzeros &= dp[elem] == 0;
    }
    cln |= allzeros;
    dp[r] = INF;
    for(auto &elem: adj[r]) {
        dp[r] = min(dp[elem] + (!cln), dp[r]);
    }
}

int main() {
    int x, k, l = 0;
    scanf("%d %d", &n, &k);
    for(int i = 2; i <= n; i++) {
        scanf("%d", &x);
        adj[x].push_back(i);
    }
    for(int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
        if(val[i])
            poss.push_back(val[i]), l++;
    }
    sort(poss.begin(), poss.end());
    unique(poss.begin(), poss.end());
    // Get Minimum at root
    int low = 0, upper = poss.size() - 1, mid;
    while(low < upper) {
        mid = (low + upper) >> 1;
        haikya(1, poss[mid]);
        if(dp[1] > k) {
            low = mid+1;
        } else {
            upper = mid;
        }
    }
    printf("%d ", poss[low]);
    k = n - l - k;
    low = 0, upper = poss.size() - 1;
    while(low < upper) {
        mid = (low + upper) >> 1;
        haikya(1, poss[mid], -1, false);
        if(dp[1] > k) {
            upper = mid;
        } else {
            haikya(1, poss[mid+1], -1, false);
            if(dp[1] > k) {
                low = mid;
                break;
            }
            low = mid+1;
        }
    }
    printf("%d", poss[low]);
    return 0;
}
