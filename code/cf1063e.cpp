// created time: 2026-08-24 14:08:15
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

int n,a[1005],w;
char s[1005][1005];

void out(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)putchar(s[i][j]);
		puts("");
	}
}
bool vis[1005];
void procedure(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		for(int j=1;j<=n;j++)s[i][j]='.';
	}
	bool flg=1;
	for(int i=1;i<=n;i++)
		flg&=(a[i]==i);

	if(flg){
		printf("%d\n",n);
		out(); return;
	}	
	for(int i=n;i>=1;i--){
		if(vis[i])continue;

		if(a[i]==i){
			vis[i]=1;
			continue;
		}
		int p=a[i];
		vector<int>vec;
		while(!vis[p]){
			vec.pb(p),vis[p]=1;
			p=a[p];
		}


		// for(int x: vec) cout<<x<<" "; cout<<endl;

		if(vec.back()!=n){
			s[++w][vec[0]]='\\';
			s[w][n]='\\';
		}

		for(int j=0;j+1<vec.size();j++){
			if(vec[j]<vec[j+1]){
				s[++w][vec[j]]='/';
				s[w][vec[j+1]]='/';
			}else{
				s[++w][vec[j]]='\\';
				s[w][vec[j+1]]='\\';
			}
		}

		if(vec.back()!=n){
			s[w][vec.back()]='/';
			s[w][n]='/';
		}
	}
	printf("%d\n",n-1);
	out();
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}