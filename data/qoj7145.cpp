// created time: 2026-08-25 08:07:25
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

int n,m,q,x[200005],y[200005],a[200005],b[200005];
vector<int>que[200005];
int ans[200005];


int c[400005];
void upd(int x,int w){
	while(x<=n+m){
		c[x]+=w;
		x+=(x&-x);
	}
}
int qry(int x){
	int ret=0;
	while(x){
		ret+=c[x];
		x-=(x&-x);
	}
	return ret;
}
char sa[200005],sb[200005];

void procedure(){
	n=read(),m=read(),q=read();
	scanf("%s",sa+1);
	for(int i=1;i<=n;i++)a[i]=sa[i]-'0';
	scanf("%s",sb+1);
	for(int i=1;i<=m;i++)b[i]=sb[i]-'0';

	for(int i=1;i<=q;i++){
		x[i]=read(),y[i]=read();
		que[x[i]].pb(i);
	}

	for(int o=1;o<=min(2,n);o++){
		b[0]=a[o];
		for(int i=1;i<=m;i++)
			b[i]=(!b[i-1])|(!b[i]);
		for(int id:que[o]) ans[id]=b[y[id]];
	}
	int tag=0,cur=b[1];
	for(int i=2;i<=m;i++)
		if(b[i]==b[i-1]) upd(i+n,1);

	for(int i=3;i<=n;i++){
		tag++; 
		if(!a[i]){
			if(cur==0){
				cur=1;
			}else{
				if(qry(n+3-tag)-qry(n+2-tag))upd(n+3-tag,-1);
				else upd(n+2-tag,1);
			}
		}else{
			cur^=1;
		}
		for(int id: que[i]){
			int tmp=qry(n+y[id]-tag);
			ans[id]=((cur^tmp^y[id]^1)&1);
		}
	}

	for(int i=1;i<=q;i++)
		if(ans[i]) puts("Yes");
		else puts("No");
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
