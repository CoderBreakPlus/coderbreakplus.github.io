// created time: 2026-08-17 13:41:13
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

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
const int B = 32;
int n; uint a[100005];
vector<int>pos[100005];

ull hsh[B];

struct Basis{
	uint a[B];
	bool ins(int x){
		for(int i=B-1;i>=0;i--){
			if((~x>>i)&1)continue;
			if(a[i]) x^=a[i];
			else {a[i]=x; return 1;}
		}
		return 0;
	}
	void clr(){ memset(a,0,sizeof(a)); }
	
	ull serious_ins(int x){
		for(int i=B-1;i>=0;i--){
			if((~x>>i)&1) continue;
			if(a[i]) x^=a[i];
			else{
				a[i]=x;
				for(int j=i-1;j>=0;j--)
					if(a[j] && ((a[i]>>j)&1)) a[i]^=a[j];
				for(int j=B-1;j>i;j--)
					if(a[j] && ((a[j]>>i)&1)) a[j]^=a[i];
				break;
			}
		}
		ull ret=0;
		for(int i=0;i<B;i++)ret+=hsh[i]*a[i];
		// for(int i=0;i<B;i++)cout<<a[i]<<" "; cout<<endl;
		return ret;
	}
}S,A[100005];

void procedure(){
	for(int i=0;i<B;i++)hsh[i]=rnd();
	n=read();
	int ans=0;
	for(int i=1;i<=n;i++)a[i]=read(),ans|=!a[i];
	pos[n+1]={};
	for(int i=n;i>=1;i--){
		S.clr(),pos[i]={};
		if(S.ins(a[i]))pos[i].pb(i);
		for(int j:pos[i+1])
			if(S.ins(a[j]))pos[i].pb(j);
	}
	for(int i=1;i<=n;i++){
		reverse(pos[i].begin(),pos[i].end());
		// for(int x:pos[i])cout<<a[x]<<" ";cout<<endl;
	}

	for(int i=1;i<=n;i++) A[i].clr();		
	for(int v=1;v<=B;v++){
		// cout<<"v="<<v<<endl;
		unordered_set<ull>S;
		for(int i=1;i<=n;i++){
			if(pos[i].empty())continue;
			ull tmp = A[i].serious_ins(a[pos[i].back()]);
			S.emplace(tmp);
			pos[i].pop_back();
			// cout<<"tmp = "<<tmp<<endl;
		}
		addmod(ans+=S.size());
	}
	printf("%d\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}