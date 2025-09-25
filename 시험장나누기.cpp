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
        sort(child[i].begin(), child[i].end());
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
        // cout << "==========M: " << M << "==========\n";
        if(sum[root_idx] <= M) return true;

        vector<int> local_sum = sum;
        int cur_k = 1;
        stack<pair<int, int>> st;
        st.push({ root_idx, child[root_idx].size() - 1 });
        while(!st.empty()) {
            // cout << "cur_idx: " << st.top().first << ", cur_sum: " << local_sum[st.top().first] << endl;

            //자식을 자를 필요가 없다면 바로 팝
            if(local_sum[st.top().first] <= M) {
                st.pop();
            }
            //내 second에 자식이 있고, 그 자식의 sum이 M보다 크면 푸시
            else if(st.top().second >= 0
                && local_sum[child[st.top().first][st.top().second--]] > M) {
                st.push({ child[st.top().first][st.top().second + 1]
                    , child[child[st.top().first][st.top().second + 1]].size() - 1 });
            }
            else {
                ++cur_k;
                if(cur_k > k)
                    return false;
                int max_child_sum = local_sum[child[st.top().first][0]];

                int p = st.top().first;
                while(p != -1) {
                    local_sum[p] -= local_sum[child[st.top().first].back()];
                    p = prnt[p];
                }
            }
        }

        return true;
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