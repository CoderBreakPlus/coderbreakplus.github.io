// created time: 2026-08-07
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P;
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

int n;

int f(int u,int k){
	int l=1,r=n;
	while(l<r){
		int mid=(l+r)>>1;
		cout<<"? "<<u<<" "<<k<<" "<<(mid-l+1)<<" ";
		for(int i=l;i<=mid;i++)
			cout<<i<<" ";
		cout<<endl;
		int x;
		if(!(cin>>x)) exit(0);
		if(x) r=mid; else l=mid+1;
	}	
	return l;
}

int qry(int u,int k,set<int> S){
	cout<<"? "<<u<<" "<<k<<" "<<S.size()<<" ";
	for(int x: S) cout<<x<<" ";
	cout<<endl;

	int ret;
	if(!(cin>>ret)) exit(0);
	return ret;
}
set<int>tmp;
void procedure(){
	cin>>n;

	int K=125;
	tmp.emplace(1);
	for(int i=0;i<K;i++) tmp.emplace(f(1,n+i));

	if(tmp.size()<K){
		for(int i=1;i<=n;i++)
		if(!tmp.count(i))
			if(qry(i,n,tmp)) tmp.emplace(i);
	}else{
		for(int i=1;i<=n;i++)
			if(!tmp.count(i))
				if(qry(i,K,tmp)) tmp.emplace(i);

		int res=500;
		for(int i=1;i<=n;i++)
			if(!tmp.count(i)){
				if(!res) break;
				res--;
				if(qry(i,n,tmp))tmp.emplace(i);
			}
		for(int i=1;i<=n;i++)
			if(!tmp.count(i)){
				if(!res) break;
				res--;
				if(qry(i,n+2*K,tmp))tmp.emplace(i);
			}
	}
	cout<<"! "<<tmp.size()<<" ";
	for(int x:tmp) cout<<x<<" "; cout<<endl;
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	// math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}