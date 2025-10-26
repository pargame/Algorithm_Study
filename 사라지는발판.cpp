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
#include <queue>
#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {
    struct Frame {
        int turn, cnt;
        vector<vector<int>> loc;
        vector<vector<int>> b;

        Frame(int _turn, int _cnt, vector<vector<int>> _loc, vector<vector<int>> _b)
            :turn(_turn), cnt(_cnt), loc(_loc), b(_b) {
        }
    };
    vector<pair<int, int>> dir{ {1,0} ,{-1,0} ,{0,1} ,{0,-1} };

    queue<Frame> q;
    q.push(Frame(0, 0, vector<vector<int>>{{aloc[0], aloc[1]}, { bloc[0], bloc[1] }}, board));

    while(true) {
        Frame fr = q.front();
        q.pop();

        if(fr.b[fr.loc[fr.turn][0]][fr.loc[fr.turn][1]] == 0) {
            return fr.cnt;
        }

        int cur_turn = fr.turn;
        int op_turn = (fr.turn + 1) % 2;
        int cnt = fr.cnt;
        int cur_i = fr.loc[cur_turn][0], cur_j = fr.loc[cur_turn][1];
        int op_i = fr.loc[op_turn][0], op_j = fr.loc[op_turn][1];
        vector<vector<int>> b = fr.b;

        bool adjc = false;
        vector<pair<int, int>> psb_locs_without_adjc;

        for(auto &[di, dj] : dir) {
            int next_cur_i = cur_i + di, next_cur_j = cur_j + dj;
            if(next_cur_i < 0 || next_cur_j < 0 || board.size() <= next_cur_i || board[0].size() <= next_cur_j
                || b[next_cur_i][next_cur_j] == 0) {
                continue;
            }
            if(next_cur_i == op_i && next_cur_j == op_j) {
                adjc = true;
                continue;
            }
            psb_locs_without_adjc.push_back({ next_cur_i,next_cur_j });
        }

        if(psb_locs_without_adjc.empty() && !adjc) {
            return cnt;
        }
        else if(psb_locs_without_adjc.empty() && adjc) {
            b[cur_i][cur_j] = 0;
            q.push(Frame(op_turn, cnt + 1, { {op_i,op_j},{op_i,op_j} }, b));
        }
        else {
            b[cur_i][cur_j] = 0;
            for(auto &[next_cur_i, next_cur_j] : psb_locs_without_adjc) {
                q.push(Frame(op_turn, cnt + 1, { {next_cur_i,next_cur_j} ,{op_i,op_j} }, b));
            }
        }
    }
}