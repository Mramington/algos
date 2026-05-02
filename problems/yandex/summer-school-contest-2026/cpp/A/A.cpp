#include <iostream>
#include <set>
#include <unordered_map>

using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    unordered_map<char, set<pair<int, string>>> mp;
    mp.reserve(30);
    set<pair<int, string>> st;
    int n, k;
    cin >> n >> k;
    string s;
    char c;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        c = s[0];
        if (mp.find(c) == mp.end())mp[c] = {{0, s}};
        else mp[c].insert({0, s});
    }
    for (int i = 0; i < k; ++i) {
        cin >> c;
        auto it = mp[c].begin();
        auto [cnt, word] = *it;
        cout << word << '\n';
        mp[c].erase(it);
        mp[c].insert({++cnt, word});
    }
    cout << endl;
    return 0;
}