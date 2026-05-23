#include <bits/stdc++.h>
using namespace std;
#define SIZIO (1<<23)
#define gc() (rp1==rp2&&(rp2=(rp1=buf)+fread(buf,1,SIZIO,stdin))==rp1?EOF:*rp1++)
#define pc(c) ((wrp==wbuf+SIZIO)&&(fwrite(wbuf,1,SIZIO,stdout),wrp=wbuf),(*wrp++)=c)
char buf[SIZIO+1],*rp1,*rp2;
char wbuf[SIZIO+1],*wrp=wbuf;
#define F first
#define S second
#define ls (u<<1)
#define rs (u<<1|1)
#define mid (l+r>>1)
inline int read(){
    int d=0,f=0;char ch=gc();
    while (!isdigit(ch)) f|=(ch=='-'),ch=gc();
    while (isdigit(ch)) d=(d<<1)+(d<<3)+ch-'0',ch=gc();
    return f?-d:d;
}
inline void write(int n){
    if (n<0) n=-n,pc('-');
    int stk[35],tp=0;
    do{stk[++tp]=n%10,n/=10;}while (n);
    while (tp) pc(stk[tp--]+'0');
} 
const int N=100005,M=3200,mod=1e9+7;
bool st[M];
int p[N+M],pcnt; 
unordered_map <int,int> mp;
inline void init(int n){
    st[1]=1;
    for (int i=2;i<=n;i++){
        if (!st[i]) p[++pcnt]=i;
        for (int j=1;p[j]*i<=n;j++) {
            st[i*p[j]]=1;
            if (i%p[j]==0) break;
        }
    }
}

int n,q,h[N],e[N<<1],ne[N<<1],idx=1,a[N],fa[N],sz[N],dfn[N],tim,top[N],son[N],dep[N],ans[N];
inline void add(int a,int b) {e[idx]=b,ne[idx]=h[a];h[a]=idx++;}
void dfs1(int u){
    sz[u]=1,son[u]=0;
    for (int i=h[u];i;i=ne[i]){
        int v=e[i];
        if (v^fa[u]){
            fa[v]=u,dep[v]=dep[u]+1;
            dfs1(v),sz[u]+=sz[v];
            if (sz[v]>sz[son[u]]) son[u]=v;
        }
    }
}
void dfs2(int u,int tp){
    dfn[u]=++tim,top[u]=tp;
    if (son[u]) dfs2(son[u],tp);
    for (int i=h[u];i;i=ne[i]){
        int v=e[i];
        if (v^fa[u]&&v^son[u]) dfs2(v,v);
    }
}
inline int LCA(int x,int y){
    while (top[x]!=top[y]) {
        if (dep[top[x]]<dep[top[y]]) swap(x,y);
        x=fa[top[x]];
    }
    return dep[x]<dep[y]?x:y;
}
struct BIT{
    int t[N];
    inline void add(int x,int v){
        for (int i=x;i<=n+1;i+=i&-i) t[i]+=v;
    }
    inline int sum(int x){
        int res=0;
        for (int i=x;i;i-=i&-i) res+=t[i];
        return res;
    }
    inline void add(int l,int r,int v){add(l,v),add(r+1,-v);}
    inline void clear(int x){
        for (int i=x;i<=n;i+=i&-i)  if (t[i]) t[i]=0;else break;
    }
    inline void clear(int l,int r){clear(l),clear(r+1);} 
}tr1,tr2;
struct Query{
    int q,u,t,id;
    bool operator< (const Query&h)const {return q<h.q;}
};
vector <Query> Q[N+M];
vector <pair<int,int>> ver[N+M];
inline int ksm(int a,int b=mod-2){
    int res=1;
    while (b){
        if (b&1) res=1ll*res*a%mod;
        a=1ll*a*a%mod;
        b>>=1; 
    }
    return res;
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
    init(M-1),n=read();
    for (int i=1,u,v;i<n;i++) 
        u=read(),v=read(),add(u,v),add(v,u);
    dep[1]=1,dfs1(1),dfs2(1,1);
    int ppcnt=pcnt;
    for (int i=1;i<=n;i++){
        a[i]=read();
        int x=a[i];
        for (int j=1;p[j]<=x&&j<=ppcnt;j++)
            if (x%p[j]==0){
                int cnt=0;
                while (x%p[j]==0) x/=p[j],cnt++;
                ver[j].emplace_back(cnt,i);
                if (x==1) break;
            }
        if (x!=1) {
            if (!mp.count(x)) mp[x]=++pcnt,p[pcnt]=x;
            ver[mp[x]].emplace_back(1,i);
        }
    }
    q=read();
    for (int i=1;i<=q;i++){
        int u=read(),v=read(),lca=LCA(u,v),x=read();ans[i]=1;
        for (int j=1;p[j]<=x&&j<=ppcnt;j++)
            if (x%p[j]==0){
                int cnt=0;
                while (x%p[j]==0) x/=p[j],cnt++;
                Q[j].push_back({cnt,u,1,i});
                Q[j].push_back({cnt,v,1,i});
                Q[j].push_back({cnt,lca,-1,i});
                if (fa[lca]) Q[j].push_back({cnt,fa[lca],-1,i});
                if (x==1) break;
            }
        if (x!=1) {
            if (!mp.count(x)) continue;
            int j=mp[x],cnt=1;
            Q[j].push_back({cnt,u,1,i});
            Q[j].push_back({cnt,v,1,i});
            Q[j].push_back({cnt,lca,-1,i});
            if (fa[lca]) Q[j].push_back({cnt,fa[lca],-1,i});
        }
    }
    for (int k=1;k<=pcnt;k++){
        int inv=ksm(p[k]);
        if (!ver[k].size()||!Q[k].size()) continue;
        sort(ver[k].begin(),ver[k].end()),sort(Q[k].begin(),Q[k].end());
        for (int j=0;j<ver[k].size();j++) {
            int u=ver[k][j].S;
            tr1.add(dfn[u],dfn[u]+sz[u]-1,ver[k][j].F);
        } 
        int j=ver[k].size()-1;
        for (int i=Q[k].size()-1;i>=0;i--){
            while (j>=0&Q[k][i].q<ver[k][j].F) {
                int u=ver[k][j].S;
                tr1.add(dfn[u],dfn[u]+sz[u]-1,-ver[k][j].F);
                tr2.add(dfn[u],dfn[u]+sz[u]-1,1);
                j--;
            }
            Query u=Q[k][i];
            int res=tr1.sum(dfn[u.u]),cnt=tr2.sum(dfn[u.u]);
            if (u.t==1) ans[u.id]=1ll*ans[u.id]*ksm(p[k],res+cnt*u.q)%mod;
            else ans[u.id]=1ll*ans[u.id]*ksm(inv,res+cnt*u.q)%mod;
        }
        for (int j=0;j<ver[k].size();j++) {
            int u=ver[k][j].S;
            tr1.clear(dfn[u],dfn[u]+sz[u]-1);
            tr2.clear(dfn[u],dfn[u]+sz[u]-1);
        }
    }
    for (int i=1;i<=q;i++) write(ans[i]),pc('\n');
	fwrite(wbuf,1,wrp-wbuf,stdout);
    return 0;
}
