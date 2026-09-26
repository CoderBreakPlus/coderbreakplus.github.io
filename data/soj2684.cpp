// created time: 2026-09-26 13:53:48
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 998244353;
inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
inline int lg2(int x){ return 31^__builtin_clz(x); }
inline ll lg2(ll x){ return 63^__builtin_clzll(x); }
template<typename T>inline void addmod(T &x){ if(x >= mod) x -= mod; }
template<typename T>inline void chkmax(T &a,T b){ a=max(a,b); }
template<typename T>inline void chkmin(T &a,T b){ a=min(a,b); }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }

const int M = 1.18e7;
#define mid ((l+r)>>1)
int lc[M+5],rc[M+5],t[400005],id;
bitset<M+5> ban;
bitset<M+5> is_leaf; 
void update(int l,int r,int x,int node,int val,int bef,int &p){
	p=++id;
	if(l==r){
        is_leaf[p] = 1;
        lc[p] = node;
        rc[p] = val;
		return;
	}
	lc[p]=~bef?lc[bef]:-1,rc[p]=~bef?rc[bef]:-1;
	if(x<=mid) update(l,mid,x,node,val,lc[p],lc[p]);
	if(x>mid) update(mid+1,r,x,node,val,rc[p],rc[p]);
}

int getpoint(int l,int r,int x,int p){
	if(l==r) return lc[p];
	if(x<=mid) return getpoint(l,mid,x,lc[p]);
	else return getpoint(mid+1,r,x,rc[p]);
}

int n,m,k,fl[400005],lst[400005];
map<int,int>E[200005];
map<int,int>son[400005];

void print(int l,int r,int p){
	if(!~p)return;
	if(l==r)return;
	print(l,mid,lc[p]),print(mid+1,r,rc[p]);
}

void build(){
	queue<int>q;
	for(int i=1;i<=n;i++){
		update(1,n,i,i,-1,t[0],t[0]);
	}
	for(int i=1;i<=n;i++){
		q.push(i);
		t[i]=t[0];
		for(auto [j,w]:E[i]){
			update(1,n,j,son[i].count(j)?son[i][j]:j,w,t[i],t[i]);
		}
	}

	while(!q.empty()){
		int x=q.front();q.pop();
		if(x>n) t[x]=t[fl[x]];
		ban[x]=ban[x]|ban[fl[x]];
		for(auto [w,y]:son[x]){
			fl[y]=getpoint(1,n,w,t[fl[x]]);
			update(1,n,w,y,E[lst[x]][w],t[x],t[x]);
			q.push(y);
		}
	}
}

ll dis[M+5]; bitset<M+5>vis;
void procedure(){
	memset(lc,-1,sizeof(lc));
	memset(rc,-1,sizeof(rc));
	n=read(),m=read(),k=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		E[u][v]=w;
	}
	for(int i=1;i<=n;i++)
		lst[son[0][i]=++id]=i;
	while(k--){
		vector<int> vec;
		int rt=0,p=read(),flg=1;
		while(p--){
			vec.pb(read());
			if(vec.size()>=2 && !E[vec[vec.size()-2]].count(vec.back())){
				flg=0;
			}
		}
		if(flg){
			for(int x: vec){
				if(!son[rt].count(x)) lst[son[rt][x]=++id]=x;
				rt=son[rt][x];
			}
			ban[rt]=1;
		}
	}
	int cnt=id;
	build();
    
	memset(dis,0x3f,sizeof(dis));
	priority_queue<pair<ll,int>>q;
	if(ban[son[0][1]]){
		puts("-1");
		return;
	}
	dis[son[0][1]]=0; q.push({0,son[0][1]});
	while(!q.empty()){
		int x=q.top().se;q.pop();
		if(vis[x])continue; vis[x]=1;
        
        if (x <= cnt) {
            int y = t[x];
            if (y > 0 && !ban[y]) {
                if (dis[y] > dis[x]) {
                    dis[y] = dis[x];
                    q.push({-dis[y], y});
                }
            }
        } 
        else {
            if (is_leaf[x]) {
                int y = lc[x], w = rc[x];
                if (y > 0 && !ban[y] && w != -1) {
                    if (dis[y] > dis[x] + w) {
                        dis[y] = dis[x] + w;
                        q.push({-dis[y], y});
                    }
                }
            } 
            else {
                int y = lc[x];
                if (y > 0 && !ban[y]) {
                    if (dis[y] > dis[x]) {
                        dis[y] = dis[x];
                        q.push({-dis[y], y});
                    }
                }
                y = rc[x];
                if (y > 0 && !ban[y]) {
                    if (dis[y] > dis[x]) {
                        dis[y] = dis[x];
                        q.push({-dis[y], y});
                    }
                }
            }
        }
	}
	ll ans=1e18;
	for(int i=1;i<=cnt;i++)
		if(lst[i]==n)
			chkmin(ans,dis[i]);
	printf("%lld\n",(ans<1e17)?ans:-1);
}

int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}