#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <climits>

using namespace std;

using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> points(n);
    int px, py;
    for (int i = 0; i < n; ++i) {
        cin >> px >> py;
        points[i] = {abs(px), abs(py)};
    }

    sort(points.begin(), points.end(), greater<pair<int, int>>());

    vector<ll> dp(n + 1, 0);
    ll y;
    for (int i = n - 1; i >= 0; --i) {
        y = 0;
        dp[i] = LONG_MAX;
        for (int j = i; j < n; ++j) {
            y = max(y, (ll)points[j].second);
            ll area = dp[j + 1] + points[i].first * y;
            dp[i] = min(dp[i], area);
        }
    }

    cout << dp[0] * 4 << endl;
    return 0;
}