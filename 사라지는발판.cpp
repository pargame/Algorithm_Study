#include <vector>
#include <stack>
#include <utility>
#include <algorithm>

using namespace std;

class Solver{
    struct Loc{
        int x;
        int y;
        Loc(int _x, int _y):x(_x),y(_y){}
    };
    struct Frame{
        int nd=0;
        Loc loc;
        vector<int> wc;
        vector<int> lc;
        Frame(Loc _loc):loc(_loc){}
    };

    vector<stack<Frame>> st;
    vector<vector<int>> board;
    vector<pair<int,int>> dir{{1,0},{0,1},{-1,0},{0,-1}};

    stack<Frame>& GetS(){
        if(st[0].size()==st[1].size()){
            return st[0];
        }
        else{
            return st[1];
        }
    }

    Frame& GetP(){
        return GetS().top();
    }

    bool Update(){
        //[..OPP-P-OP] 이 상태라고 해보면 P차례임(아직 안 감. 갈 곳이 더이상 없음)
        //1. P가 이기거나 진 모두의 경우가 없다면, P는 지금 갈 곳이 하나도 없이 진 것임.
        //      (따라서 P는 현재 걸음수가 유일한 진 값이 됨)
        //      =반대로 OPP는 wc에 그 값을 추가하면 됨
        //2. P가 이긴 경우만 있다면, P는 이긴 값중 최대값으로 확정(OP는 최대한 많은 걸음을 택할 것이기 때문)
        //      =OPP는 P의 의해 무조건 지게 될 것이고 lc에 이 값을 추가
        //3. 그 외, P가 지는 경우가 하나라도 있다면 OP에 의해서 무조건 지게 됨.
        //      (따라서 lc중 상대방에 의해서 최소가 택해질 것.)
        //      =OPP는 이겼으므로 그 값을 wc에 추가


        //일단 OPP의 이긴 유무와 받을 값만 구함
        Frame& p=GetP();
        bool OPPwin=false;
        int v=0;
        if(p.wc.empty() && p.lc.empty()){
           OPPwin=true;
           v=st[0].size()+st[1].size()-2;
        }
        else if(p.lc.empty()){
            v=*max_element(p.wc.begin(),p.wc.end());    
        }
        else{
            OPPwin=true;
            v=*min_element(p.lc.begin(),p.lc.end());
        }

        //OP제거
        if(st[0].size()==st[1].size()){
            st[1].pop();
        }
        else{
            st[0].pop();
        }

        //Break Point 검사
        if(st[0].size()+st[1].size()==1){
            ans=v;
            return true;
        }
        else{
            //OP제거 이후의 OPP는 이 때의 차례, 즉 P가 됨
                Frame& opp=GetP();
                if(OPPwin){
                    opp.wc.push_back(v);
                }
                else{
                    opp.lc.push_back(v);
                }
                return false;
        }
    }

    void Backtrack(){
        //Update에서 이미 팝이 되었음. 따라서 발판은 현재의 P에서 채워줘야 함
        Frame& p=GetP();
        board[p.loc.x][p.loc.y]=1;
    }

    void Proceed(){
        Frame& p=GetP();
        if(board[p.loc.x][p.loc.y]==0){
            p.nd=4;
            return;
        }

        int nx=p.loc.x+dir[p.nd].first;
        int ny=p.loc.y+dir[p.nd].second;
        if(nx<0||ny<0||board.size()<=nx||board[0].size()<=ny||board[nx][ny]==0){
            ++p.nd;
            return;
        }
        
        board[p.loc.x][p.loc.y]=0;
        stack<Frame> &s=GetS();
        s.push(Frame(Loc(nx,ny)));
        GetP().nd=0;
    }

    void GetAns(){
        while(true){
            //P의 차례. P는 안가본 방향 중 갈 수 있는 방향을 탐색한다.
            //    - 갈 방향이 없다면
            //        - 가장 첫 A의 스택이라면 모든 경우를 봤으므로, 해당 프레임 기반의 ans를 리턴하고 종료 
            //        - 그게 아니면 (일반적) Update->Backtrack
            //    - 갈 방향이 있다면 Proceed

            Frame& p=GetP();
            if(p.nd==4){
                if(Update()){
                    break;
                }
                Backtrack();
            }
            else{
                Proceed();
            }
        }
    }

public:
    int ans;
    
    Solver(vector<vector<int>> _board, vector<int> _aloc, vector<int> _bloc):st(2), board(_board){
        st[0].push(Frame(Loc(_aloc[0],_aloc[1])));
        st[1].push(Frame(Loc(_bloc[0],_bloc[1])));

        GetAns();
    }
};

int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {
    Solver sol(board,aloc,bloc);
    return sol.ans;
}