#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>

using namespace std;

typedef struct edge
{
    int to;
    int w;
} edge;

vector<vector<int>> g; 
vector<edge> edges;
vector<int> d;
vector<int> prevs;

queue<int> q;
vector<bool> in_queue;

bool spfa(int s, int n) {
    d.assign(n, INT_MAX);
    prevs.assign(n, -1);
    d[s] = 0;

    in_queue.assign(n, 0);
    q.push(s);

    int from, to;
    while(!q.empty()) {
        from = q.front(); q.pop();
        in_queue[from] = 0;
        for (const int i : g[from]) {
            edge& e = edges[i];
            to = e.to;
            if (d[from] + e.w < d[to]) {
                d[to] = d[from] + e.w;
                prevs[to] = from;

                if (in_queue[to]) continue;
                in_queue[to] = 1;
                q.push(to);
            }
        }
    }

    for (int from = 0; from < n; ++from) {
        for (const int i : g[from]) {
            edge& e = edges[i];
            if (d[from] + e.w < d[e.to]) {
                return true;
            }
        }
    }

    return false;
}