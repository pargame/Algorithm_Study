//https://school.programmers.co.kr/learn/courses/30/lessons/92345
// 제한사항
// 1 ≤ board의 세로 길이 ≤ 5
// 1 ≤ board의 가로 길이 ≤ 5
// board의 원소는 0 또는 1입니다.
// 0은 발판이 없음을, 1은 발판이 있음을 나타냅니다.
// 게임 보드의 좌측 상단 좌표는 (0, 0), 우측 하단 좌표는 (board의 세로 길이 - 1, board의 가로 길이 - 1)입니다.
// aloc과 bloc은 각각 플레이어 A의 캐릭터와 플레이어 B의 캐릭터 초기 위치를 나타내는 좌표값이며 [r, c] 형태입니다.
// r은 몇 번째 행인지를 나타냅니다.
// 0 ≤ r < board의 세로 길이
// c는 몇 번째 열인지를 나타냅니다.
// 0 ≤ c < board의 가로 길이
// 초기 보드의 aloc과 bloc 위치는 항상 발판이 있는 곳입니다.
// aloc과 bloc이 같을 수 있습니다.
// 상대 플레이어의 캐릭터가 있는 칸으로 이동할 수 있습니다.
#include <vector>
#include <utility>
#include <stack>

using namespace std;

struct Frame {
    int i, j;
    int v = -1;  //최적값
    int nd = 0;  //다음 방향
    Frame(int _i, int _j) :i(_i), j(_j) {}
};

vector<pair<int, int>> dir{ {1,0} ,{0,1} ,{-1,0} ,{0,-1} };

int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {
    stack<Frame> st1, st2;
    st1.push(Frame(aloc[0], aloc[1]));
    st2.push(Frame(bloc[0], bloc[1]));

    while(!(st1.size() == 1 && st1.top().nd == 4)) {
        stack<Frame> &turn = (st1.size() + st2.size()) % 2 == 0 ? st1 : st2;
        Frame &top = turn.top();

        int ni = top.i + dir[top.nd].first;
        int nj = top.j + dir[top.nd].second;
        if(ni < 0 || nj < 0 || board.size() <= ni || board[0].size() <= nj || board[ni][nj] == 0) {
            ++top.nd;
        }
        else if() {

        }



    }


}