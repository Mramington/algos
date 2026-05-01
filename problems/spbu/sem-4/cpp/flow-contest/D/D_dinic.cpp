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

vector<bool> visited;
vector<ll> flows;

ll decompose(
    int u, int t, ll mn, vector<int>& path
) {
    visited[u] = true;
    if (u == t) return mn;
    for (int i = 0; i < (int)g[u].size(); ++i) {
        int e_i = g[u][i];
        Edge& e = edges[e_i];
        int to = e.to;

        if (visited[to]) continue;
        if (e.flow <= 0) continue;

        path.push_back((e_i / 2) + 1);

        ll flow = decompose(to, t, min(e.flow, mn), path);
        visited[to] = false;
        if (flow == 0) {
            path.pop_back();
            continue;
        }
        edges[e_i].flow -= flow;
        edges[e_i ^ 1].flow += flow;
        return flow;
    }
    visited[u] = false;
    return 0;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int N, M, s, t;
    cin >> N >> M;
    s = 0; t = N - 1;
    g.assign(N, {});
    edges.reserve(2 * M);
    int from, to;
    ll cap;
    for (int i = 0; i < M; ++i) {
        cin >> from >> to >> cap;
        --from; --to;
        add_edge(from, to, cap);
    }

    ll max_flow = dinic(s, t);

    flows.reserve(M);
    vector<vector<int>> paths; paths.reserve(M);
    while (true) {
        visited.assign(N, false);
        vector<int> path;
        ll flow = decompose(s, t, LLONG_MAX, path);
        if (!flow) break;
        paths.push_back(path);
        flows.push_back(flow);
    }

    cout << flows.size() << '\n';
    for (int i = 0; i < (int)flows.size(); ++i) {
        cout << flows[i] << ' ' << paths[i].size();
        for (int j = 0; j < (int)paths[i].size(); ++j) {
            cout << ' ' << paths[i][j];
        }
        cout << '\n';
    }
    cout << endl;
}