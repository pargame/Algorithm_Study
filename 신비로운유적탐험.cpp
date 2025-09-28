//https://school.programmers.co.kr/learn/courses/30/lessons/1834
// 제한사항
// 1 <= n1, n2 <= 100
// 노드 번호는 각각 1부터 n1, n2까지의 값이 사용되며, 각 트리의 1번 노드가 루트이다.
// 입력되는 데이터는 항상 올바른 트리임이 보장된다.

#include <vector>

using namespace std;

int solution(int n1, vector<vector<int>> g1, int n2, vector<vector<int>> g2) {
    vector<vector<int>> t1(n1 + 1);
    vector<vector<int>> t2(n2 + 1);
    for(int i = 0; i < g1.size(); ++i) {
        t1[g1[i][0]].push_back(g1[i][1]);
        t1[g1[i][1]].push_back(g1[i][0]);
    }
    for(int i = 0; i < g2.size(); ++i) {
        t2[g2[i][0]].push_back(g2[i][1]);
        t2[g2[i][1]].push_back(g2[i][0]);
    }



}