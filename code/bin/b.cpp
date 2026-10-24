// created time: 2026-10-23 18:24:24
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

int n,c0,c1;
char s[1000005];


void procedure(){
	n=read(),c0=read(),c1=read();
	int d0=0,d1=0;
	scanf("%s",s+1);
	for(int i=1;i<=n;i++){
		if(s[i]=='0') d0++;
		else d1++;
	}
	int sum=c0+c1*2+d0+d1*2;
	if(c0>d0){
		int now=sum-(c0-d0);
		assert(now%2==0);
		printf("%d\n",now/2+c0-d0);
		return;
	}
	if(c0==d0){
		if(!c0){
			if(c1!=d1)sum+=2;
			printf("%d\n",sum/2);
			return;
		}
		int now=sum/2;

		int tl=n,need=0;
		while(tl>=1&&s[tl]=='1')tl--,need++;
		if(c1<need)now++;
		printf("%d\n",now);
		return;
	}

	int cur=0,pos=0;
	if(c0)
		for(int i=1;i<=n;i++){
			if(s[i]=='0'){
				cur++;
				if(cur==c0){ pos=i; break; }
			}
		}
		// cout<<"pos="<<pos<<endl;
		int add=0,ok=0;
		for(int i=pos+1;i<=n;i++){
			if(s[i]=='1'){
				if(!ok) add++,ok=1;
			}else{
				if(!ok) add++;
				else ok=0;
			}
		}
		// cout<<"sum = "<<sum<<endl;
		int tl=n,need=0;
		while(tl>=1&&s[tl]=='1')tl--,need++;

		int calc=sum+add+ok;
		if(c1>=need && need) calc-=2;
		assert(calc%2==0);
		printf("%d\n",calc/2);

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