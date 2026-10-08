// created time: 2026-10-08 09:30:35
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

const int B = 26;
int n,k;
char s[1000005];
int cnt[B];

void procedure(){
	memset(cnt,0,sizeof(cnt));

	n=read(),k=read();
	scanf("%s",s);
	for(int i=0;i<n;i++)cnt[s[i]-'a']++;

	if(n==1){
		puts("Yes");
		return;
	}
	if(n==2){
		puts(s[0]==s[1]?"Yes":"No");
		return;
	}

	if(!k){
		int buc=0;
		for(int i=0;i<B;i++)
			buc+=(cnt[i]&1);

		puts(buc<=1?"Yes":"No");
		return;
	}

	int d=__gcd(B,k),len=B/d,buc=0;

	int sum=0, flg=1, col=0;
	for(int i=0;i<d;i++){
		int now=0;
		for(int j=i,k=0;j<B;j+=d,k++){
			now+=cnt[j];
			sum+=cnt[j]*k;
		}
		buc+=(now&1);
		if(buc>1){puts("No");return;}
	}
	if(n%2 == 0 && len%2 == 0 && (sum&1)) puts("No");
	else puts("Yes");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}