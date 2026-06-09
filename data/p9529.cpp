// created time: 2026-06-09 16:26:54

#ifdef LOCAL
#include"dango.h"
#endif
#ifndef LOCAL
#include<vector>
void Solve(int N, int M);
int Query(const std::vector<int> &x);
void Answer(const std::vector<int> &a);
#endif

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
vector<int>vec;

bool vis[50005];

void solve(vector<int> a,int m){
#ifdef LOCAL
	cout<<"[";
	for(int x:a) cout<<x<<","; cout<<"] m = "<<m<<endl;
#endif
	if(!m)return;
	if(m==1){
		Answer(a);
		return;
	}
	// int sz=a.size();
	shuffle(a.begin(),a.end(),rnd);
	auto query = [&](){
		vector<int>tmp;
		for(int i=0;i<a.size();i++)
			if(!vis[i])tmp.emplace_back(a[i]);
		return Query(tmp);
	};
	int sb=m/2;
	for(int i=0;i<a.size();i++)vis[i]=0;
	for(int i=0;i<a.size();i++){
		vis[i]=1;
		if(query()<sb)
			vis[i]=0;
	}
	vector<int>v0,v1; 
	for(int i=0;i<a.size();i++)
		if(vis[i]) v1.pb(a[i]); else v0.pb(a[i]);
	solve(v0,sb),solve(v1,m-sb);
}
void Solve(int N,int M){
	vector<int>vec;
	for(int i=1;i<=N*M;i++)vec.pb(i);
	solve(vec,M);
}