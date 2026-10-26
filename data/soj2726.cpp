// created time: 2026-10-24 11:17:31
#include<bits/stdc++.h>
#include"apotheosis.hpp"
#ifdef LOCAL
#include"grader.cpp"
#endif

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

vector<vector<int>>Alice(int N,int L,string S){
	vector<int>lim(51,0);
	for(int i=0;i<S.size();i++)lim[i]=S[i]-'0';
	vector<vector<int>>T(N,vector<int>(N,0));

	T[0][0]=lim[0];
	int cnt=0;
	for(int i=1;i<=13;i++){
		vector<pair<int,int>>vec;
		for(int x=0;x<=7;x++){
			int y=i-x;
			if(0<=y&&y<=7){
				vec.pb(x,y);
			}
		}
		int sb=0;
		for(int i=1;i<vec.size();i++){
			T[vec[i].fi][vec[i].se]=lim[++cnt];
			if(~i&1) sb^=lim[cnt];
		}
		T[vec[0].fi][vec[0].se]=sb;
	}
	T[7][7]=lim[50];
	return T;
}
string Bob(int N,int L,vector<vector<int>>T){
	vector<int>lim(51,0);
	lim[0]=1-T[0][0];
	int cnt=0;
	int X=0,Y=0;
	for(int i=1;i<=13;i++){
		vector<pair<int,int>>vec;
		for(int x=0;x<=7;x++){
			int y=i-x;
			if(0<=y&&y<=7){
				vec.pb(x,y);
			}
		}
		vector<int>tmp(vec.size());

		int p0=-1,p1=-1;
		for(int i=0;i<vec.size();i++){
			tmp[i]=T[vec[i].fi][vec[i].se];
			if(vec[i].fi==X&&vec[i].se==Y+1){
				if(~p0)p1=i;
				else p0=i;
			}
			if(vec[i].fi==X+1&&vec[i].se==Y){
				if(~p0)p1=i;
				else p0=i;
			}
		}
		if(!~p1){
			tmp[p0]^=1;
			X=vec[p0].fi,Y=vec[p0].se;
		}else{
			tmp[p0]^=1;
			X=vec[p0].fi,Y=vec[p0].se;
			int now=0;
			for(int j=0;j<vec.size();j+=2)now^=tmp[j];
			if(now){
				tmp[p0]^=1;
				tmp[p1]^=1;
				X=vec[p1].fi,Y=vec[p1].se;
			}
		}
		for(int i=1;i<vec.size();i++){
			lim[++cnt]=tmp[i];
		}
	}
	lim[50]=1-T[7][7];
	string S;
	for(int i=0;i<L;i++)S+=char('0'+lim[i]);
	return S;
}