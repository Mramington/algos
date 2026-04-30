#include <iostream>
#include <vector>
#include <queue>

using namespace std;


void bfs_template(
    const vector<vector<int>>& g, int s,
    vector<int>& result
) {
    int n = g.size();
    result.reserve(n);
    result.push_back(s);

    vector<bool> visited(n);
    visited[s] = true;

    queue<int> q{};
    q.push(s);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if (visited[v]) continue;
            result.push_back(v);
            visited[v] = true;
            q.push(v);
        }
    }
}