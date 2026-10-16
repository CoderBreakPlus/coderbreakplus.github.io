// created time: 2026-10-15 14:48:15
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

int n,k,a[1000005];

void Alice(){
	n=read(),k=read();
	for(int i=1;i<=n;i++)a[i]=0;
	while(k--) a[read()]=1;
	
	int kn=0, br=0, lst;
	for(int i=1;i<=n;i++){
		if(!a[i]){
			if(!br)lst=i;
			else br--;
		}else br++;
	}
	a[lst]=1;
	for(int i=1;i<=n;i++)
		if(a[i]) printf("%d ",i);
	puts("");
}
int stk[1000005];
void Bob(){
	n=read(),k=read();
	for(int i=1;i<=n;i++)a[i]=0;
	++k;
	while(k--) a[read()]=1;

	int tp=0;
	for(int i=1;i<=n;i++){
		if(!a[i]){
			if(tp) --tp;
		}else
			stk[++tp]=i;
	}
	printf("%d\n",stk[1]);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	char s[10];
	scanf("%s",s);
	ll T=read();
	if(s[0]=='A'){
		while(T--) Alice();
	}else{
		while(T--) Bob();
	}
	return 0;
}