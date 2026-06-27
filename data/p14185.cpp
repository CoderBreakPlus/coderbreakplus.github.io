// created time: 2026-06-26 11:22:06
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

char s[1000005];
int n,f[1000005],sum[1000005];
struct Node{
	int fl,son[26],len,dif,slink;
}t[1000005];

int cnt,lst;
void init(){ cnt=lst=1; t[0].fl=t[1].fl=1,t[1].len=-1; }
inline int find(int p,int i){
	while(i-t[p].len<1 || s[i-t[p].len-1]!=s[i]) p=t[p].fl;
	return p;
}
inline int insert(int p,int c,int i){
	p=find(p,i);
	if(!t[p].son[c]){
		int v=++cnt;
		t[v].fl=t[find(t[p].fl,i)].son[c];
		t[p].son[c]=v;
		t[v].len=t[p].len+2;
		t[v].dif=t[v].len-t[t[v].fl].len;

		if(t[v].dif==t[t[v].fl].dif)
			t[v].slink=t[t[v].fl].slink;
		else
			t[v].slink=t[v].fl;
	}
	return t[p].son[c];
}
void procedure(){
	scanf("%s",s+1);
	n=strlen(s+1);
	init();
	f[0]=1;
	for(int i=1;i<=n;i++){
		lst=insert(lst,s[i]-'a',i);
		for(int x=lst;x;x=t[x].slink){
			sum[x]=f[i-t[t[x].slink].len-t[x].dif];
			if(t[x].fl!=t[x].slink)
				addmod(sum[x]+=sum[t[x].fl]);
			addmod(f[i]+=sum[x]);
		}
	}
	printf("%d\n",f[n]);
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