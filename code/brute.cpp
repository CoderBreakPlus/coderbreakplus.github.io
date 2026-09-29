#include<bits/stdc++.h>
using namespace std;
const int N=5050;
int n,ans=1e9+10;
char s[2][N];//s[1]就是题目说的t
struct node{int v,t;};
//t=0是s[0]，t=1是s[1]
//最后剩下的就和n位置匹配
vector<int> pos[2];
void work(int l,int r)
{
    for(int c=l;c<=r;c+=2)
    {
        queue<node> q;
        int now=0,p0=0,p1=0; node t;
        for(int i=1;i<=abs(c);i++) q.push(node{0,(c>0)});
        while(p0<pos[0].size()||p1<pos[1].size())
        {
            if(p0<pos[0].size()&&((!(p1<pos[1].size()))||pos[0][p0]<pos[1][p1])) t=node{pos[0][p0],0},p0++;
            else t=node{pos[1][p1],1},p1++;
            if(q.size()&&q.front().t!=t.t) now+=(t.v-q.front().v),q.pop();
            else q.push(t);
        }
        while(q.size()) now+=(n-q.front().v),q.pop();
        ans=min(ans,now);
    }
}
int main()
{
    #ifdef LOCAL
        assert(freopen("test.in","r",stdin));
        assert(freopen("test.ans","w",stdout));
    #endif
    scanf("%d",&n);
    scanf("%s%s",s[0]+1,s[1]+1);
    for(int t=0;t<2;t++)
        for(int i=2;s[t][i];i++)
            if(s[t][i]!=s[t][i-1])
                pos[t].push_back(i-1);
    if(s[0][1]==s[1][1]) work(-2*(n/2),2*(n/2));//左边的个数只能枚举偶数
    else work(-2*(n/2)-1,2*(n/2)+1);//左边的个数只能枚举奇数
    printf("%d\n",ans);
    return 0;
}
