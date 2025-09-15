//https://www.acmicpc.net/problem/1107

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

vector<int> GetCands(vector<int> possibles,int const n){
    sort(possibles.begin(),possibles.end(),[]())
}

int main(){
    string dest; cin>>dest;  //목적 채널 번호
    int limit_cnt=0; cin>>limit_cnt;  //제한 번호 개수
    vector<int> limits;  //제한 번호 목록
    for(size_t i=0;i<limit_cnt;++i){
        int n=0; cin>>n;
        limits.push_back(n);
    }
    sort(limits.begin(),limits.end());

    vector<int> possibles{0,1,2,3,4,5,6,7,8,9};  //가능 번호 목록
    for(int const&n:limits){
        possibles.erase(find(possibles.begin(),possibles.end(),n));
    }

    vector<int> cands=GetCands(possibles, stoi(dest[0]));



    return 0;
}