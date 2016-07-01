#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
using namespace std;

const int MAXN = 204;
int demand[MAXN], edge_nos[MAXN][MAXN], answers[MAXN*MAXN], minim[MAXN*MAXN];

template<typename T>
struct Dinic {
    Dinic() { }
    Dinic(int num_nodes, int sc, int t) : n(num_nodes), source(sc), sink(t) { }
    void add_edge(int a, int b, T cap) {
        edge e1 = { a, b, cap, 0};
        edge e2 = { b, a, 0,   0};
        g[a].push_back(e.size());
        e.push_back(e1);
        g[b].push_back(e.size());
        e.push_back(e2);
    }
    bool bfs() {
        int qh = 0, qt = 0;
        std::fill(d, d + MAXN, -1);
        q[qt++] = source, d[source] = 0;;
        while(qh < qt) {
            int f = q[qh++];
            for(int i = 0; i < g[f].size(); i++) {
                int id = g[f][i], to = e[id].b;
                if(d[to] == -1 and e[id].flow < e[id].cap) {
                    q[qt++] = to;
                    d[to] = d[f] + 1;
                }
            }
        }
        return d[sink] != -1;
    }
    int dfs(int v, int flow) {
        if(v == sink || !flow) return flow;
        for(; ptr[v] < g[v].size(); ptr[v]++) {
            int id = g[v][ptr[v]], to = e[id].b;
            if(d[to] != d[v] + 1 || e[id].flow == e[id].cap) continue;
            int pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
            if(pushed) { // push flow
                e[id].flow += pushed;
                e[id^1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
    int dinic() {
        int flow = 0;
        while(bfs()) {
            std::fill(ptr, ptr + MAXN, 0);
            while(int temp = dfs(source, INF))
                flow += temp;
        }
        return flow;
    }
    void solve(int num_edges) {
        cout << "YES\n";
        for(int id = 0; id < e.size(); id++) {
            if(id % 2 == 0 and e[id].a != source and e[id].b != sink) {
                answers[edge_nos[e[id].a][e[id].b]] = e[id].flow;
            }
        }
        for(int i = 0; i < num_edges; i++) cout << answers[i] + minim[i] << '\n';
    }
private:
    struct edge {
        int a, b;
        T cap, flow;
    };
    static const int MAXN = 300, INF = 1e9;
    vector<int> g[MAXN];
    vector<edge> e;
    int n, source, sink, d[MAXN], ptr[MAXN], q[MAXN];
};

int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef __APPLE__
    freopen("cooling.in", "rb", stdin);
    freopen("cooling.out", "wb", stdout);
#endif
    int n, m, a, b, l, u;
    cin >> n >> m;
    int sc = 0, sink = n + 1;
    Dinic<int> tester(n + 2, sc, sink);
    for(int i = 0; i < m; i++) {
        cin >> a >> b >> l >> u;
        edge_nos[a][b] = i;
        minim[i] = l;
        demand[a] += l, demand[b] -= l;
        tester.add_edge(a, b, u - l);
    }
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        if(demand[i] > 0) {
            tester.add_edge(i, sink, demand[i]);
            sum += demand[i];
        } else if(demand[i] < 0) {
            tester.add_edge(sc, i, -demand[i]);
        }
    }
    int f = tester.dinic();
    assert(f <= sum);
    if(f < sum) return cout << "NO\n", 0;
    tester.solve(m);
    return 0;
}
