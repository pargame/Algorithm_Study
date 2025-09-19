// https://www.acmicpc.net/problem/3109
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
    int R = 0, C = 0; cin >> R >> C;
    vector<vector<char>> grid(R, vector<char>(C));
    for (vector<char>& arr : grid) {
        for (char& cell : arr) {
            cin >> cell;
        }
    }

    int ans = 0;
    for (int si = 0;si < R;++si) {
        int i = si, j = 0;
        for (;j < C - 1;) {
            int nj = j + 1;
            for (int di : {-1, 0, 1}) {
                int ni = i + di;
                if (0 <= ni && ni < R && 0 <= nj && nj < C && grid[ni][nj] == '.') {
                    i = ni, j = nj;
                    grid[i][j] = 'X';
                    break;
                }
            }
            if (j < nj) break;
        }
        if (j == C - 1)
            ++ans;
    }

    cout << ans;

    return 0;
}