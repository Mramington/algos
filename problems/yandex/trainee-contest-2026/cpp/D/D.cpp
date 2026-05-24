#include <vector>
#include <chrono>
#include <random>
#include <unordered_map>
#include <iostream>

using namespace std;

using ll = long long;
using ull = unsigned long long;

int N = 40;
ull full = (1ULL << 40) - 1;

ull get_mask() {
    static mt19937_64 rng(
        chrono::steady_clock::now().time_since_epoch().count()
    );

    ull mask = 0;
    while (!mask) {
        mask = rng() & full;
    }

    return mask;
}

void print_mask(ull mask) {
    vector<int> ans;

    for (int i = 0; i < N; ++i) {
        if ((mask >> i) & 1ULL) {
            ans.push_back(i + 1);
        }
    }

    cout << ans.size() << '\n';

    for (int x : ans) {
        cout << x << ' ';
    }

    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<ll> a(N);

    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }

    unordered_map<ull, ull> was;
    was.reserve(3000000);

    for (ull iter = 1; ; ++iter) {
        ull mask = get_mask();
        ull sum = 0;

        for (int i = 0; i < N; ++i) {
            if ((mask >> i) & 1ULL) {
                sum += a[i];
            }
        }

        auto it = was.find(sum);

        if (it != was.end()) {
            ull old = it->second;

            if (old == mask) {
                continue;
            }

            ull first = old & ~mask;
            ull second = mask & ~old;

            if (first == 0 || second == 0) {
                continue;
            }

            print_mask(first);
            print_mask(second);

            return 0;
        }

        was[sum] = mask;
    }
}