#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>

using namespace std;

typedef struct edge
{
    int to;
    int w;
    int cap;
    int flow;

    int rem_flow() { return cap - flow; };
    int cost(int add_flow) { return add_flow * w; };
} edge;

vector<vector<int>> g; 
vector<edge> edges;
vector<int> d;
vector<pair<int, int>> prevs;

void add_edge(int from, int to, int w, int cap) {
    g[from].push_back(edges.size());
    edges.push_back({to, w, cap, 0});
    g[to].push_back(edges.size());
    edges.push_back({from, -w, 0, 0});
}

queue<int> q;
vector<bool> in_queue;

void spfa(int s, int n) {
    d.assign(n, INT_MAX);
    prevs.assign(n, {-1, -1});
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
            if (e.rem_flow() > 0 && d[from] + e.w < d[to]) {
                d[to] = d[from] + e.w;
                prevs[to] = {from, i};

                if (in_queue[to]) continue;
                in_queue[to] = 1;
                q.push(to);
            }
        }
    }
}

pair<int, int> increase_path(int t) {
    int v = t;
    int push = INT_MAX;
    while (prevs[v].first != -1) {
        auto [from, e_i] = prevs[v];
        push = min(edges[e_i].rem_flow(), push);
        v = from;
    }

    v = t;
    int cost = 0;
    while (prevs[v].first != -1) {
        auto [from, e_i] = prevs[v];
        cost += edges[e_i].cost(push);
        edges[e_i].flow += push;
        edges[e_i ^ 1].flow -= push;
        v = from;
    }

    return {push, cost};
}

pair<int, int> mcmf(int s, int t, int n) {
    spfa(s, n);
    int max_flow = 0;
    int min_cost = 0;
    while (prevs[t].first != -1) {
        const auto [flow, cost] = increase_path(t);
        max_flow += flow;
        min_cost += cost;
        spfa(s, n);
    }

    return {max_flow, min_cost};
}