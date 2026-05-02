#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

using ll = long long;

int m;

int get_mask(const string& s) {
    int mask = 0;
    for (int i = 0; i < m; ++i) {
        if (s[i] != '?') {
            mask |= (1 << i);
        }
    }
    return mask;
}

int proj_hash(const string& s, int mask) {
    int h = 0;
    for (int i = 0; i < m; ++i) {
        if (mask & (1 << i)) {
            h = h * 26 + (s[i] - 'a');
        }
    }
    return h;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n >> m;
    vector<string> groups[64];

    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        int mask = get_mask(s);
        groups[mask].push_back(s);
    }

    ll ans = 0;

    for (int mask1 = 0; mask1 < (1 << m); ++mask1) {
        for (int mask2 = mask1; mask2 < (1 << m); ++mask2) {
            if (groups[mask1].empty() || groups[mask2].empty()) continue;

            int mask = mask1 & mask2;
            unordered_map<int, ll> cnt;

            if (mask1 == mask2) {
                for (const auto& s : groups[mask1]) {
                    int h = proj_hash(s, mask);
                    ++cnt[h];
                }

                for (auto [h, c] : cnt) {
                    ans += c * (c - 1) / 2;
                }
            } else {
                if (!mask) {
                    ans += 1LL * groups[mask1].size() * groups[mask2].size();
                    continue;
                }

                cnt.reserve(groups[mask1].size() * 2);

                for (const auto& s : groups[mask1]) {
                    int h = proj_hash(s, mask);
                    ++cnt[h];
                }

                for (const auto& s : groups[mask2]) {
                    int h = proj_hash(s, mask);
                    if (cnt.count(h)) {
                        ans += cnt[h];
                    }
                }
            }
        }
    }

    cout << ans << endl;
    return 0;
}