//https://school.programmers.co.kr/learn/courses/30/lessons/81305
#include <vector>
#include<algorithm>
#include<numeric>
#include<utility>
#include<stack>

using namespace std;

vector<int> num;
vector<vector<int>> links;
int k, root_idx;

bool isPsb(int const& v) {
    struct Frame {
        int cur_idx, total = 0;
        vector<int> child_idxs;
        Frame(int _ci, vector<int> _cis) :cur_idx(_ci), child_idxs(_cis), total(num[cur_idx]) {}
    };

    int cur_k = 1;
    stack<Frame> st; st.push(Frame(root_idx, links[root_idx]));
    while(true) {
        int left_idx = st.top().child_idxs[0], right_idx = st.top().child_idxs[1];
        if(left_idx != -1) {
            st.top().child_idxs[0] = -1;
            st.push(Frame(left_idx, links[left_idx])); continue;
        }
        if(right_idx != -1) {
            st.top().child_idxs[1] = -1;
            st.push(Frame(right_idx, links[right_idx])); continue;
        }

        Frame child = st.top(); st.pop();
        if(st.empty()) return true;
        if(st.top().total + child.total <= v) st.top().total += child.total;
        else if(cur_k < k) ++cur_k;
        else return false;
    }
}

int solution(int k, vector<int> num, vector<vector<int>> links) {
    ::num = move(num), ::links = move(links), ::k = k;
    vector<bool> vst(::num.size());
    for(auto link : ::links) {
        if(link[0] != -1)vst[link[0]] = true;
        if(link[1] != -1)vst[link[1]] = true;
    }
    ::root_idx = find(vst.begin(), vst.end(), false) - vst.begin();

    int L = *max_element(::num.begin(), ::num.end());
    int R = accumulate(::num.begin(), ::num.end(), 0);
    int ans = R;
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