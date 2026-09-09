// created time: 2026-09-08 09:32:09
#include<bits/stdc++.h>
// #include"grader.cpp"
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

void init(int c,int t){

}

int n;
ull a[500005];

const int B = 63;

bool mp[1000005], mp2[1000005];

pair<ll,ll> brute(int m){
	// map<ull,int>mp,mp2;
	for(int i=0;i<=m;i++) mp[i]=mp2[i]=0;

	ll cnt=0,sum=0,hv=0;
	ull fuck=0;

	int demand=-1;
	// cout<<"bruting"<<endl;
	for(int x=B;x>=0;x--){
		ull f0=(1ull<<x)-1;
		ull exp=0;
		// cout<<"solving x="<<x<<endl;
		for(int j=1;j<=m && j<=(1ull<<x);j++){
			// cout<<"j="<<j<<endl;
			ull val=(1ull<<x)-j;

			// cout<<"j = "<<j<<" dec: "<<(a[j]^a[j-1])<<endl;
			// assert(!((a[j]^a[j-1])>>x&1));
			if(((a[j]^a[j-1])>>x&1)^mp[j]){
				// cout<<"shabi"<<endl;
				if(x<B && val+m>=(1ull<<x+1)) return {-1,-1};
				fuck^=val;
				mp[j]^=1;
				demand=-1;
				cnt++, addmod(sum += val%mod);
			}
		}
		if(m>(1ull<<x))
			if(((a[m]^a[m-1])>>x&1)!=((a[m-(1ull<<x)]^a[m-(1ull<<x)-1])>>x&1))
				return {-1,-1};

		if(((fuck^a[0])>>x)&1){
			fuck^=(1ull<<x);
			// cout<<"modify at "<<x<<endl;
			if(x==B) {
				addmod(sum += (1ull<<x)%mod);
			}else{
				demand=x;
				addmod(sum += (1ull<<x)%mod);
			}
		}
		
		if(x){
			if((1ull<<x-1)<m)
			for(int i=(1ull<<x-1)+1;i<=m;i++)
				mp[i-(1ull<<x-1)]^=mp[i];
		}
	}
	if(~demand){
		if(m < (1ull<<demand))
			cnt+=2;
		else
			return {-1,-1};
	}
	return {max(hv,cnt), sum};
}
vector<pair<ll,ll>> seq(int N, vector<ull> A){
	n=N;
	for(int i=0;i<=n;i++)a[i]=A[i];

	// for(int i=1;i<=n;i++) cout<<a[i]<<" "; cout<<endl;

	vector<pair<ll,ll>>ret(n,{-1,-1});
	ret[n-1]=brute(n);
	return ret;
}