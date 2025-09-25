//https://school.programmers.co.kr/learn/courses/30/lessons/81305
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

int solution(int k, vector<int> num, vector<vector<int>> link) {
    int tree_size = num.size();
    vector<vector<int>> adjc(tree_size, vector<int>());
    for(int i = 0; i < tree_size; ++i) {
        for(int child_idx : link[i]) {
            if(child_idx == -1) continue;
            adjc[i].push_back(child_idx);
            adjc[child_idx].push_back(i);
        }
    }

    int start_idx = 0;
    for(int i = 0; i < tree_size; ++i) {
        if(link[i][0] == -1 && link[i][1] == -1) {
            start_idx = i;
            break;
        }
    }

    auto isPsb = [&](int const &M)->bool {
        struct Frame {
            int idx;
            int vst_state;

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

}