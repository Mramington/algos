#include <iostream>
#include <vector>

using namespace std;

// metres
int parse_type(int type) {
    switch (type)
    {
    case 1: return 1;
    case 2: return 2;
    case 3: return 4;
    default: return 0;
    };
}

static inline int metres2points(int metres) {
    switch (metres)
    {
    case 1: return 1;
    case 2: return 3;
    case 4: return 5;
    default: return 0;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    bool lost_game = false;

    int n;
    cin >> n;
    int x;
    vector<int> starts(n);
    for (int i = 0; i < n; ++i) {
        cin >> starts[i];
    }

    vector<bool> track(1000000 + 100, false);
    int type, metres;
    for (int i = 0; i < n; ++i) {
        cin >> type;
        metres = parse_type(type);

        if (track[starts[i] - 1]) lost_game = true;
        for (int j = starts[i]; j < starts[i] + metres; ++j) {
            if (track[j]) lost_game = true;
            track[j] = true;
        }
    }

    int m;
    cin >> m;
    starts.resize(m);
    vector<bool> is_start(1000000 + 100, false);
    for (int i = 0; i < m; ++i) {
        cin >> starts[i];
        is_start[starts[i]] = true;
    }

    vector<bool> jumps(1000000 + 100, false);
    for (int i = 0; i < m; ++i) {
        cin >> metres;
        for (int j = starts[i]; j < starts[i] + metres; ++j) {
            jumps[j] = true;
        }
    }

    if (lost_game) {
        cout << 0 << endl;
        return 0;
    }

    int metres_cnt = 0;
    int total = 0;
    bool lost = false;
    for (int i = 0; i < track.size(); ++i) {
        if (track[i]) {
            if (metres_cnt && is_start[i]) lost = true;
            ++metres_cnt;
            if (!jumps[i]) lost = true;
        }
        else {
            if (lost) --total;
            else total += metres2points(metres_cnt);
            metres_cnt = 0;
            lost = false;
        }
    }

    total = total < 0 ? 0 : total;
    cout << total << endl;
    return 0;
}