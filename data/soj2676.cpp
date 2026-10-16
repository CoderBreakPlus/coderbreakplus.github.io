// created time: 2026-10-16 07:10:00
#include<bits/stdc++.h>
#include"lis.h"
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

int lis(int n){
	n--;
	int sz=1;
	while(2*sz+1<=n)sz*=2;

	// cout<<"sz="<<sz<<endl;
	// 对前 sz 个二分
	int l=0,r=(n+1)/2,lst=(n+1)/2;
	for(int t=0;l<r&&(1<<t)<sz;t++){
		int mid=(l+r+1)>>1;
		vector<int>vec;
		for(int i=mid;i<=lst;i++)vec.pb(i);
		// cout<<"from "<<mid<<"->"<<lst<<endl;
		if(vec.size()==1||query(vec)==vec.size()){
			lst=mid;
			r=mid;
		}else
			l=mid;
	}
	if(lst>1){
		// cout<<"fuck1"<<endl;
		vector<int>q1,q2;
		for(int i=0;i<=n;i++){
			if(i!=lst)q1.pb(i);
			if(i!=lst-1)q2.pb(i);
		}
		return max(query(q1),query(q2));
	}
	vector<int>q1={0,1},q2;
	for(int i=1;i<=n;i++) q2.pb(i);
	return query(q1)+query(q2)-1;
}