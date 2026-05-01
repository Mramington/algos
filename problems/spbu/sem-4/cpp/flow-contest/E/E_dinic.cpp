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

int char2val(const char c) {
    switch (c) {
        case 'H': return 1;
        case 'O': return 2;
        case 'N': return 3;
        case 'C': return 4;
        default: return 0;
    }
}

void add_side_edges(int i, int j, int N, int M) {
    int from = M * i + j;
    int shift = N * M;
    if (i != 0) {
        int to = shift + M * (i - 1) + j;
        add_edge(from, to, 1);
    }
    if (i != N - 1) {
        int to = shift + M * (i + 1) + j;
        add_edge(from, to, 1);
    }

    if (j != 0) {
        int to = shift + M * i + j - 1;
        add_edge(from, to, 1);
    }
    if (j != M - 1) {
        int to = shift + M * i + j + 1;
        add_edge(from, to, 1);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int N, M, s, t;
    cin >> N >> M;
    g.assign(2 * N * M + 2, {});
    edges.reserve(6 * N * M);
    vector<bool> colors(N, false);
    s = g.size() - 2; t = g.size() - 1;
    int val;
    char c;
    ll need_s_flow = 0;
    ll need_t_flow = 0;
    bool was_atom = false;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> c;
            val = char2val(c);
            if (!val) continue;
            was_atom = true;

            int pos = M * i + j;
            int shift = N * M;
            int color = (i + j) % 2;
            if (!color) {
                need_t_flow += val;
                add_edge(shift + pos, t, val);
            }
            else {
                need_s_flow += val;
                add_edge(s, pos, val);
                add_side_edges(i, j, N, M);
            }
        }
    }

    ll max_flow = dinic(s, t);
    if (was_atom && max_flow == need_t_flow && max_flow == need_s_flow) {
        cout << "Valid" << endl;
    } else cout << "Invalid" << endl;

    return 0;
}