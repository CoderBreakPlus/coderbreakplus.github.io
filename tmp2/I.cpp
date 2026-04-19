// created time: 2026-04-18 07:59:13
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

map<vector<int>,int>mp;

vector<int>vec[5005]; int t;

int now[10];

void dfs(int x,int w){
	if(x==6){
		vector<int>cur;
		for(int i=0;i<6;i++)cur.pb(now[i]);
		if(!mp.count(cur))mp[cur]=++t,vec[t]=cur;
		return;
	}
	for(int d=0;w+d<=8;d++){
		now[x]=w+d, dfs(x+1,w+d);
	}
}

int p[100],q[100];

void procedure(){
	int x=read();
	if(!p[x]&&!q[x]){
		puts("No");
		return;
	}
	puts("Yes");
	for(auto y:vec[p[x]])printf("%d ",y);
	for(auto y:vec[q[x]])printf("%d ",y);
	puts("");
}
bool f1[10],f2[10];
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif

	dfs(0,0);
	// cout<<t<<endl;
	// for(int i=1;i<=t;i++){
	// 	for(auto x: vec[i])cout<<x<<" ";cout<<endl;
	// }

	for(int i=1;i<=t;i++){
		for(int j=1;j<=t;j++){
			memset(f1,0,sizeof(f1)),memset(f2,0,sizeof(f2));
			for(auto x: vec[i]){
				f1[x]=1; if(x==6)f1[9]=1;
			}
			for(auto x: vec[j]){
				f2[x]=1; if(x==6)f2[9]=1;
			}

			int mx=1;
			while((f1[mx/10] && f2[mx%10])||(f2[mx/10] && f1[mx%10])) mx++;
			p[mx]=i,q[mx]=j;
		}
	}
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}