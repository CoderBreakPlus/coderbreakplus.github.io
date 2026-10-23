// created time: 2026-10-23 07:56:16
#include<bits/stdc++.h>
#include"range.h"
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
mt19937_64 rnd(114514);
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }

vector<int>all;
vector<int>lst;

int N;
int qry(vector<int> vec, bool res=0){
	// cout<<"querying ";
	// for(int x: vec) cout<<x<<" "; cout<<endl;
	// cout<<"res = "<<res<<endl;

	for(int x:vec)all[x]^=1;
	vector<int> _xor;
	for(int i=0;i<N;i++)if(all[i]!=lst[i])_xor.pb(i);
	// cout<<"upd ";
	// for(int x:_xor) cout<<x<<" "; cout<<endl;
	int ret=query(_xor).fi;
	lst=all;
	if(res) for(int x:vec)all[x]^=1;
	return ret;
}
std::vector<int> recover(int c,int n){
	N=n;
	all.clear();
	all.resize(n,0);
	lst=all;

	vector<int>res,A(n,(n+1)/2),B(n,(n+1)/2);
	for(int i=0;i<n;i++)res.pb(i);

	for(int l=1,r=n,tar=n-1;l<r;l++,r--,tar--){
		shuffle(res.begin(),res.end(),rnd);
		// cout<<"##at "<<l<<" "<<r<<" need tar < "<<tar<<endl;
		while(1){
			vector<int>love;
			for(int i=0;i<res.size();i++)
				if(rnd()&1)love.pb(res[i]);
			int now=qry(love);
			// cout<<"now="<<now<<endl;
			if(now<tar) break;
		}

		// cout<<"#satisfied"<<endl;

		int X1=0,X2=0;
		if(l==1){
			if(l==1){
				vector<int>V1,V2;
				while(1){
					V1.clear(),V2.clear();
					for(int x:res){
						if(rnd()&1)V1.pb(x);
						else V2.pb(x);
					}
					if(qry(V1,1)==tar)break;
				}
				auto findone=[&](vector<int>v){
					while(v.size()>1){
						int mid=v.size()/2;
						vector<int>now(v.begin(),v.begin()+mid);
						if(qry(now,1)==tar)v.resize(mid);
						else v.erase(v.begin(),v.begin()+mid);
					}
					return v[0];
				};
				X1=findone(V1);
				X2=findone(V2);
			}
		}else{
			int L=0,R=(int)res.size()-1;
			while(L<=R){
				int M=(L+R)>>1;
				vector<int>tmp;
				for(int i=0;i<=M;i++)tmp.pb(res[i]);
				int now=qry(tmp,1);
				if(now==tar){
					X1=M;
					R=M-1;
				}else L=M+1;
			}
			L=X1+1,R=(int)res.size()-1;
			while(L<=R){
				int M=(L+R)>>1;
				vector<int>tmp;
				for(int i=X1+1;i<=M;i++)tmp.pb(res[i]);
				int now=qry(tmp,1);
				if(now==tar){
					X2=M;
					R=M-1;
				}else L=M+1;
			}
			X1=res[X1],X2=res[X2];
		}
		A[X1]=A[X2]=l;
		B[X1]=B[X2]=r;
		vector<int>res2;
		for(int x:res)if(x!=X1&&x!=X2)res2.pb(x);
		swap(res,res2);
	}
	for(int i=0;i<n;i++)if(all[i])swap(A[i],B[i]);
	return A;
}
