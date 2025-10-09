//https://school.programmers.co.kr/learn/courses/30/lessons/1834
// [제한 조건]
// 1 <= n1, n2 <= 100
// 노드 번호는 각각 1부터 n1, n2까지의 값이 사용되며, 각 트리의 1번 노드가 루트이다.
// 입력되는 데이터는 항상 올바른 트리임이 보장된다.

#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <iostream>

using namespace std;

void MakeTree(vector<vector<int>> &t, vector<vector<int>>const &g, int n) {
    for(vector<int>const &node : g) {
        t[node[0]].push_back(node[1]);
        t[node[1]].push_back(node[0]);
    }
    queue<int> q;
    q.push(1);
    while(!q.empty()) {
        int top = q.front();
        q.pop();
        for(int c : t[top]) {
            t[c].erase(find(t[c].begin(), t[c].end(), top));
            q.push(c);
        }
    }
}

int GetAns(vector<vector<int>>const &t1, vector<vector<int>>const &t2) {
    struct Frame {
        int i1, i2;
        int ncj1 = 0, ncj2 = 0;
        Frame(int _i1, int _i2) :i1(_i1), i2(_i2) {}
    };

}

int solution(int n1, vector<vector<int>> g1, int n2, vector<vector<int>> g2) {
    vector<vector<int>> t1(n1 + 1, vector<int>()), t2(n2 + 1, vector<int>());
    MakeTree(t1, g1, n1);
    MakeTree(t2, g2, n2);

    return GetAns(t1, t2);
}