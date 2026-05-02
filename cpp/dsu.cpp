#include <vector>
#include <iostream>

using namespace std;

vector<int> parent(100);
vector<int> ranks(100, 0);

int make_set(int v) {
    ranks[v] = 1;
    return parent[v] = v;
}

int find_set(int u) {
    if (parent[u] == u) return u;
    return parent[u] = find_set(parent[u]);
}

int union_sets(int u, int v) {
    int up = find_set(u);
    int vp = find_set(v);
    if (up == vp) return up;

    if (ranks[up] < ranks[vp]) {
        swap(up, vp);
    }
    if (ranks[vp] == ranks[up]) ++ranks[up];
    parent[vp] = up;
    return up;
}
