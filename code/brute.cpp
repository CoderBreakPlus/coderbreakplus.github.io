// created time: 2026-04-02 18:30:04
// E. Inverse Topological Sort

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

int n,a[100005],b[100005],ind[100005],ok[100005];
int c[100005],cc,d[100005],dd;
vector<int>E[100005];

void procedure(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i]=read();
	vector<pair<int,int>>edge;
	for(int i=1;i<n;i++){
		if(a[i]>a[i+1]){
			E[a[i]].pb(a[i+1]);
			edge.pb(a[i],a[i+1]);
			// cout<<"add "<<a[i]<<"->"<<a[i+1]<<endl;
			ind[a[i+1]]++;
		}
	}

	{
		priority_queue<int,vector<int>,greater<int>>q;
		for(int i=1;i<=n;i++)if(!(ok[i]=ind[i]))q.push(i);
		while(!q.empty()){
			int x=q.top();q.pop();
			c[++cc]=x;
			// cout<<"output "<<x<<endl;
			for(auto y:E[x]){
				ok[y]--;
				if(!ok[y]) q.push(y);
			}
		}
		for(int i=1;i<=n;i++)assert(a[i]==c[i]);
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