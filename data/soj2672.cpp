// created time: 2026-10-15 07:18:49
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

int n,x,y;
char s[20000005];

int seq[2][20000005],t[2];
int buc[2][20000005];

void procedure(){
	n=read(),x=read(),y=read();
	scanf("%s",s+1);

	int c[2]={0,0};
	for(int i=1;i<=n;i++){
		c[s[i]-'0']++;
	}
	if(!c[0]){ puts("Alice");return; }
	if(!c[1]){
		if(!y||c[0]>=2) puts("Bob");
		else puts("Alice");
		return;
	}

	if(c[0]<=c[1]){
		if(x>=c[0]-1){puts("Alice");return;}
	}else{
		if(y>=c[1]){puts("Bob");return;}
	}

	if(x>y){puts("Alice");return;}
	else if(x<y){puts("Bob");return;}

	t[0]=t[1]=0;
	for(int i=1;i<=n;i++){
		if(i==n||s[i]==s[i+1]){
			int j=i,cnt=0;
			while(j>1&&s[j-1]!=s[j])j--,cnt+=(s[j]!=s[i]);
			int o='1'-s[i];
			seq[o][++t[o]]=cnt;
		}
	}
	sort(seq[0]+1,seq[0]+t[0]+1,greater<>());
	sort(seq[1]+1,seq[1]+t[1]+1,greater<>());
	seq[0][t[0]+1]=seq[0][t[0]+2]=0;
	seq[1][t[1]+1]=seq[1][t[1]+2]=0;

	for(int i=t[0]-1;i>=1;i--)seq[0][i]+=seq[0][i+1];
	for(int i=t[1]-1;i>=1;i--)seq[1][i]+=seq[1][i+1];
	
	int L=1,R=1;
	while(1){
		L++;
		if(seq[0][L]<=x){ puts("Alice");return; }
		R++;
		if(seq[1][R]<=x){ puts("Bob");return; }
	}
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