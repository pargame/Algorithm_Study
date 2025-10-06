//https://school.programmers.co.kr/learn/courses/30/lessons/1834
// [제한 조건]
// 1 <= n1, n2 <= 100
// 노드 번호는 각각 1부터 n1, n2까지의 값이 사용되며, 각 트리의 1번 노드가 루트이다.
// 입력되는 데이터는 항상 올바른 트리임이 보장된다.

#include <vector>
#include <queue>
#include <algorithm>
#include <stack>

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

void SetDP(int i1, int i2, vector<vector<int>> &dp
    , vector<vector<int>>const &t1, vector<vector<int>>const &t2) {
    if(t1[i1].size() == 0 || t2[i2].size() == 0) {
        dp[i1][i2] = 1;
        return;
    }

    vector<vector<int>> sub_dp(t1[i1].size(), vector<int>(t2[i2].size()));
    for(int c1 = 0; c1 < t1[i1].size(); ++c1) {
        for(int c2 = 0; c2 < t2[i2].size(); ++c2) {
            sub_dp[c1][c2] = dp[t1[i1][c1]][t2[i2][c2]];
        }
    }



}

int GetAns(vector<vector<int>>const &t1, vector<vector<int>>const &t2) {
    int ans = 0;

    stack<pair<int, int>> st;
    queue<pair<int, int>> q;
    q.push({ 1,1 });
    while(!q.empty()) {
        st.push(q.front());
        q.pop();
        for(int c1 : t1[st.top().first]) {
            for(int c2 : t2[st.top().second]) {
                q.push({ c1,c2 });
            }
        }
    }

    vector<vector<int>> dp(t1.size() + 1, vector<int>(t2.size() + 1));
    while(!st.empty()) {
        int i1 = st.top().first, i2 = st.top().second;
        st.pop();
        SetDP(i1, i2, dp, t1, t2);
    }


    return ans;
}

int solution(int n1, vector<vector<int>> g1, int n2, vector<vector<int>> g2) {
    vector<vector<int>> t1(n1 + 1, vector<int>()), t2(n2 + 1, vector<int>());
    MakeTree(t1, g1, n1);
    MakeTree(t2, g2, n2);

    return GetAns(t1, t2);
}