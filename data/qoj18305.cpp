// created time: 2026-06-04 08:43:24
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

const int S=10000,D=100;
int n,m,a[500005],p[2505],s[2505],c[2505];
ll que[25000005],ans[500005],g[S+5],tl;
ll cost[105];

int id[500005];

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),id[i]=i;
	m=read();
	for(int i=1;i<=m;i++)
		p[i]=read()-1,s[i]=read(),c[i]=read();

	sort(id+1,id+n+1,[](int x,int y){ return a[x]<a[y]; });
	int pt=0;

	for(int i=1;i<=m;i++)
		for(int j=i+1;j<=m;j++)
			if(p[i]>p[j]){
				swap(p[i],p[j]);
				swap(s[i],s[j]);
				swap(c[i],c[j]);
			}
	++m;
	p[m]=1e9,s[m]=1,c[m]=1e9;

	tl=que[0]=0;
	memset(cost,0x3f,sizeof(cost));

	for(int i=1;i<=m;i++){
		int e=min(p[i+1]-p[i],S);
		chkmin(cost[s[i]],(ll)c[i]);
		for(int j=1;j<=e;j++){
			que[++tl]=1e18;
			if(j<=D){
				for(int k=1;k<=i;k++){
					int to=max(p[i]+j-s[k], p[k]);
					int pos=tl-(p[i]+j)+to;
					if(pos>=0) chkmin(que[tl], que[pos]+c[k]);
				}
			}else{
				for(int k=1;k<=D;k++){
					int to=p[i]+j-k;
					int pos=tl-(p[i]+j)+to;
					chkmin(que[tl], que[pos]+cost[k]);
				}
			}
		}
		for(int j=0;j<=e;j++)g[j]=que[tl-e+j];

		int fk=1;
		for(int j=2;j<=i;j++)
			if((ll)c[j]*s[fk]<(ll)c[fk]*s[j])fk=j;
		auto calc = [&](int v){
			int x=max(0,(v-(p[i]+e)+s[fk]-1)/s[fk]);
			return g[v-x*s[fk]-p[i]]+(ll)x*c[fk];
		};

		while(pt+1<=n && a[id[pt+1]]<=p[i+1]){
			int x=id[++pt];
			ans[x]=calc(a[x]);
		}

		if(e==S){
			tl=0;
			for(int v=p[i+1]-D+1;v<=p[i+1];v++)
				que[++tl]=calc(v);
		}
	}
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
	puts("");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}