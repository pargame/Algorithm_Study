//https://school.programmers.co.kr/learn/courses/30/lessons/62050

// 제한사항
// land는 N x N크기인 2차원 배열입니다.
// land의 최소 크기는 4 x 4, 최대 크기는 300 x 300입니다.
// land의 원소는 각 격자 칸의 높이를 나타냅니다.
// 격자 칸의 높이는 1 이상 10,000 이하인 자연수입니다.
// height는 1 이상 10,000 이하인 자연수입니다.

#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int solution(vector<vector<int>> land, int height) {
    int N = land.size();
    //(i,j) 좌표가 속한 그룹
    vector<vector<int>> group(N, vector<int>(N, -1)); group[0][0] = 0;
    //(g1,g2) 그룹 사이의 최소 사다리 비용
    vector<vector<int>> min_group_diff(N, vector<int>(N, 6000000));
    //총 그룹 수
    int grout_cnt = 1;

    queue<pair<int, int>> q;
    q.push({ 0,0 });
    while(!q.empty()) {
        pair<int, int> f = q.front();
        q.pop();
        int ci = f.first, cj = f.second;
        for(auto &[di, dj] : vector<pair<int, int>>{ { 1,0 }, { 0,1 }, { -1,0 }, { 0,-1 } }) {
            int ni = ci + di, nj = cj + dj;
            if(ni < 0 || nj < 0 || N <= ni || N <= nj) continue;
            int diff = abs(land[ci][cj] - land[ni][nj]);

        }
    }




    int answer = 0;
    return answer;
}