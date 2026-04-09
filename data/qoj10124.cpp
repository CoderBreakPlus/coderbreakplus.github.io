// created time: 2026-04-09 11:02:00
// https://qoj.ac/contest/1924/problem/10124
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

char s[70];
int n,c[5000];

vector<int>v[64];

inline bool upd(int x,int r){
	bool f=1;
	for(int i: v[x]) f&=((c[i]+=r)>0);
	return f;
}

int ans,now;
char out[70],cur[70];
inline void dfs(int x){
	if(now-(n-x)>=ans) return;
	if(x==n){
		ans=now;
		memcpy(out,cur,sizeof(out));
		return;
	}

	if(s[x]!='#'){
		cur[x]='.', now--; 
		if(upd(x,-1)) dfs(x+1);
		upd(x,1), cur[x]='#', now++;
	}
	dfs(x+1);
}
void procedure(){
	scanf("%s",s);
	n=strlen(s);

	if(n==1){
		puts("1");
		puts("#");
		return;
	}
	for(int x=0;x<n;x++){
		for(int i=0;i<n;i++)
			if(i^x){
				v[x].pb(x*n+i);
				v[x].pb(i*n+x);
			}
		for(int i=-n;i<=n;i++){
			if(i==0)continue;
			unsigned a=x-i,b=x+i;
			if(max(a,b)<n){
				v[x].pb(a*n+b);
			}
		}
		sort(v[x].begin(),v[x].end());
	}
	for(int i=0;i<n;i++) upd(i,1);
	now=ans=n;
	for(int i=0;i<n;i++) out[i]=cur[i]='#';
	dfs(0);
	
	printf("%d\n",ans);
	for(int i=0;i<n;i++)putchar(out[i]);puts("");
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