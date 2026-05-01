#include <iostream>
#include <vector>

using namespace std;


// -------------- Iterative ---------------
typedef struct Frame {
    int u;
    int idx;
};

void dfs_template(
    const vector<vector<int>>& g, int s,
    vector<int>& result
) {
    int n = g.size();
    result.reserve(n);
    result.push_back(s);

    vector<Frame> st;
    st.push_back({s, 0});

    vector<bool> visited(n, false);
    visited[s] = true;

    while (!st.empty()) {
        // {
        //
        Frame& u_fr = st.back();
        int u = u_fr.u;

        // if have used all edges
        if (u_fr.idx == g[u].size()) {
            st.pop_back();
            continue;
        }
        //
        // }

        // body {
        int v = g[u][u_fr.idx++];
        if(visited[v]) continue;

        visited[v] = true;
        result.push_back(v);
        st.push_back({v, 0});
        // }
    }
}