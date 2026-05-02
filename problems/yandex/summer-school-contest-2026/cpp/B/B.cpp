#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

vector<int> parent;
vector<int> parent_set;
vector<int> sizes;

bool isNumber(const string& s) {
    return isdigit(s[0]);
}

int make_set(int v, int val) {
    sizes[v] = 1;
    parent_set[v] = val;
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

    if (sizes[up] < sizes[vp]) {
        swap(up, vp);
    }

    int& a = parent_set[up];
    int& b = parent_set[vp];
    if (a && b && (a != b)) return -1;
    else if (b) a = b;

    if (sizes[vp] == sizes[up]) ++sizes[up];

    parent[vp] = up;
    return up;
}

int main() {
    int n;
    cin >> n;

    unordered_map<string, int> mp;
    mp.reserve(n);
    parent.assign(2 * n, -1);
    parent_set.assign(2 * n, -1);
    sizes.assign(2 * n, 0);

    string s;
    for (int i = 0; i < n; ++i) {
        cin >> s;

        if (isNumber(s)) {
            make_set(i, atoi(s.c_str()));
        } else {
            if (mp.find(s) == mp.end()) {
                mp[s] = make_set(i, 0);
            }
            else parent[i] = find_set(mp[s]);
        }
    }

    for (int i = 0; i < n; ++i) {
        cin >> s;

        if (isNumber(s)) {
            make_set(n + i, atoi(s.c_str()));
            if (union_sets(n + i, i) == -1) {
                cout << "NO" << endl;
                return 0;
            }
        } else {
            if (mp.find(s) == mp.end()) {
                mp[s] = make_set(n + i, 0);
            }
            else parent[n + i] = find_set(mp[s]);

            if (union_sets(n + i, i) == -1) {
                cout << "NO" << endl;
                return 0;
            }
        }
    }
    cout << "YES" << endl;
    return 0;
}