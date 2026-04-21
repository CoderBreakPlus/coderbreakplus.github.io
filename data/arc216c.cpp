// created time: 2026-04-21 19:23:43
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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

const int M=200050;
int n,a[200005],buc[M+5],mw[200005];
ll ans=0;
ull hsh[M+5],qz[M+5],val[M+5];

void solve(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1, mx=0, mn=M+1;
	ll tot=0;

	ull sbf=0;
	vector<int>rub;
	auto add = [&](int x){ buc[x]++, rub.pb(x), sbf^=hsh[x]; };
	auto del = [&](int x){ buc[x]-=2; };
	map<ull,int>L,R;
	
	for(int i=mid,pt;i>=l;i--){
		add(pt=a[i]);
		bool f=0;
		if(pt<=mn) mn=pt,f=1;
		while(buc[pt]==2){
			del(pt), add(++pt);
			if(f) mn++;
		}
		mx=max(mx, pt);
		val[i]=sbf^qz[mn], mw[i]=mx;
		if(sbf==hsh[mx]) mw[i]--;
		L[val[i]]++;
	}

	for(auto x:rub) buc[x]=0; vector<int>().swap(rub);
	sbf=mx=0;

	for(int i=mid+1,pt;i<=r;i++){
		add(pt=a[i]);
		while(buc[pt]==2) del(pt), add(++pt);
		mx=max(mx, pt);
		val[i]=sbf, mw[i]=mx;
		R[val[i]]++;
	}

	for(auto x:rub) buc[x]=0; vector<int>().swap(rub);	

	for(int i=mid;i>=l;i--){
		if(R.count(qz[mw[i]]^val[i]))
			tot += R[qz[mw[i]]^val[i]];
	}
	for(int i=mid+1;i<=r;i++){
		if(L.count(qz[mw[i]]^val[i]))
			tot += L[qz[mw[i]]^val[i]];
	}
	ans+=tot;
	solve(l,mid),solve(mid+1,r);
}
void procedure(){
	n=ans=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=0;i<=M;i++)hsh[i]=qz[i]=rnd();
	for(int i=1;i<=M;i++)qz[i]^=qz[i-1];
	solve(1,n);
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