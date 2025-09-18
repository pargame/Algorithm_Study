// https://www.acmicpc.net/problem/3109
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int constexpr NONE = 2;

class Element {
  public:
    vector<vector<int>> waitQ;
    Element() = default;
    Element(vector<vector<char>> map, int const _i) {
        int i = _i, j = 0; // 최근 업데이트 된 map 좌표
        vector<pair<int, vector<int>>> S(
            1, {NONE, GetPsbs(map, i, j)}); // 기저 요소
        while (!S.empty()) {
            if (S.size() == map[0].size()) { // 모든 열 전파된 상황을 찾았으면
                waitQ.push_back(vector<int>()); // 새로 벡터 만들고
                for (auto [cur, _] : S)         // 그곳에 cur 모두 푸시
                    waitQ.back().push_back(cur);
                S.pop_back(); // pop
                continue;
            }
            pair<int, vector<int>> top = S.back();
            if (top.second.empty()) { // top의 가능 후보(psbs)가 더 없으면
                map[i][j] = '.';      // map 역전파
                i -= top.first, --j;  // i, j 역전파
                S.pop_back();         // pop
                continue;
            }
            // 푸시 상황
            int cur = top.second.back();
            i += cur, ++j; // i,j 업데이트
            top.second.pop_back();
            map[i][j] = 'X';
            S.push_back({cur, GetPsbs(map, i, j)});
        }
    }

    vector<int> GetPsbs(vector<vector<char>> const &_map, int const &_i, int j) {
        ++j;
        if (_map[0].size() == j)
            return vector<int>();

        vector<int> rtn;
        for (int i : {_i - 1, _i, _i + 1}) {
            if (i < 0 || _map.size() <= i || _map[i][j] == 'X')
                continue;
            rtn.push_back(i - _i);
        }
        return rtn;
    }
};

int main() {
    int R = 0, C = 0;
    cin >> R >> C;
    vector<vector<char>> map(R, vector<char>(C));
    for (vector<char> &_ : map)
        for (char &__ : _)
            cin >> __;

    Element test(map, 0);
    for (vector<int> &Q : test.waitQ) {
        for (int &n : Q)
            cout << n << ' ';
        cout << endl;
    }

    return 0;
}