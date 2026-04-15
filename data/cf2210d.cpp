// created time: 2026-04-15 14:48:52
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

int n; char s[500005],t[500005];
int stk[500005],to1[500005],to2[500005],cnt1[500005],cnt2[500005],tp;
void procedure(){
	n=read();
	scanf("%s%s",s+1,t+1);

	for(int i=0;i<=n;i++)cnt1[i]=cnt2[i]=0;

	tp=0;
	for(int i=1;i<=n;i++){
		if(s[i]=='(') stk[++tp]=i;
		else{
			to1[i]=stk[tp--];
			cnt1[stk[tp]]++;
		}
	}
	int all=0;
	for(int i=0;i<=n;i++)if(cnt1[i]>1)all+=cnt1[i]-1;

	tp=0;
	for(int i=1;i<=n;i++){
		if(t[i]=='(') stk[++tp]=i;
		else{
			to2[i]=stk[tp--];
			cnt2[stk[tp]]++;
		}
	}
	for(int i=0;i<=n;i++)if(cnt2[i]>1)all-=cnt2[i]-1;

	int sb1=0,sb2=0;
	for(int i=n;i>=1;i--){
		if(s[i]==')'&&to1[i]==n-i+1)sb1++;
		else break;
	}
	for(int i=n;i>=1;i--){
		if(t[i]==')'&&to2[i]==n-i+1)sb2++;
		else break;
	}
	puts((all||sb1!=sb2)?"NO":"YES");
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