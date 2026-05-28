// created time: 2026-05-28 08:13:08
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

int n,a[400005],c[400005],h[400005],rk[400005],r[400005],m;
ll val[400005],f[400005];
bool vis[400005];

inline ll calc(int j,int s){
	return f[j]-val[max(r[j],h[j]+s)];
}
deque<tuple<int,int,int>>Q;
void push(int u){
	int s=r[u]-h[u];
	while(!Q.empty()){
		auto &[j,L,R] = Q.front(); 
		if(R<=s) Q.pop_front();
		else{ chkmax(L,s+1);break; }
	}
	int up=m-h[u];
	while(!Q.empty()){
		auto &[j,L,R]=Q.back();
		if(L>up) Q.pop_back();
		else{ chkmin(R,up);break; }
	}
	while(!Q.empty()){
		auto &[j,L,R]=Q.front();
		if(calc(u,R)>=calc(j,R)){ s=R;Q.pop_front();continue; }
		int l=L,r=R-1;
		while(l<=r){
			int mid=(l+r)>>1;
			if(calc(u,mid)<calc(j,mid)) r=mid-1;
			else l=mid+1;
		}
		s=r,L=r+1; break;
	}
	Q.push_front({u,0,s});
}
ll query(int s){
	int L=0, R=(int)Q.size()-1,ans=0;
	while(L<=R){
		int mid=(L+R)>>1;
		if(get<1>(Q[mid])<=s) ans=mid,L=mid+1;
		else R=mid-1;
	}
	return calc(get<0>(Q[ans]),s);
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)c[i]=read();

	for(int i=1;i<=n;i++){
		h[i]=h[i-1]+(a[i]==-1);
		if(~a[i])rk[a[i]]=-1;
	}
	for(int i=1;i<=n;i++){
		if(~rk[i])val[++m]=c[i];
		rk[i]+=rk[i-1]+1;
	}
	for(int i=1;i<=n;i++)
		if(~a[i]) r[i]=rk[a[i]];
	for(int i=1;i<=m;i++)
		val[i]+=val[i-1];

	int mx=0; vis[0]=1;
	for(int i=1;i<=n;i++){
		if(a[i]>mx && h[i]<=rk[a[i]]) vis[i]=1,mx=a[i];
	}

	Q.push_back({0,0,m});
	for(int i=1;i<=n;i++)if(vis[i]){
		// for(int j=i-1;j>=0;j--)if(vis[j]){
		// 	chkmax(f[i], f[j]+val[r[i]]-val[max(r[j],h[j]+r[i]-h[i])]);
		// 	if(h[i]-h[j]>=r[i]-r[j]) break;
		// }
		f[i]=query(r[i]-h[i])+val[r[i]]+c[a[i]];
		push(i);
	}
	Q.clear();Q.push_back({0,0,m});
	for(int i=1;i<=n;i++){
		if(vis[i]) push(i);
		printf("%lld ",query(m-h[i])+val[m]);
	}
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