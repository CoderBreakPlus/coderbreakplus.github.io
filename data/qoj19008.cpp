// created time: 2026-09-03 08:56:07
#include<vector>
#pragma GCC optimize(3,"inline")
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2")
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

int n,nxt[5000005][9];
char s[5000005];

int seq[10000005][9],sz[10000005],bg[10],idx;

void procedure(){
	n=read();
	scanf("%s",s+1);
	for(int i=0;i<9;i++)nxt[n+1][i]=n+1;
	for(int i=n;i>=1;i--){
		memcpy(nxt[i],nxt[i+1],sizeof(nxt[i]));
		if(s[i]!='9')nxt[i][s[i]-'0']=i;
	}
	for(int i=1;i<=idx;i++){
		int now=0;
		for(int j=0;j<sz[i];j++){
			now=nxt[1+now][seq[i][j]];
			if(now>n)break;
		}

		if(now<=n){
			printf("%d ",sz[i]);
			int now=0;
			for(int j=0;j<sz[i];j++)
				printf("%d ",now=nxt[1+now][seq[i][j]]);
			puts("");
			return;
		}
	}
	puts("0");
}
int main(){
	for(int len=8;len>=1;len--){
		bg[len]=idx+1;
		for(int i=0;i<(1<<8);i++)if(__builtin_popcount(i)==len){
			vector<int>tmp;
			for(int j=0;j<8;j++)if((i>>j)&1)tmp.pb(j+1);
			do{
				int lst=0;
				++idx;
				for(int x:tmp){
					int v=(x-lst+9)%9;
					seq[idx][sz[idx]++]=v;
					lst=x;
				}
			}while(next_permutation(tmp.begin(),tmp.end()));	
		}
	}
	bg[0]=idx+1;
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	// for(int i=8;i>=1;i--) cout<<bg[i-1]-bg[i]<<" "; cout<<endl;
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}