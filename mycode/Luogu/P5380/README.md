```cpp
#include<bits/stdc++.h>
using namespace std;
#define captain 0
#define guard 1
#define elephant 2
#define horse 3
#define car 4
#define duck 5
#define soldier 6 // 棋子的编号
#define red 0
#define blue 1 // 执棋方的编号
typedef pair<int,int> P; // 执棋方；棋子
P chess[10][9]; // 棋盘
#define mkp(a,b) make_pair(a,b)
int redcapx,redcapy,bluecapx,bluecapy; // 王的位置
inline void init(){
    redcapx=0,redcapy=4,bluecapx=9,bluecapy=4;
    chess[0][0]=mkp(red,car),chess[0][1]=mkp(red,horse),chess[0][2]=mkp(red,elephant);
    chess[0][3]=mkp(red,guard),chess[0][4]=mkp(red,captain),chess[0][5]=mkp(red,guard);
    chess[0][6]=mkp(red,elephant),chess[0][7]=mkp(red,horse),chess[0][8]=mkp(red,car);
    for(int i=0;i<=8;i++) chess[1][i]=mkp(-1,-1);
    chess[2][0]=chess[2][8]=mkp(red,duck);
    for(int i=1;i<8;i++) chess[2][i]=mkp(-1,-1);
    for(int i=0;i<=8;i++){
        if(i%2==0) chess[3][i]=mkp(red,soldier);
        else chess[3][i]=mkp(-1,-1);
    }
    for(int i=4;i<=5;i++)
        for(int j=0;j<=8;j++) chess[i][j]=mkp(-1,-1);
    for(int i=0;i<=8;i++){
        if(i%2==0) chess[6][i]=mkp(blue,soldier);
        else chess[6][i]=mkp(-1,-1);
    }
    chess[7][0]=chess[7][8]=mkp(blue,duck);
    for(int i=1;i<8;i++) chess[7][i]=mkp(-1,-1);
    for(int i=0;i<=8;i++) chess[8][i]=mkp(-1,-1);
    chess[9][0]=mkp(blue,car),chess[9][1]=mkp(blue,horse),chess[9][2]=mkp(blue,elephant);
    chess[9][3]=mkp(blue,guard),chess[9][4]=mkp(blue,captain),chess[9][5]=mkp(blue,guard);
    chess[9][6]=mkp(blue,elephant),chess[9][7]=mkp(blue,horse),chess[9][8]=mkp(blue,car);
} // 初始棋盘
const int dx[8]={1,0,0,-1,1,1,-1,-1};
const int dy[8]={0,1,-1,0,1,-1,1,-1}; // 兵的走法
const int carx[4]={1,0,0,-1},cary[4]={0,1,-1,0}; // 车/王的走法
const int gx[4]={1,1,-1,-1},gy[4]={1,-1,1,-1}; // 士的走法
bool inchess(int s1,int t1){
    return (s1>=0)&&(s1<=9)&&(t1>=0)&&(t1<=8);
}
bool moved(int man,int s1,int t1,int s2,int t2){ // 判断是不是能走
    if(man==soldier){ // 兵
        for(int i=0;i<8;i++){
            int tmpx=s1+dx[i],tmpy=t1+dy[i];
            if(tmpx==s2 && tmpy==t2) return true;
        }
    }else if(man==car){ // 车
        for(int i=0;i<4;i++){
            int tmpx=s1,tmpy=t1;
            while(1){
                tmpx+=carx[i],tmpy+=cary[i];
                if(!inchess(tmpx,tmpy)) break;
                if(tmpx==s2 && tmpy==t2) return true;
                if(chess[tmpx][tmpy].first!=-1) break;
            }
        }
    }else if(man==horse){ // 马 (hard)
        for(int i=-1;i<=1;i++)
            for(int j=-1;j<=1;j++){
                if(i==0 || j==0) continue;
                if(inchess(s1+2*i,t1+j) && chess[s1+i][t1].first==-1){
                    if(s1+2*i==s2 && t1+j==t2) return true;
                }
                if(inchess(s1+i,t1+2*j) && chess[s1][t1+j].first==-1){
                    if(s1+i==s2 && t1+2*j==t2) return true;
                }
            }
    }else if(man==elephant){ // 象 (hard)
        for(int i=-1;i<=1;i++)
            for(int j=-1;j<=1;j++){
                if(i==0 || j==0) continue;
                if(inchess(s1+2*i,t1+2*j) && chess[s1+i][t1+j].first==-1){
                    if(s1+2*i==s2 && t1+2*j==t2) return true;
                }
            }
    }else if(man==duck){ // 鸭 (hard+)
        for(int i=-1;i<=1;i++)
            for(int j=-1;j<=1;j++){
                if(i==0 || j==0) continue;
                if(inchess(s1+3*i,t1+2*j) && chess[s1+i][t1].first==-1 && chess[s1+2*i][t1+j].first==-1){
                    if(s1+3*i==s2 && t1+2*j==t2) return true;
                }
                if(inchess(s1+2*i,t1+3*j) && chess[s1][t1+j].first==-1 && chess[s1+i][t1+2*j].first==-1){
                    if(s1+2*i==s2 && t1+3*j==t2) return true;
                }
            }
    }else if(man==captain){ // 王 
        for(int i=0;i<4;i++){
            int tmpx=s1+carx[i],tmpy=t1+cary[i];
            if(tmpx==s2 && tmpy==t2) return true;
        }
    }else{ // 士
        for(int i=0;i<4;i++){
            int tmpx=s1+gx[i],tmpy=t1+gy[i];
            if(tmpx==s2 && tmpy==t2) return true;
        }
    }
    return false;
}
int ready_kill(){ // 判断将军
    for(int i=0;i<=9;i++)
        for(int j=0;j<=8;j++){
            if(chess[i][j].first==red)
            if(moved(chess[i][j].second,i,j,bluecapx,bluecapy)) return 1;
        }
    for(int i=0;i<=9;i++)
        for(int j=0;j<=8;j++){
            if(chess[i][j].first==blue)
            if(moved(chess[i][j].second,i,j,redcapx,redcapy)) return 1;
        }
    return 0;
}
struct Return{
    P mover,tomove;
    bool ready_kill,killed;
    Return(){
        mover=tomove=mkp(-1,-1);
        ready_kill=killed=false;
    }
};
bool end1; // 结束
Return moveit(int player,int s1,int t1,int s2,int t2){ // 移动，不合法返回 -1
    Return ans;
    if(chess[s1][t1].first!=player) return ans;
    if(chess[s2][t2].first==player) return ans;
    if(!moved(chess[s1][t1].second,s1,t1,s2,t2)) return ans;
    ans.mover=chess[s1][t1];
    if(chess[s2][t2].first^1==player){ // 吃了这个子
        ans.tomove=chess[s2][t2];
        if(chess[s2][t2].second==captain){
            ans.killed=true;
            return ans;
        }
    }
    chess[s2][t2]=chess[s1][t1],chess[s1][t1]=mkp(-1,-1);
    if(chess[s2][t2].second==captain){
        if(player==red) redcapx=s2,redcapy=t2;
        else bluecapx=s2,bluecapy=t2;
    }
    if(ready_kill()) ans.ready_kill=true; // 将军
    return ans;
}
int q,s1,t1,s2,t2;
string str[9]={"captain","guard","elephant","horse","car","duck","soldier"};
inline void print(P a){
    if(a.first==red) cout<<"red ";
    else cout<<"blue ";
    cout<<str[a.second]<<";";
}
int main(){
    init();
    cin>>q;
    int player=red;
    for(int i=1;i<=q;i++){
        cin>>s1>>t1>>s2>>t2;
        Return tmp=moveit(player,s1,t1,s2,t2);
        if(tmp.mover==mkp(-1,-1) || end1){
            cout<<"Invalid command\n";
            continue;
        }
        print(tmp.mover);
        if(tmp.tomove==mkp(-1,-1)) cout<<"NA;";
        else print(tmp.tomove);
        if(tmp.ready_kill) cout<<"yes;"; else cout<<"no;";
        if(tmp.killed){
            cout<<"yes"; end1=true;
        }else cout<<"no";
        cout<<endl; player^=1;
    }
    return 0;
}
```

[返回上一页](https://coderbreakplus.github.io/website/mycode/Luogu)
