//https://school.programmers.co.kr/learn/courses/30/lessons/81305
#include <vector>
#include<utility>
#include<stack>
#include<algorithm>

using namespace std;

int k, root_idx;
vector<int> sums;
vector<vector<int>> links;
vector<int> prnts;

int GetRookIdx_Prnts(vector<int>const &nums) {
    prnts.assign(nums.size(), -1);
    for(int i = 0; i < nums.size(); ++i) {
        if(links[i][0] != -1) prnts[links[i][0]] = i;
        if(links[i][1] != -1) prnts[links[i][1]] = i;
    }
    root_idx = find(prnts.begin(), prnts.end(), -1) - prnts.begin();
}

void MakeSumTree(vector<int>const &nums) {
    sums.assign(nums.begin(), nums.end());
    stack<int> st; st.push(root_idx);
}

int solution(int k, vector<int> nums, vector<vector<int>> links) {
    ::links = links;
    SetRootIdx_Prnts(nums);
    MakeSumTree(nums);

}