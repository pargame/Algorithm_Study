//https://school.programmers.co.kr/learn/courses/15008/lessons/121685
// 제한사항
// 1 ≤ queries의 길이(쿼리의 개수) ≤ 5
// queries의 원소는 [n, p] 형태입니다.
// 1 ≤ n ≤ 16
// 1 ≤ p ≤ 4n-1
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Frame {
    int cur = 0;  //RR:0/Rr·rR:1/rr:2
    int level = 0;
    int n = 0;
};

vector<int> lv_cnt(17);

vector<string> solution(vector<vector<int>> queries) {
    sort(queries.begin(), queries.end(), [](auto const &a, auto const &b) {
        if(a[0] == b[0]) return a[1] < b[1];
        return a[0] < b[0];
        });
    queue<Frame>q;
    q.push(Frame());
    q.front().cur = 1;
    q.front().level = 1;
    q.front().n = 1;
    lv_cnt[1] = 1;
    int cnt = 0;
    vector<string> ans;
    while(cnt < queries.size()) {
        Frame top = q.front();

        if(top.level == queries[cnt][0] && top.n == queries[cnt][1]) {
            if(top.cur == 0) {
                ans.push_back("RR");
            }
            else if(top.cur == 1) {
                ans.push_back("Rr");
            }
            else {
                ans.push_back("rr");
            }
            ++cnt;
            continue;
        }

        q.pop();


        if(top.cur == 0) {
            for(int i : {0, 0, 0, 0}) {
                Frame next;
                next.cur = 0;
                next.level = top.level + 1;
                next.n = ++lv_cnt[next.level];
                q.push(next);
            }
        }
        else if(top.cur == 1) {
            Frame next1, next2, next3, next4;
            next1.cur = 0, next1.level = top.level + 1, next1.n = ++lv_cnt[next1.level];
            next2.cur = 1, next2.level = top.level + 1, next2.n = ++lv_cnt[next2.level];
            next3.cur = 1, next3.level = top.level + 1, next3.n = ++lv_cnt[next3.level];
            next4.cur = 2, next4.level = top.level + 1, next4.n = ++lv_cnt[next4.level];
            q.push(next1);
            q.push(next2);
            q.push(next3);
            q.push(next4);
        }
        else {
            for(int i : {0, 0, 0, 0}) {
                Frame next;
                next.cur = 2;
                next.level = top.level + 1;
                next.n = ++lv_cnt[next.level];
                q.push(next);
            }
        }
    }
    return ans;
}