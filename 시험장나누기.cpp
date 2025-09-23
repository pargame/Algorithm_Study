//https://school.programmers.co.kr/learn/courses/30/lessons/81305
#include <vector>
#include<algorithm>
#include<numeric>
#include<queue>
#include<stack>
#include<iostream>
#include<format>

using namespace std;

vector<int> nums;
vector<vector<int>> links;
int root_idx;
int k;

int GetTotal(int idx, vector<vector<int>> const &links) {
    if(idx == -1) return 0;
    queue<int> q; q.push(idx);
    int total = 0;
    while(!q.empty()) {
        total += ::nums[q.front()];
        if(links[q.front()][0] != -1) q.push(links[q.front()][0]);
        if(links[q.front()][1] != -1) q.push(links[q.front()][1]);
        q.pop();
    }
    return total;
}

bool isPsb(int M) {
    vector<vector<int>> links = ::links;
    queue<int> q;
    stack<int> st;
    //BFS로 stack에 추가->리프노드부터 팝 될 예정
    q.push(root_idx);
    while(!q.empty()) {
        st.push(q.front());
        if(links[q.front()][0] != -1) q.push(links[q.front()][0]);
        if(links[q.front()][1] != -1) q.push(links[q.front()][1]);
        q.pop();
    }
    int cur_k = 1;
    while(!st.empty()) {
        int left_total = GetTotal(links[st.top()][0], links);
        int right_total = GetTotal(links[st.top()][1], links);

        //불가능 할 때
        if(::nums[st.top()] + left_total + right_total > M) {
            //그룹 수가 오버하면 바로 false 리턴
            if(cur_k == k) return false;
            //그룹 수 증가
            ++cur_k;
            //자식 중 서브트리 합이 큰 자식과 연결을 끊음
            left_total < right_total ? links[st.top()][1] = -1 : links[st.top()][0] = -1;
        }
        st.pop();
    }
    return true;
}

int solution(int k, vector<int> nums, vector<vector<int>> links) {
    ::nums = move(nums);
    ::links = move(links);
    vector<bool>vst(::nums.size());
    for(int i = 0; i < vst.size(); ++i) {
        if(::links[i][0] != -1) vst[::links[i][0]] = true;
        if(::links[i][1] != -1) vst[::links[i][1]] = true;
    }
    ::root_idx = find(vst.begin(), vst.end(), false) - vst.begin();
    ::k = k;

    int L = *max_element(::nums.begin(), ::nums.end());
    int R = accumulate(::nums.begin(), ::nums.end(), 0);
    int ans = R;
    while(L <= R) {
        int M = (L + R) / 2;
        if(isPsb(M)) {
            ans = M;
            R = M - 1;
        }
        else L = M + 1;
    }

    return ans;
}

int main() {
    // 테스트 1
    {
        int k = 3;
        vector<int> nums = { 12, 30, 1, 8, 8, 6, 20, 7, 5, 10, 4, 1 };
        vector<vector<int>> links = { {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {8, 5}, {2, 10}, {3, 0}, {6, 1}, {11, -1}, {7, 4}, {-1, -1}, {-1, -1} };
        cout << "Test 1: \n" << solution(k, nums, links) << " (expected: 40)" << endl;
    }
    // 테스트 2
    {
        int k = 1;
        vector<int> nums = { 6, 9, 7, 5 };
        vector<vector<int>> links = { {-1, -1}, {-1, -1}, {-1, 0}, {2, 1} };
        cout << "Test 2: \n" << solution(k, nums, links) << " (expected: 27)" << endl;
    }
    // 테스트 3
    {
        int k = 2;
        vector<int> nums = { 6, 9, 7, 5 };
        vector<vector<int>> links = { {-1, -1}, {-1, -1}, {-1, 0}, {2, 1} };
        cout << "Test 3: \n" << solution(k, nums, links) << " (expected: 14)" << endl;
    }
    // 테스트 4
    {
        int k = 4;
        vector<int> nums = { 6, 9, 7, 5 };
        vector<vector<int>> links = { {-1, -1}, {-1, -1}, {-1, 0}, {2, 1} };
        cout << "Test 4: \n" << solution(k, nums, links) << " (expected: 9)" << endl;
    }
    return 0;
}