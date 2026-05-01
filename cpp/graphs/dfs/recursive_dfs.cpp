#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> g;
vector<bool> visited;
vector<int> result;

void dfs_template(
    int u
) {
    visited[u] = true;
    result.push_back(u);
    for (int i = 0; i < g[u].size(); ++i) {
        int v = g[u][i];
        if (visited[v]) continue;
        dfs_template(v);
    }
}