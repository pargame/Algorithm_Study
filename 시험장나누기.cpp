//https://school.programmers.co.kr/learn/courses/30/lessons/81305
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <stack>
#include <queue>

using namespace std;

int solution(int k, vector<int> num, vector<vector<int>> link) {
    int node_cnt = num.size();
    vector<int> prnt(node_cnt, -1);
    vector<vector<int>> child(node_cnt);
    for(int i = 0; i < node_cnt; ++i) {
        for(int child_idx : link[i]) {
            if(child_idx == -1) continue;
            prnt[child_idx] = i;
            child[i].push_back(child_idx);
        }
    }
    int root_idx = find(prnt.begin(), prnt.end(), -1) - prnt.begin();

    vector<int> sum(num.begin(), num.end());
    stack<pair<int, int>> st;
    st.push({ root_idx, 0 });  //second: 방문해야 할 child의 자식 인덱스
    while(!st.empty()) {
        if(st.top().second < child[st.top().first].size()) {
            ++st.top().second;
            st.push({ child[st.top().first][st.top().second - 1], 0 });
            continue;
        }
        if(prnt[st.top().first] != -1)
            sum[prnt[st.top().first]] += sum[st.top().first];
        st.pop();
    }


    auto isPsb = [&](int const &M)mutable ->bool {
        int cur_k = 1;
        vector<int> local_sum = num;

        stack<pair<int, int>> st;
        st.push({ root_idx, 0 });
        while(!st.empty()) {
            auto &[node_idx, child_pos] = st.top();
            if(child_pos < (int)child[node_idx].size()) {
                int child_idx = child[node_idx][child_pos++];
                st.push({ child_idx, 0 });
                continue;
            }
            if(!child[node_idx].empty()) {
                vector<int> child_sums;
                for(int c : child[node_idx]) child_sums.push_back(local_sum[c]);
                sort(child_sums.begin(), child_sums.end());

                for(int child_sum : child_sums) {
                    if(local_sum[node_idx] + child_sum <= M) {
                        local_sum[node_idx] += child_sum;
                    }
                    else {
                        ++cur_k;
                        if(cur_k > k) return false;
                    }
                }
            }
            st.pop();
        }
        return cur_k <= k;
        };


    int L = *max_element(num.begin(), num.end());
    int R = accumulate(num.begin(), num.end(), 0);
    int ans = L;
    while(L <= R) {
        int M = (L + R) / 2;
        if(isPsb(M)) {
            ans = M;
            R = M - 1;
        }
        else {
            L = M + 1;
        }
    }
    return ans;
}