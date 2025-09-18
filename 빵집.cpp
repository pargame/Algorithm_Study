// https://www.acmicpc.net/problem/3109
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

int R, C;
vector<vector<char>> grid;
vector<vector<bool>> visited;

bool find_path_iterative(int start_x) {
  struct Frame
  {
    int x;
    int y;
    int next;
  };
  int dirs[3] = { -1, 0, 1 };
  stack<Frame> st;
  st.push({ start_x, 0, 0 });
  visited[start_x][0] = true;

  while (!st.empty()) {
    Frame& f = st.top();
    int x = f.x;
    int y = f.y;
    if (y == C - 1)
      return true;
    if (f.next < 3) {
      int dx = dirs[f.next++];
      int nx = x + dx;
      int ny = y + 1;
      if (nx >= 0 && nx < R && ny < C && grid[nx][ny] == '.' &&
        !visited[nx][ny]) {
        visited[nx][ny] = true; // mark when pushing (match recursive behavior)
        st.push({ nx, ny, 0 });
      }
    }
    else st.pop();

  }
  return false;
}

int main() {
  cin >> R >> C;
  grid.assign(R, vector<char>(C));
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      cin >> grid[i][j];
    }
  }

  visited.assign(R, vector<bool>(C, false));
  int count = 0;

  // 위쪽 행부터 시작해서 그리디하게 파이프 설치
  for (int i = 0; i < R; ++i) {
    if (grid[i][0] == '.' && !visited[i][0] && find_path_iterative(i)) {
      count++;
    }
  }

  cout << count;
  return 0;
}