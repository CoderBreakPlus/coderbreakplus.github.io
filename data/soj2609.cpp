// created time: 2026-07-07 11:33:04
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

int n,m,q,mn[(1<<21)+5],mx[(1<<21)+5];
void pushup(int i){
	mn[i]=min(mn[i<<1],mn[i<<1|1]);
	mx[i]=max(mx[i<<1],mx[i<<1|1]);
}
void upd(int x,int y){
	x+=m;
	for(mx[x]=mn[x]=y,x>>=1;x;x>>=1)pushup(x);
}
int qry(int l,int r){
	int ans=1e9;
	for(int lp=m+l-1,rp=m+r+1;lp^rp^1;lp>>=1,rp>>=1){
		if(~lp&1) chkmin(ans,mn[lp^1]);
		if(rp&1) chkmin(ans,mn[rp^1]);		
	}
	return ans;
}
int find(int x,int y){
	int ans=0;
	for(x+=m-1;x;x>>=1){
		if((~x&1)&&(mx[x+1]>=y)){
			x++;
			while(x<m){
				x<<=1;
				if(mx[x]<=y)x++;
			}
			ans=x-m;
			break;
		}
	}
	return ans;
}
void procedure(){
	n=read(),q=read();
	m=1;
	while(m<=n+1)m<<=1;
	for(int i=m;i<2*m;i++)mn[i]=1e9,mx[i]=-1e9;
	for(int i=1;i<=n;i++)
		mn[i+m]=mx[i+m]=read();
	for(int i=m;i>=1;i--)pushup(i);
		
	while(q--){
		int op=read(),x=read(),y=read();
		if(op==1) upd(x,y);
		if(op==2) printf("%d\n",qry(x,y));
		if(op==3) printf("%d\n",find(x,y));
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