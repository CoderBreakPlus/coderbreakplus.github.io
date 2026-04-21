// created time: 2026-04-21 16:39:55
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

int n,p[4005];

void upd(int x,int y){
	if(x==y)return;
	cout<<"? "<<x<<" "<<y<<endl;
	int a,b; if(!(cin>>a>>b)) exit(0);
	swap(p[a],p[b]);
}

void procedure(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>p[i];

	if(n&1){
		int pos;
		for(int i=1;i<=n;i++)
			if(p[i]==(n/2+1))pos=i;

		upd(pos, n/2+1);
		while(p[n/2+1]!=n/2+1){
			pos=n-pos+1;
			upd(pos, n/2+1);
		}
	}
	
	for(int i=1,j=n;i<j;i++,j--){
		{
			int a,b;
			for(int x=1;x<=n;x++){
				if(p[x]==i) a=x;
				if(p[x]==j) b=x;
			}
			upd(a,n-b+1);
		}
		{
			int a;
			for(int x=1;x<=n;x++){
				if(p[x]==i) a=x;
			}
			while(!(p[i]==i && p[j]==j)) upd(a,i);
		}
	}
	cout<<"!"<<endl;
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T;cin>>T;
	// math_init();
	while(T--) procedure();
	return 0;
}