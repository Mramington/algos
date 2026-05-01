#include <iostream>
#include <vector>
#include <climits>

using namespace std;

typedef struct Edge {
    int to;
    int cap;
    int flow;

    int rem_flow() {
        return cap - flow;
    }
};

vector<vector<int>> g;
vector<Edge> edges;

void add_edge(
    int from, int to, int cap
) {
    g[from].push_back(edges.size());
    edges.push_back({to, cap, 0});
    g[to].push_back(edges.size());
    edges.push_back({from, 0, 0});
}


vector<bool> visited;

int s2t_dfs(
    int u, int t, int mn
) {
    if (u == t) return mn;
    visited[u] = true;
    for (int i = 0; i < g[u].size(); ++i) {
        int e_i = g[u][i];
        Edge& e = edges[e_i];
        if (visited[e.to]) continue;

        int rem = e.rem_flow();
        if (rem <= 0) continue;

        int res = s2t_dfs(e.to, t, min(mn, rem));
        if (res <= 0) continue;

        edges[e_i ^ 1].flow -= res;
        e.flow += res;
        return res;
    }

    return 0;
}

int ford_falkerson(
    int s, int t
) {
    int max_flow = 0;
    while (true) {
        visited.assign(g.size(), 0);
        int flow = s2t_dfs(s, t, INT_MAX);
        if (flow <= 0) break;
        max_flow += flow;
    }

    return max_flow;
}
