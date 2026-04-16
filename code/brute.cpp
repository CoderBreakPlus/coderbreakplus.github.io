// created time: 2026-04-16 11:33:26
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

int n=5,a[55];

void procedure(){
	for(n=1;n<=5;n++){
		for(int i=0;i<n;i++)a[i]=i;
		int cnt=0;
		do{
			bool f=1;
			for(int l=0;l<n;l++){
				vector<bool>v(n+1);
				int pt=0;
				for(int r=l;r<n;r++){
					v[a[r]]=1;
					while(v[pt]) pt++;
					if(pt==r-l+1 && pt!=n && pt!=1){
						f=0;
					} 
				}
			}
			cnt+=f;
		}while(next_permutation(a,a+n));
		cout<<cnt<<endl;
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.ans","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}