// created time: 2026-09-22 17:51:02
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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

int n,q,md[1000005],mx[1000005],qx[15],ans[15],dep[1000005],rt;
vector<int>E[1000005];
int son[1000005];

vector<int>s[1000005];
void dfs(int x,int fa){
	// cout<<"dep["<<x<<"] = "<<dep[x]<<endl;
	if(E[x].size()==1){
		s[x]={dep[x]};
		return;
	}
	shuffle(E[x].begin(),E[x].end(),rnd);
	for(int y:E[x])if(y!=fa){
		dep[y]=dep[x]+1;
		dfs(y,x); 
		if(!son[x]||s[y].size()>s[son[x]].size())son[x]=y;
	}
	swap(s[son[x]],s[x]);
	int len=s[x].size()-1;

	auto upd=[&](int d1,int s1){
		for(int k=1;k<=q;k++){
			auto check=[&](int Mid){
				int d2=max(Mid-d1-qx[k],0);
				return d2<=len&&s[x][d2]+s1-2*dep[x]>=Mid;
			};
			while(check(ans[k]+1))ans[k]++;
		}
	};

	for(int y:E[x])if(y!=fa&&y!=son[x]){
		for(int i=0;i<s[y].size();i++){
			upd(i,s[y][i]);
		}
		for(int i=0;i<s[y].size();i++)
			chkmax(s[x][i],s[y][i]);
	}
	upd(md[x],dep[x]);
	if(md[x]>len)s[x].pb(0);

	chkmax(s[x][md[x]],dep[x]);
}
void procedure(){
	n=read();
	for(int i=2;i<=n;i++){
		int x=read();
		E[x].pb(i),E[i].pb(x);
	}
	q=read();
	for(int i=1;i<=q;i++)qx[i]=read();

	memset(md,-1,sizeof(md));
	queue<int>Q;
	for(int i=1;i<=n;i++)if(E[i].size()==1)md[i]=0,Q.push(i);
	while(!Q.empty()){
		int x=Q.front();Q.pop();
		for(int y:E[x])if(!~md[y]){
			md[y]=md[x]+1;
			Q.push(y);
		}
	}
	for(int i=1;i<=n;i++)if(E[i].size()>1){rt=i;break;}
	dfs(rt,0);
	
	for(int i=1;i<=q;i++)printf("%d ",ans[i]);
	puts("");
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