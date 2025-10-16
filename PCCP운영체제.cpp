//https://school.programmers.co.kr/learn/courses/15008/lessons/121686
// 제한사항
// 1 ≤ program의 길이 ≤ 100,000
// program[i]은 i+1번 프로그램의 정보를 의미하며, [a, b, c]의 형태로 주어집니다.
// a는 프로그램의 점수를 의미하며, 1 ≤ a ≤ 10 을 만족합니다.
// b는 프로그램이 호출된 시각을 의미하며, 0 ≤ b ≤ 10,000,000을 만족합니다.
// c는 프로그램의 실행 시간을 의미하며, 1 ≤ c ≤ 1,000을 만족합니다.
// a, b쌍이 중복되는 프로그램은 입력으로 주어지지 않습니다. 즉, 호출된 시각이 같으면서 점수도 같은 프로그램은 없습니다.
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<long long> solution(vector<vector<int>> program) {
    vector<long long> answer(11);
    struct Cmp {
        bool operator()(vector<int>const &a, vector<int>const &b) {
            if(a[1] == b[1]) return a[0] > b[0];
            return a[1] > b[1];
        }
    };
    priority_queue<vector<int>, vector<vector<int>>, Cmp> pq;
    for(vector<int> p : program) {
        pq.push(p);
    }

    int cur_t = 0;
    while(true) {
        struct CmpS {
            bool operator()(vector<int>const &a, vector<int>const &b) {
                return a[0] > b[0];
            }
        };
        priority_queue<vector<int>, vector<vector<int>>, CmpS> pqs;





        if(pq.empty()) break;
    }



    return answer;
}