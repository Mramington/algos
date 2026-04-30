#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

typedef struct Edge {
    int to;
    int cap;
    int flow;

    int rem_flow() const { return cap - flow; }
};

vector<vector<int>> g;
vector<Edge> edges;
// last used edge_id of every vertex in dfs
vector<int> ptr;
// layer of vertex
vector<int> d;


void add_edge(int from, int to, int cap) {
    g[from].push_back(edges.size());
    edges.push_back({to, cap, 0});
    g[to].push_back(edges.size());
    edges.push_back({from, 0, 0});
}


int dfs_block_flow(
    int u, int t, int mn
) {
    if (u == t) return mn;
    for (int& i = ptr[u]; i < g[u].size(); ++i) {
        int e_i = g[u][i];
        Edge& e = edges[e_i];
        int to = e.to;

        if (d[to] != d[u] + 1) continue;

        int rem = e.rem_flow();
        if (rem <= 0) continue;

        int flow = dfs_block_flow(to, t, min(mn, rem));
        if (flow <= 0) continue;

        e.flow += flow;
        edges[e_i ^ 1].flow -= flow;
        return flow;
    }

    return 0;
}

int block_flow(
    int s, int t
) {
    int max_flow = 0;
    ptr.assign(g.size(), 0);
    while (true) {
        int flow = dfs_block_flow(s, t, INT_MAX);
        if (flow <= 0) break;
        max_flow += flow;
    }

    return max_flow;
}

bool layer_bfs(
    const vector<vector<int>>& g, int s, int t
) {
    int n = g.size();
    d.assign(n, -1);
    d[s] = 0;

    queue<int> q{};
    q.push(s);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < g[u].size(); ++i) {
            int e_i = g[u][i];
            Edge& e = edges[e_i];
            int to = e.to;

            if (d[to] != -1) continue;
            int rem = e.rem_flow();
            if (rem <= 0) continue;

            d[to] = d[u] + 1;
            if (to == t) return true;
            q.push(to);
        }
    }

    return false;
}

int dinic(int s, int t) {
    int max_flow = 0;
    while(layer_bfs(g, s, t)) {
        int flow = block_flow(s, t);
        if (flow <= 0) return max_flow;
        max_flow += flow;
    }

    return max_flow;
}