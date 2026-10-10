// created time: 2026-10-07 10:51:23
#include<bits/stdc++.h>
#include"cake.h"
#ifdef LOCAL
#include"_c.cpp"
#endif
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod=998244353;
inline ll read(){
	ll x=0,f=1;int ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	return x*f;
}
inline int lg2(int x){return 31^__builtin_clz(x);}
inline ll lg2(ll x){return 63^__builtin_clzll(x);}
template<typename T>inline void addmod(T &x){if(x>=mod)x-=mod;}
template<typename T>inline void chkmax(T &a,T b){a=max(a,b);}
template<typename T>inline void chkmin(T &a,T b){a=min(a,b);}
inline ll qpow(ll a,ll b){
	ll ans=1,base=a;
	while(b){
		if(b&1)ans=ans*base%mod;
		base=base*base%mod;b>>=1;
	}
	return ans;
}
inline ll INV(ll x){return qpow(x,mod-2);}

ll n,m;
__int128 sum;

char add(ll x){
	sum+=x;
	return modify(x);
}

pair<ll,ll> cake(ll N){
	n=N,m=0,sum=0;

	ll L=0,R=0;
	for(ll k=1;;){
		int cnt=0;
		bool same=0;
		for(int T=0;T<6;T++){
			char c=add(k);
			if(c=='='){
				m=k;
				same=1;
				break;
			}
			if(c=='<')cnt++;
		}
		if(same)break;

		if(cnt>=4){
			L=k+1;
			R=min(n,2*k-1);
			break;
		}

		if(k==n){
			m=n;
			break;
		}
		ll nk=(ll)min<__int128>(n,((__int128)3*k+1)/2);
		if(nk<=k)nk=k+1;
		k=nk;
	}
	
	if(!m){
		const int T=8;
		while(L<R){
			ll M=(L+R)>>1;
			int cnt=0;
			bool same=0;
			for(int t=0;t<T;t++){
				char c=add(M);
				if(c=='='){
					m=M;
					same=1;
					break;
				}
				if(c=='<')cnt++;
			}
			if(same)break;

			ll lim=(ll)(((__int128)T*(M-L)+L-1)/L);

			if(cnt<=lim)R=M-1;
			else L=M+1;
		}
		if(!m)m=L;
	}

	if(m==1)return {0,1};

	ll s=(ll)(sum%m);
	if(s)add(m-s);

	L=0,R=m-1;
	while(L<R){
		ll M=(L+R+1)>>1;
		char c=add(m-M);
		add(M);
		if(c=='<')L=M;
		else R=M-1;
	}
	return {L,m};
}