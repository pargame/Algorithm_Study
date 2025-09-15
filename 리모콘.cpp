//https://www.acmicpc.net/problem/1107

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<cmath>

using namespace std;

string GetCnds(vector<int> _psbs, string const &_tgt, int _nxt_idx){
    if(_tgt.size()<=_nxt_idx)
        return "";

    char nxt_chn=_tgt[_nxt_idx];
    sort(_psbs.begin(),_psbs.end(),[](int const&a, int const&b){
        return abs(a-nxt_chn+'0')<abs(b-nxt_chn+'0');
    });

    while(_psbs.size()>3)
        _psbs.pop_back();
    string ret;
    for(int _:_psbs)
        ret+=to_string(_);
    return ret;
}

int main(){
    string tgt; cin>>tgt;  //목적 채널 번호
    int lmt_n=0; cin>>lmt_n;  //제한 번호 개수
    vector<int> lmts;  //제한 번호 목록
    for(size_t _=0;_<lmt_n;++_){
        int __=0; cin>>__;
        lmts.push_back(__);
    }
    sort(lmts.begin(),lmts.end());

    vector<int> psbs{0,1,2,3,4,5,6,7,8,9};  //가능 번호 목록
    for(int const&n:lmts){
        psbs.erase(find(psbs.begin(),psbs.end(),n));
    }
    //======================================================
    int ans=abs(stoi(tgt)-100);
    vector<string>S
    for(ch fst_chn:GetCnds(psbs,tgt,1)){
        string out(1,fst_chn);
        while(!S.empty()){
            if(S.size()==tgt.size)
        }
    }

    cout<<ans;
    return 0;
}