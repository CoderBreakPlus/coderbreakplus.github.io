// created time: 2026-05-20 19:50:35
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

int n,m,p[200005],c[200005],tp[400005],tc[400005],d[400005];
int ans[200005];

vector<int>vec0[1000005],vec1[1000005];
int qz0[1000005],qz1[1000005];

void procedure(){
	n=read();

	int mp=1e9,mc=1e9,mpc=1e9;
	for(int i=1;i<=n;i++)chkmin(mp,p[i]=read());
	for(int i=1;i<=n;i++)chkmin(mc,c[i]=read()),chkmin(mpc,p[i]+c[i]);

	m=read();
	for(int i=1;i<=m;i++) tp[i]=read();
	for(int i=1;i<=m;i++) tc[i]=read();
	for(int i=1;i<=m;i++) d[i]=read();

	for(int i=0;i<=1e6;i++)qz0[i]=qz1[i]=1e9;
	for(int i=1;i<=n;i++)chkmin(qz0[p[i]],c[i]),chkmin(qz1[c[i]],p[i]);
	for(int i=1;i<=1e6;i++)chkmin(qz0[i],qz0[i-1]),chkmin(qz1[i],qz1[i-1]);

	for(int i=1;i<=m;i++){
		int v1=(mp<tp[i]?0:min(tp[i]+d[i],mp))+tc[i];
		int v2=(mc<tc[i]?0:min(tc[i]+d[i],mc))+tp[i];

		int s1=min(v1,v2)+d[i];
		int s2=mpc;
		int s3=tp[i]?qz0[tp[i]-1]:1e9;
		if(s3<tc[i])s3=0;

		int s4=tc[i]?qz1[tc[i]-1]:1e9;
		if(s4<tp[i])s4=0;
		// cout<<"1: "<<min(v1,v2)+d[i]<<endl;
		// cout<<s1<<" "<<s2<<" "<<s3<<" "<<s4<<endl;
		ans[i]=min({s1,s2,s3,s4});
		printf("%d\n",ans[i]);
	}
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