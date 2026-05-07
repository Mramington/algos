#include <iostream>
#include <vector>
#include <limits>

using namespace std;

typedef struct edge
{
    int from;
    int to;
    int w;
} edge;

vector<edge> edges;
vector<int> d;
vector<int> prevs;

bool bellman_ford(int s, int n) {
    d.assign(n, INT_MAX);
    prevs.assign(n, -1);
    d[s] = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (const auto& [from, to, w] : edges) {
            if (d[from] + w < d[to]) {
                d[to] = d[from] + w;
                prevs[to] = from;
            }
        }
    }

    for (const auto& [from, to, w] : edges) {
        if (d[from] + w < d[to]) {
            // cycle with negative weight
            return true;
        }
    }

    return false;
}