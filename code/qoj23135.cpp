// created time: 2026-10-08 13:45:48
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }
const int mod = 1e9+9, base = rng(1e7,2e7);
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
int n,m,fa[500005],pw[500005],c[500005];
vector<int>S[500005];
vector<tuple<int,int,int,int>>edge;

void upd(int x,int v){
	while(x<=n){
		addmod(c[x]+=v);
		x+=(x&-x);
	}
}
int qry(int x){
	int ret=0;
	while(x){
		addmod(ret+=c[x]);
		x-=(x&-x);
	}
	return ret;
}
void setfa(int x,int v){
	int dc=(ull)(mod+v-fa[x])*pw[x]%mod;
	upd(x,dc); fa[x]=v;
}
void merge(int x,int y){
	x=fa[x],y=fa[y];
	if(S[x].size()>S[y].size())swap(x,y);
	for(int a:S[x])
		S[y].pb(a),setfa(a,y);
	vector<int>().swap(S[x]);
}
bool check(int l1,int r1,int l2,int r2){
	int val1=(ull)(qry(r1)+mod-qry(l1-1))*pw[l2-l1]%mod;
	int val2; addmod(val2=qry(r2)+mod-qry(l2-1));
	return val1==val2;
}
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) setfa(i,i),S[i]={i};
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),l=read(),c=read();
		if(u==v)continue;
		if(u>v)swap(u,v); edge.pb(c,u,v,l);
	}
	sort(edge.begin(),edge.end());
	ll out=0;
	for(auto [c,u,v,l]: edge){
		while(l>=1){
			int L=1,R=l,Ans=0;
			while(L<=R){
				int M=(L+R)>>1;
				if(check(u,u+M-1,v,v+M-1))Ans=M,L=M+1;
				else R=M-1;
			}
			if(Ans>=l)break;
			u+=Ans,v+=Ans;
			merge(fa[u],fa[v]),out+=c;
			u++,v++,l-=Ans+1;
		}
	}
	printf("%lld\n",out);
	vector<tuple<int,int,int,int>>().swap(edge);
	for(int i=1;i<=n;i++) c[i]=fa[i]=0,vector<int>().swap(S[i]);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	pw[0]=1;
	for(int i=1;i<=5e5;i++) pw[i]=(ull)pw[i-1]*base%mod;
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}