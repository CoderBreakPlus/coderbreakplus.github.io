// created time: 2026-04-22 18:55:32
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

int n,k,w[1000005],qz[1000005];
void Alice(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)w[i]=-1;
	for(int i=1,x;i<=k;i++)cin>>x,w[x]=1;
	for(int i=1;i<=n;i++)qz[i]=qz[i-1]+w[i];

	int mn=0,pos=0;
	for(int i=1;i<=n;i++){
		if(qz[i]<=mn){
			mn=qz[i];
			pos=i;
		}
	}
	w[pos]=1;
	for(int i=1;i<=n;i++) if(w[i]==1) cout<<i<<" ";cout<<endl;
}
void Bob(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)w[i]=-1;
	for(int i=1,x;i<=k+1;i++)cin>>x,w[x]=1;
	for(int i=1;i<=n;i++)qz[i]=qz[i-1]+w[i];
	
	int mn=0,pos=0;
	for(int i=1;i<=n;i++) mn=min(mn,qz[i]);

	for(int i=n;i>=1;i--){
		
	}
}
void procedure(){
	string s;cin>>s;
	if(s=="Alice"){
		int T;cin>>T;
		while(T--)Alice();
	}else{
		int T;cin>>T;
		while(T--)Bob();
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