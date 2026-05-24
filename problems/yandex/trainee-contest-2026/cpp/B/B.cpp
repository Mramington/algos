#include <iostream>
#include <vector>

using namespace std;

int h, w;
vector<int> totals;
vector<int> stones;
vector<int> sand_pointer;
vector<vector<int>> columns;


bool is_stone(char c) { return c == 'x'; }

void walk(int pos, int side) {
    if (pos < 0 || pos >= w) return;

    if (side > 0) {
        // if (totals[pos] - totals[pos - 1] <= 1) return;
        int ptr = sand_pointer[pos];
        if (ptr == -1 || columns[pos].size() == ptr) return;
        if (columns[pos][ptr] - totals[pos - 1] <= 1) return;

        ++sand_pointer[pos];
    } else {
        if (totals[pos] - totals[pos + 1] <= 1) return;
    }

    --totals[pos];
    ++totals[pos - side];
    walk(pos + side, side);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> h >> w;
    columns.resize(w);
    for (int i = 0; i < w; ++i) columns[i].reserve(h);

    totals.assign(w, h);
    stones.assign(w, 0);
    sand_pointer.assign(w, -1);

    char c;
    for (int i = h; i > 0; --i) {
        for (int j = 0; j < w; ++j) {
            cin >> c;
            if (is_stone(c)) {
                ++stones[j];
            } else {
                columns[j].push_back(i);
                if (sand_pointer[j] == -1) {
                    sand_pointer[j] = columns[j].size() - 1;
                }
            }
        }
    }

    for (int i = 0; i < w; ++i) {
        while(stones[i] > 0) {
            --stones[i];
            --totals[i];
            walk(i + 1, +1);
            walk(i - 1, -1);
        }
    }

    for (int i = h; i > 0; --i) {
        for (int j = 0; j < w; ++j) {
            cout << (totals[j] >= i ? '0' : '-') << ' ';
        }
        cout << '\n';
    }

    return 0;
}