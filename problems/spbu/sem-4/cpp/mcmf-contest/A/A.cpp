#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>

using namespace std;
using ll = long long;
using ull = unsigned long long;

typedef struct edge
{
    int to;
    int w;
    int cap;
    int flow;

    int rem_flow() { return cap - flow; };
    ll cost(ll add_flow) { return add_flow * w; };
} edge;

vector<vector<int>> g; 
vector<edge> edges;
vector<ll> d;
vector<pair<int, int>> prevs;

void add_edge(int from, int to, int w, int cap) {
    g[from].push_back(edges.size());
    edges.push_back({to, w, cap, 0});
    g[to].push_back(edges.size());
    edges.push_back({from, -w, 0, 0});
}

queue<int> q;
vector<bool> in_queue;

void spfa(int s, int n) {
    d.assign(n, LLONG_MAX);
    prevs.assign(n, {-1, -1});
    d[s] = 0;

    in_queue.assign(n, 0);
    q.push(s);

    int from, to;
    while(!q.empty()) {
        from = q.front(); q.pop();
        in_queue[from] = 0;
        for (const int i : g[from]) {
            edge& e = edges[i];
            to = e.to;
            if (e.rem_flow() > 0 && d[from] != LLONG_MAX && d[from] + e.w < d[to]) {
                d[to] = d[from] + e.w;
                prevs[to] = {from, i};

                if (in_queue[to]) continue;
                in_queue[to] = 1;
                q.push(to);
            }
        }
    }
}

pair<ll, ll> increase_path(int t) {
    int v = t;
    ll push = LLONG_MAX;
    while (prevs[v].first != -1) {
        auto [from, e_i] = prevs[v];
        push = min((ll)edges[e_i].rem_flow(), push);
        v = from;
    }

    v = t;
    ll cost = 0;
    while (prevs[v].first != -1) {
        auto [from, e_i] = prevs[v];
        cost += edges[e_i].cost(push);
        edges[e_i].flow += push;
        edges[e_i ^ 1].flow -= push;
        v = from;
    }

    return {push, cost};
}

pair<ull, ll> mcmf(int s, int t, int n) {
    spfa(s, n);
    ull max_flow = 0;
    ll min_cost = 0;
    while (prevs[t].first != -1) {
        const auto [flow, cost] = increase_path(t);
        max_flow += flow;
        min_cost += cost;
        spfa(s, n);
    }

    return {max_flow, min_cost};
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    g.resize(n, {});
    edges.reserve(2 * m);

    int u, v, cap, cost;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> cap >> cost;
        --u; --v;
        add_edge(u, v, cost, cap);
    }

    auto [max_flow, min_cost] = mcmf(0, n-1, n);
    cout << min_cost << endl;
}