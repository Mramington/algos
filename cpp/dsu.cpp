#include <vector>
#include <iostream>

using namespace std;
int parent[100];
vector<int> sizes = vector<int>(100, 0);

int make_set(int v) {
    return parent[v] = v;
    sizes[v] = 1;
}

int find_set(int u) {
    if (parent[u] == u) return u;
    return parent[u] = find_set(parent[u]);
}

int union_sets(int u, int v) {
    int up = find_set(u);
    int vp = find_set(v);
    if (up == vp) return up;

    if (sizes[up] < sizes[vp]) {
        swap(up, vp);
    }
    sizes[vp] += sizes[up];
    parent[vp] = up;
    return up;
}

