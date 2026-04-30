#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef struct Edge {
    int to;
    int cap;
    int flow;

    int rem_flow() { return cap - flow; }
};

typedef struct Frame
{
    int u;
    int mn;
};

typedef struct Prev {
    int from;
    int edge_id;
};

vector<vector<int>> g;
vector<Edge> edges;
vector<bool> visited;
vector<Prev> used_edge;

void add_edge(int from, int to, int cap) {
    g[from].push_back(edges.size());
    edges.push_back({to, cap, 0});
    g[to].push_back(edges.size());
    edges.push_back({from, 0, 0});
}

int s2t_bfs(
    const vector<vector<int>>& g, int s, int t
) {
    int n = g.size();
    visited.assign(n, false);
    visited[s] = true;
    used_edge.assign(g.size(), {-1, -1});

    queue<Frame> q{};
    q.push({s, INT_MAX});
    while(!q.empty()) {
        Frame fr_u = q.front(); q.pop();
        int u = fr_u.u;
        for (int i = 0; i < g[u].size(); ++i) {
            int e_i = g[u][i];
            Edge& e = edges[e_i];
            int to = e.to;

            if (visited[to]) continue;
            int rem = e.rem_flow();
            if (rem <= 0) continue;

            visited[to] = true;
            used_edge[to] = {u, e_i};
            q.push({to, min(fr_u.mn, rem)});

            if (to != t) continue;

            int mn = min(fr_u.mn, rem);
            while (to != s) {
                e_i = used_edge[to].edge_id;
                edges[e_i].flow += mn;
                edges[e_i ^ 1].flow -= mn;
                to = used_edge[to].from;
            }
            return mn;
        }
    }

    return 0;
}

int edmonds_karp(int s, int t) {
    int max_flow = 0;
    while(true) {
        int flow = s2t_bfs(g, s, t);
        if (flow <= 0) return max_flow;
        max_flow += flow;
    }

    return max_flow;
}
