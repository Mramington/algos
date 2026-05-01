#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> d;
vector<vector<int>> g;
vector<int> prevs;
vector<vector<int>> weights;

void dijkstra(int s) {
    prevs.assign(g.size(), -1);
    d.assign(g.size(), INT_MAX);
    d[s] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({d[s], s});
    while (!q.empty()) {
        auto [dist, u] = q.top(); q.pop();
        if (dist > d[u]) continue;

        for (int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            int w = weights[u][i];
            if (d[u] + w < d[v]) {
                prevs[v] = u;
                d[v] = d[u] + w;
                q.push({d[v], v});
            }
        }
    }
}
