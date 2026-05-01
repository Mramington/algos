#include <iostream>
#include <iomanip>
#include <vector>
#include <climits>
#include <queue>

using namespace std;


typedef struct Edge {
    int to;
    int cap;
    int flow;

    int rem_flow() const { return cap - flow; }
} Edge;

typedef struct Frame
{
    int u;
    int mn;
} Frame;

typedef struct Prev {
    int from;
    int edge_id;
} Prev;

vector<vector<int>> g;
vector<Edge> edges;
vector<bool> visited;
vector<Prev> used_edge;

void add_edge(
    int from, int to, int cap
) {
    g[from].push_back(edges.size());
    edges.push_back({to, cap, 0});
    g[to].push_back(edges.size());
    edges.push_back({from, cap, 0});
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

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int N, M;
    cin >> N >> M;
    g.assign(N, {});
    edges.reserve(2 * M);
    int from, to, cap;
    for (int i = 0; i < M; ++i) {
        cin >> from >> to >> cap;
        --from; --to;
        add_edge(from, to, cap);
    }

    int max_flow = edmonds_karp(0, N-1);
    cout << max_flow << ".00000000000000000000" << '\n';
    for (int i = 0; i < M; ++i) {
        cout << edges[2 * i].flow << ".00000000000000000000" << "\n";
    }
}