#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 60);
const int LIMIT = 1001;

int n;
vector<int> w;
vector<long long> pref;

vector<vector<long long>> dp;
vector<vector<int>> optL, optR;
vector<vector<int>> ways;

long long sumW(int l, int r) {
    if (l > r) return 0;
    return pref[r] - pref[l - 1];
}

long long getDp(int l, int r) {
    if (l > r) return 0;
    return dp[l][r];
}

int getWays(int l, int r) {
    if (l > r) return 1;
    return ways[l][r];
}

bool isOptimalRoot(int l, int r, int k) {
    long long cur = getDp(l, k - 1) + getDp(k + 1, r) + sumW(l, r);
    return cur == dp[l][r];
}

vector<vector<int>> build(int l, int r) {
    if (l > r) {
        return {{}};
    }

    vector<vector<int>> ans;

    for (int k = optL[l][r]; k <= optR[l][r]; k++) {
        if (!isOptimalRoot(l, r, k)) continue;

        auto leftTrees = build(l, k - 1);
        auto rightTrees = build(k + 1, r);

        for (auto &L : leftTrees) {
            for (auto &R : rightTrees) {
                vector<int> cur;
                cur.reserve(1 + L.size() + R.size());

                cur.push_back(k);

                for (int x : L) cur.push_back(x);
                for (int x : R) cur.push_back(x);

                ans.push_back(cur);
            }
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    w.assign(n + 1, 0);
    pref.assign(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        pref[i] = pref[i - 1] + w[i];
    }

    dp.assign(n + 2, vector<long long>(n + 2, 0));
    optL.assign(n + 2, vector<int>(n + 2, 0));
    optR.assign(n + 2, vector<int>(n + 2, 0));
    ways.assign(n + 2, vector<int>(n + 2, 0));

    for (int i = 1; i <= n; i++) {
        dp[i][i] = w[i];
        optL[i][i] = optR[i][i] = i;
        ways[i][i] = 1;
    }

    for (int len = 2; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;

            int from = optL[l][r - 1];
            int to = optR[l + 1][r];

            dp[l][r] = INF;

            for (int k = from; k <= to; k++) {
                long long cur = getDp(l, k - 1) + getDp(k + 1, r) + sumW(l, r);

                if (cur < dp[l][r]) {
                    dp[l][r] = cur;
                    optL[l][r] = optR[l][r] = k;
                } else if (cur == dp[l][r]) {
                    optR[l][r] = k;
                }
            }

            long long cnt = 0;

            for (int k = optL[l][r]; k <= optR[l][r]; k++) {
                if (!isOptimalRoot(l, r, k)) continue;

                cnt += 1LL * getWays(l, k - 1) * getWays(k + 1, r);

                if (cnt >= LIMIT) {
                    cnt = LIMIT;
                    break;
                }
            }

            ways[l][r] = (int)cnt;
        }
    }

    auto answers = build(1, n);

    cout << answers.size() << '\n';

    for (auto &tree : answers) {
        for (int i = 0; i < (int)tree.size(); i++) {
            if (i) cout << ' ';
            cout << tree[i];
        }
        cout << '\n';
    }

    return 0;
}