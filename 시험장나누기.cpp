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
        int const& cur_idx;
        vector<int> const& child_idxs;
        Frame(int const& _ci, vector<int>const& _cis) :cur_idx(_ci), child_idxs(_cis) {}
    };

    stack<Frame> st; st.push(Frame(root_idx, links[root_idx]));
    while(!st.empty()) {

    }

}

int solution(int k, vector<int> num, vector<vector<int>> links) {
    ::num = move(num), ::links = move(links), ::k = k;
    vector<bool> vst(num.size());
    for(auto link : links) { vst[link[0]] = true, vst[link[1]] = true; }
    ::root_idx = find(vst.begin(), vst.end(), false) - vst.begin();

    int L = *max_element(num.begin(), num.end());
    int R = accumulate(num.begin(), num.end(), 0);
    int ans = R;
    while(L < R) {
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