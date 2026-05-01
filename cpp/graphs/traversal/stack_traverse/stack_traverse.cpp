#include <iostream>
#include <vector>

using namespace std;

// -------------- Iterative ---------------
void stack_traverse_template(
    const vector<vector<int>>& g, int s,
    vector<int>& result
) {
    int n = g.size();
    result.reserve(n);
    result.push_back(s);

    vector<int> st;
    st.push_back(s);

    vector<bool> visited(n, false);
    visited[s] = true;

    while (!st.empty()) {
        int u = st.back(); st.pop_back();
        for (int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if(visited[v]) continue;

            visited[v] = true;
            result.push_back(v);
            st.push_back(v);
        }
    }
}