#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cassert>
#define MAXN 200001

using namespace std;

struct data {
    int x, y, idx;
    bool operator<(const data &other) const {
        if(x == other.x)    return y < other.y;
        return x < other.x;
    }
}arr[MAXN];
int P[MAXN], dp[MAXN];
int n;

struct node {
    int maxim, idx;
    void merge(node &l, node &r) {
        if(l.maxim >= r.maxim) {
            maxim = l.maxim;
            idx = l.idx;
        } else {
            maxim = r.maxim;
            idx = r.idx;
        }
    }
}tree[4*MAXN];

void update(int idx, int y, int maxim, int root = 1, int l = 1, int r = n) {
    if(r == l) {
        if(tree[root].maxim < maxim) {
            tree[root].maxim = maxim;
            tree[root].idx = idx;
        }
        return ;
    }
    int mid = (l + r) >> 1;
    if(y > mid)
        update(idx, y, maxim, root*2+1, mid+1, r);
    else
        update(idx, y, maxim, root*2, l, mid);
    tree[root].merge(tree[root*2], tree[root*2+1]);
}

pair<int, int> query(int ql, int qr, int root = 1, int l = 1, int r = n) {
    if(ql > qr) return {0, 0};
    if(l >= ql && r <= qr) {
        return {tree[root].maxim, tree[root].idx};
    }
    int mid = (l + r) >> 1;
    pair<int, int> one = {0, 0}, two = {0, 0};
    if(ql <= mid) {
        one = query(ql, qr, root*2, l, mid);
    }
    if(qr > mid)
        two = query(ql, qr, root*2+1, mid+1, r);
    return max(one, two);
}

int main() {
#ifndef __APPLE__
    freopen("people.in", "rb", stdin);
    freopen("people.out", "wb", stdout);
#endif
    scanf("%d", &n);
    map<int, int> cmp_x, cmp_y;
    for(int i = 1; i <= n; i++) {
        scanf("%d %d", &arr[i].x, &arr[i].y);
        arr[i].idx = i;
        cmp_x[arr[i].x] = 0;
        cmp_y[arr[i].y] = 0;
    }
    sort(arr + 1, arr + 1 + n);
    int cnt = 0;
    for(auto &elem: cmp_x) {
        elem.second = ++cnt;
    }
    for(int i = 1; i <= n; i++) arr[i].x = cmp_x[arr[i].x];
    cnt = 0;
    for(auto &elem: cmp_y)
        elem.second = ++cnt;
    for(int i = 1; i <= n; i++) arr[i].y = cmp_y[arr[i].y];
    // compressed
    int iter = 1;
    int res = 0;
    for(int x = 1; x <= n; x++) {
        vector<data> working;
        while(iter <= n && arr[iter].x == x) {
            working.push_back(arr[iter++]);
        }
        for(auto &elem: working) {
            auto f = query(1, elem.y - 1);
            dp[elem.idx] = f.first + 1;
            res = max(dp[elem.idx], res);
            P[elem.idx] = f.second;
        }
        for(auto &elem: working) {
            update(elem.idx, elem.y, dp[elem.idx]);
        }
    }
    printf("%d\n", res);
    assert(res > 0);
    int st = 0;
    for(int i = 1; i <= n; i++) {
        if(dp[i] == res) {
            st = i;
            break;
        }
    }
    vector<int> answer;
    while(st > 0) {
        answer.push_back(st);
        st = P[st];
    }
    for(int i = answer.size()-1; i >= 0; i--) {
        printf("%d ", answer[i]);
    } printf("\n");
    return 0;
}
