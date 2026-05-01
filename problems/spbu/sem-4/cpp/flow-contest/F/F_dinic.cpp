#include <iostream>
#include <iomanip>
#include <vector>
#include <climits>
#include <queue>
#include <unordered_map>

using namespace std;

using ll = long long;

typedef struct Edge {
    int to;
    ll cap;
    ll flow;

    ll rem_flow() const { return cap - flow; }
} Edge;

vector<vector<int>> g;
vector<Edge> edges;
// last used edge_id of every vertex in dfs
vector<int> ptr;
// layer of vertex
vector<int> d;


void add_edge(
    int from, int to, ll cap
) {
    g[from].push_back(edges.size());
    edges.push_back({to, cap, 0});
    g[to].push_back(edges.size());
    edges.push_back({from, 0, 0});
}


ll dfs_block_flow(
    int u, int t, ll mn
) {
    if (u == t) return mn;
    for (int& i = ptr[u]; i < (int)g[u].size(); ++i) {
        int e_i = g[u][i];
        Edge& e = edges[e_i];
        int to = e.to;

        if (d[to] != d[u] + 1) continue;

        ll rem = e.rem_flow();
        if (rem <= 0) continue;

        ll flow = dfs_block_flow(to, t, min(mn, rem));
        if (flow <= 0) continue;

        e.flow += flow;
        edges[e_i ^ 1].flow -= flow;
        return flow;
    }

    return 0;
}

ll block_flow(
    int s, int t
) {
    ll max_flow = 0;
    ptr.assign(g.size(), 0);
    while (true) {
        ll flow = dfs_block_flow(s, t, LLONG_MAX);
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
        for (int i = 0; i < (int)g[u].size(); ++i) {
            int e_i = g[u][i];
            Edge& e = edges[e_i];
            int to = e.to;

            if (d[to] != -1) continue;
            ll rem = e.rem_flow();
            if (rem <= 0) continue;

            d[to] = d[u] + 1;
            if (to == t) return true;
            q.push(to);
        }
    }

    return false;
}

ll dinic(int s, int t) {
    ll max_flow = 0;
    while(layer_bfs(g, s, t)) {
        ll flow = block_flow(s, t);
        if (flow <= 0) return max_flow;
        max_flow += flow;
    }

    return max_flow;
}

vector<bool> cut_visited;

void cut_dfs(int u) {
    cut_visited[u] = true;

    for (int i = 0; i < g[u].size(); ++i) {
        int e_i = g[u][i];
        Edge& e = edges[e_i];

        int to = e.to;
        if(cut_visited[to]) continue;
        if (e.rem_flow() <= 0) continue;

        cut_dfs(to);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int N, M, s, t;
    cin >> N >> M;
    g.assign(N + M + 2, {});
    edges.reserve(3 * M + N);
    s = g.size() - 2; t = g.size() - 1;
    int w;
    for (int i = 0; i < N; ++i) {
        cin >> w;
        add_edge(i, t, w);
    }

    int from, to;
    ll ans = 0;
    for (int i = N; i < N + M; ++i) {
        cin >> from >> to >> w;
        --from; --to;
        ans += w;
        add_edge(s, i, w);
        add_edge(i, from, INT_MAX);
        add_edge(i, to, INT_MAX);
    }

    ll max_flow = dinic(s, t);
    cout << ans - max_flow;
}