// created time: 2026-04-09 17:44:27
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
inline void addmod(int &x){ if(x >= mod) x -= mod; }
inline void addmod(ll &x){ if(x >= mod) x -= mod; }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }

ll n,q,k;
ll a[500005],s[500005],t[500005];

ll f[20][500005],g[20][500005];

ll que[500005],val[500005],tl;
void procedure(){
	n=read(),q=read(),k=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(!(i&1)) s[i]=s[i-1]-a[i];
		else s[i]=s[i-1]+a[i];
		t[i]=(s[i]%k+k)%k;
	}
	if(n&1) n++,s[n]=s[n-1],t[n]=(s[n]%k+k)%k;

	set<tuple<ll,ll,ll>>S = {{-1e18, 1e18, n}};

	auto split = [&](ll v){
		auto [l,r,x] = *prev(S.lower_bound({v+1,-2e18,0}));
		if(l==v) return;
		S.erase({l,r,x});
		S.emplace(l,v-1,x),S.emplace(v,r,x);
	};
	for(ll i=n-1;i>=1;i-=2){
		val[i+1]=max(t[i],t[i]-a[i+1]+k);
		while(tl && val[i+1]<=val[que[tl]]) tl--;
		que[++tl]=i+1;

		if(i+1!=n){
			ll L=t[i]-a[i+1]+1, R=t[i];
			split(L);
			split(R+1);

			auto it = S.lower_bound({L,-2e18,0});
			while(it != S.end() && get<0>(*it)<=R){
				S.erase(it);
				it = S.lower_bound({L,-2e18,0});
			}
			S.emplace(L,R,i+1);
		}

		auto [x,y,z]=*prev(S.lower_bound({t[i-1]+1,-2e18,0}));

		ll pt=z;

		ll lft=1,rht=tl;
		while(lft<=rht){
			ll mid=(lft+rht)>>1;
			if(val[que[mid]]<t[i-1]) {
				pt=min(pt,que[mid]);
				lft=mid+1;
			}else rht=mid-1;
		}

		f[0][i]=pt+1;
		g[0][i]=(s[pt-1]-s[i-1])/k;
	}
	f[0][n+1]=n+1,g[0][n+1]=0;
	for(ll i=1;i<=19;i++)
		for(ll j=1;j<=n+1;j+=2){
			f[i][j]=f[i-1][f[i-1][j]];
			g[i][j]=g[i-1][j]+g[i-1][f[i-1][j]];
		}

	while(q--){
		ll l=read(),r=read();
		if(!(l&1)) l++;
		if(!(r&1)) r--;
		if(l>r){
			puts("0");
			continue;
		}

		ll ans=0;
		for(ll i=19;i>=0;i--){
			if(f[i][l]<=r){
				ans+=g[i][l];
				l=f[i][l];
			}
		}
		printf("%lld\n", ans+max(0ll,(s[r]-s[l-1])/k));
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