// created time: 2026-04-14 15:47:53
#pragma GCC optimize(3,"Ofast","inline","unroll-loops")
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
inline int read(){
	int x=0; int ch=getchar_unlocked();
	while(ch<'0' || ch>'9') ch=getchar_unlocked();
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar_unlocked();
	return x;
}

int n,m,a[5000005],qz[5000005],dp[5000005];
int buc[1<<27];

inline void chkmax(int &a,int b){ if(b>a) a=b; }
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();

	for(int x=0;x<=27;x++){
		if(!(m&1)){
			for(int i=1;i<=n;i++)a[i]>>=1;
			m>>=1;
			continue;
		}
		for(int i=1;i<=n;i++){
			qz[i]=max(qz[i],buc[a[i]^m^1]);
			buc[a[i]]=i;
		}
		for(int i=1;i<=n;i++) buc[a[i]]=0,a[i]>>=1;
		m>>=1;
	}	
	for(int i=1;i<=n;i++){
		dp[i]=dp[i-1];
		if(qz[i]) dp[i]=max(dp[i], dp[qz[i]-1]+1);
	}
	for(int i=1;i<=n;i++)putchar_unlocked(dp[i]!=dp[i-1]?'Y':'N');
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