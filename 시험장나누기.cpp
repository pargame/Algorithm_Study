#include <string>
#include <vector>
#include<numeric>
#include<stack>
#include<algorithm>

using namespace std;

struct Frame {
    int cur_total;
    bool isRoot = false;
    vector<int>const& childs_idx;
    Frame(int _cur_total, vector<int>const& _childs_idx) :cur_total(_cur_total), childs_idx(_childs_idx) {};
};

int findRootIdx(vector<int>const& num, vector<vector<int>>const& links) {
    vector<bool> check(num.size());
    for(vector<int>const& link : links) {
        for(int c : link) {
            if(c != -1)
                check[c] = true;
        }
    }
    return find(check.begin(), check.end(), false) - check.begin();
}

bool isPsb(vector<int>const& num, vector<vector<int>>const& links, int const& root_idx, int const& k, int const& M) {
    vector<bool> vst(num.size()); //노드 방문 여부
    stack<Frame> st; //DFS용 스택
    int cur_k = 1; //현재 그룹 수

    //DFS 스택 초기화
    st.push(Frame(num[root_idx], links[root_idx])); vst[root_idx] = true;
    st.top().isRoot = true;
    //반복적 DFS 실행
    while(!st.empty()) {
        //탑 저장
        Frame top = st.top();
        //left 자식부터 스택에 푸시 컨티뉴
        int left_idx = top.childs_idx[0];
        if(left_idx != -1 && !vst[left_idx]) {
            if(num[left_idx] > M) return false;
            st.push(Frame(num[left_idx], links[left_idx]));
            vst[left_idx] = true;
            continue;
        }
        int right_idx = top.childs_idx[1];
        if(right_idx != -1 && !vst[right_idx]) {
            if(num[right_idx] > M) return false;
            st.push(Frame(num[right_idx], links[right_idx]));
            vst[right_idx] = true;
            continue;
        }
        //더 이상 자식 방문 불가능 시점
        st.pop();
        //부모가 있을 때 부모에게 전달
        if(!top.isRoot) {
            //전달값과 부모값의 합이 M이하일 때는 그냥 추가 저장
            if(st.top().cur_total + top.cur_total <= M) {
                st.top().cur_total += top.cur_total;
            }
            else if(cur_k < k) { //그룹을 나누어 해결
                ++cur_k;  //현재 그룹 수 증가
            }
            else //그룹을 더 늘릴 수 없으므로 불가능
                return false;
        }
    }
    //전부 팝되어 가능한 것이므로
    return true;
}

int solution(int k, vector<int> num, vector<vector<int>> links) {
    int root_idx = findRootIdx(num, links);

    int L = *max_element(num.begin(), num.end())
        , R = accumulate(num.begin(), num.end(), 0);
    int ans = R;
    while(L <= R) {
        int M = (L + R) / 2;
        if(isPsb(num, links, root_idx, k, M)) {
            ans = M;
            R = M - 1;
        }
        else
            L = M + 1;
    }
    return ans;
}

