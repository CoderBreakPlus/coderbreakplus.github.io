// created time: 2026-07-09 07:35:32
#include <vector>
std::vector<long long> max_area(std::vector<int> H);

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back

inline int lg2(int x){ return 31^__builtin_clz(x); }
inline ll lg2(ll x){ return 63^__builtin_clzll(x); }
template<typename T>inline void chkmax(T &a,T b){ a=max(a,b); }
template<typename T>inline void chkmin(T &a,T b){ a=min(a,b); }

const int M = 500005;
int n,h[500005],f[20][500005],lc[500005],rc[500005],fa[500005];
int get(int x,int y){ return h[x]<h[y]?x:y; }
int query(int l,int r){
    int p = lg2(r-l+1);
    return get(f[p][l], f[p][r-(1<<p)+1]);
}
struct Line{
    ll k,b;
    ll val(ll x){ return (ll)k*x+b; }
}s[1500005]; int id;
vector<pair<ll,ll>>sl[500005],sr[500005];

int rt1[500005],rt2[500005];
ll a0[500005],a1[500005],a2[500005],a3[500005],ans3;
int t[10000005],ls[10000005],rs[10000005],cid;
int new_line(ll k,ll b){
    s[++id] = (Line){k,b};
    return id;
}
void update(int l,int r,int x,int &p){
    if(l>r) return;
    if(!p){
        t[p=++cid]=x;
        return;
    }
    int mid=(l+r)>>1;
    if(s[t[p]].val(mid)<s[x].val(mid)) swap(t[p],x);

    if(s[x].k>s[t[p]].k) update(mid+1,r,x,rs[p]);
    if(s[x].k<s[t[p]].k) update(l,mid-1,x,ls[p]);
}
int merge(int x,int y,int l,int r){
    if(!x||!y) return x|y;
    int mid=(l+r)>>1;
    if(s[t[y]].val(mid)>s[t[x]].val(mid))swap(t[x],t[y]);
    ls[x]=merge(ls[x],ls[y],l,mid-1);
    rs[x]=merge(rs[x],rs[y],mid+1,r);

    if(s[t[y]].k>s[t[x]].k) update(mid+1,r,t[y],rs[x]);
    if(s[t[y]].k<s[t[x]].k) update(l,mid-1,t[y],ls[x]);
    return x;
}
ll query(int l,int r,int x,int p){
    if(!p) return -1e18;
    int mid=(l+r)>>1;

    ll ret=s[t[p]].val(x);
    if(x<mid) chkmax(ret,query(l,mid-1,x,ls[p]));
    if(x>mid) chkmax(ret,query(mid+1,r,x,rs[p]));
    return ret;
}

vector<pair<ll,ll>>glo;

int build(int l,int r){
    if(l>r) return 0;
    int p=query(l,r);
    lc[p]=build(l,p-1),rc[p]=build(p+1,r);
    if(lc[p])fa[lc[p]]=p;
    if(rc[p])fa[rc[p]]=p;

    ll area=(ll)h[p]*(r-l+1);
    sr[l].pb(r-l+1,area),sl[r].pb(r-l+1,area);
    glo.pb(h[p],area);

    a0[p]=area;
    a1[p]=max({a1[lc[p]],a1[rc[p]],area});
    a2[p]=max({a2[lc[p]],a2[rc[p]],a1[lc[p]]+a1[rc[p]]});
    a3[p]=max({a3[lc[p]],a3[rc[p]],a1[lc[p]]+a2[rc[p]],a2[lc[p]]+a1[rc[p]]});

    rt1[p]=merge(rt1[lc[p]],rt1[rc[p]],-M,0);
    rt2[p]=merge(rt2[lc[p]],rt2[rc[p]],-M,0);

    ll tmp;
    chkmax(a2[p], tmp=area+query(-M,0,-h[p],rt1[p]));
    chkmax(a3[p], area+query(-M,0,-h[p],rt2[p]));

    update(-M,0,new_line(r-l+1,area),rt1[p]);
    update(-M,0,new_line(r-l+1,tmp),rt2[p]);

    return p;
}
struct Convex{
    vector<pair<ll,ll>>v;
    Convex(){ v={{0,0}}; }
    void abandon(){ vector<pair<ll,ll>>().swap(v); }
    bool check(pair<ll,ll> A,pair<ll,ll> B,pair<ll,ll> C){
        B.fi-=A.fi,B.se-=A.se,C.fi-=A.fi,C.se-=A.se;
        return (__int128)B.se*C.fi>(__int128)C.se*B.fi;
    }
    void simplify(){
        vector<pair<ll,ll>>stk={{0,0}};
        for(auto p: v){
            if(p.fi==stk.back().fi){
                chkmax(stk[stk.size()-1].se,p.se);
                continue;
            }
            while(stk.size()>=2 && !check(stk[stk.size()-2],stk.back(),p)){
                stk.pop_back();
            }
            stk.push_back(p);
        }
        swap(stk,v);
    }
    void pre_dif(){
        for(int i=v.size()-1;i>=1;i--) v[i].fi-=v[i-1].fi,v[i].se-=v[i-1].se;
    }
    void pre_sum(){
        for(int i=1;i<v.size();i++) v[i].fi+=v[i-1].fi,v[i].se+=v[i-1].se;
    }
}tot,tl[1200005],tr[1200005];

void Montagem_Pitty(Convex &Me,Convex &Beauty,Convex &Pity){
    Me.v.resize(Beauty.v.size()+Pity.v.size());
    merge(Beauty.v.begin(),Beauty.v.end(),Pity.v.begin(),Pity.v.end(),Me.v.begin());
    Me.simplify();
}
void Anti_Utopia(Convex &Success, Convex &Failure){
    Success.pre_dif(), Failure.pre_dif();
    Convex Life; Life.v.resize(Success.v.size()+Failure.v.size()-1);
    merge(Success.v.begin()+1,Success.v.end(),Failure.v.begin()+1,Failure.v.end(),Life.v.begin()+1,
        [](const pair<ll,ll> &A, const pair<ll,ll> &B){
            return (__int128)A.se*B.fi>(__int128)B.se*A.fi;
        });
    Life.pre_sum();
    for(auto p: Life.v){
        tot.v.push_back(p);
    }
}
void solve(int l,int r,int p){
    if(l==r){
        tl[p].v=sl[l],tr[p].v=sr[l];
        vector<pair<ll,ll>>().swap(sl[l]),vector<pair<ll,ll>>().swap(sr[l]);
        return;
    }
    int mid=(l+r)>>1;
    solve(l,mid,p<<1),solve(mid+1,r,p<<1|1);
    Montagem_Pitty(tl[p],tl[p<<1],tl[p<<1|1]);
    Montagem_Pitty(tr[p],tr[p<<1],tr[p<<1|1]);

    Anti_Utopia(tl[p<<1], tr[p<<1|1]);
    tl[p<<1].abandon(), tl[p<<1|1].abandon();
    tr[p<<1].abandon(), tr[p<<1|1].abandon();
}
vector<ll> max_area(vector<int> H){
    n=H.size();
    for(int i=1;i<=n;i++)h[i]=H[i-1];
    for(int i=1;i<=n;i++)f[0][i]=i;
    for(int i=1;(1<<i)<=n;i++)
        for(int j=1;j<=n-(1<<i)+1;j++)
            f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);

    for(int i=1;i<=n;i++)sl[i]=sr[i]={{0,0}};
    int p=build(1,n);
    solve(1,n,1);

    sort(tot.v.begin(),tot.v.end(),[](const pair<ll,ll> &A,const pair<ll,ll> &B){
        if(A.fi!=B.fi)return A.fi<B.fi;
        else return A.se>B.se;
    });

    tot.simplify();
    sort(glo.begin(),glo.end(),greater<pair<ll,ll>>());

    vector<pair<ll,ll>>hh=tot.v;

    int pt=0;

    auto calc = [&](ll u,ll v,int i){ return v+hh[i].se-u*hh[i].fi; };
    for(auto [u,v]:glo){
        while(pt+1<hh.size()&&calc(u,v,pt)<calc(u,v,pt+1)) pt++;
        chkmax(ans3,calc(u,v,pt));
    }
    return {a1[p],max(a1[p],a2[p]),max({a1[p],a2[p],a3[p],ans3})};
}