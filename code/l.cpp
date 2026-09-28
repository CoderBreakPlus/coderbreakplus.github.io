
// created time: 2026-09-28 11:16:13
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

ll n,m,l[100005],r[100005],s[1000005],cnt;
ll buc[1000005];

void procedure(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		l[i]=read(),r[i]=read();
		s[++cnt]=l[i],s[++cnt]=r[i]+1;
	}
	for(ll l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		s[++cnt]=l,s[++cnt]=r+1;
	}
	sort(s+1,s+cnt+1);
	cnt=unique(s+1,s+cnt+1)-(s+1);

	for(int i=1;i<=m;i++){
		l[i]=lower_bound(s+1,s+cnt+1,l[i])-s;
		r[i]=lower_bound(s+1,s+cnt+1,r[i]+1)-s;
		buc[l[i]]++,buc[r[i]]--;
	}
	map<ll,ll>q;

	for(int i=1;i<cnt;i++){
		buc[i]+=buc[i-1];
		q[(n/s[i])*buc[i]]+=s[i+1]-s[i];
	}

	ll ans=0;
	if(q.size()==1 && q.begin()->se==1){
		ans += q.begin()->fi;
	}
	while(q.size()>1||q.begin()->se>1){
		auto [a,b]=*q.begin(); q.erase(a);
		if(b>=2){
			if(b&1) q[a]++;
			q[a*2]+=b/2;
			ans+=a*2*(b/2);
			continue;
		}
		assert(b==1);
		auto [c,d]=*q.begin(); q.erase(c);
		ans+=a+c; q[a+c]++;
		d--; if(d) q[c]+=d;
	}
	printf("%lld\n",ans);
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