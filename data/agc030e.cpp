// created time: 2026-09-29 13:51:57
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

int n; char s[5005],t[5005];
int a[5005],ca,b[5005],cb,tmp[5005],d[5005],cd;

void procedure(){
	n=read();
	scanf("%s%s",s+1,t+1);

	int c1=0,c2=0;
	for(int i=1;i<=n;i++)
		if(s[i]==s[i-1])a[ca]++; else a[++ca]=1;
	for(int i=1;i<=n;i++)
		if(t[i]==t[i-1])b[cb]++; else b[++cb]=1;
	if(n<=2){
		int ans=0;
		for(int i=1;i<=n;i++)ans+=(s[i]!=t[i]);
		printf("%d\n",ans);return;
	}

	for(int i=1;i<=ca;i++)if(a[i]==1)c1++;else c2++;
	int ans = 2e9;

	int add = cb-ca;
	for(int i=-n;i<=n;i++){
		if((i^(s[1]!=t[1]))&1) continue;
		int j=add-i,op=0;
		auto do_left = [&](int sz){
			if(i<0){
				int res=-2*i;
				for(int x=1;x<=sz;x++)
					if(tmp[x]==1&&res) res--,tmp[x]=0,op+=x-1;
				op-=i*(i+1);
				return res==0;
			}else{
				int res=i,tot=0;
				for(int x=1;x<=sz;x++)
					if(tmp[x]==2&&res) res--,tmp[x]=0,op+=x+tot,tot++;
				return res==0;
			}
		};
		auto do_right = [&](int sz){
			if(j<0){
				int res=-2*j;
				for(int x=sz;x>=1;x--)
					if(tmp[x]==1&&res) res--,tmp[x]=0,op+=sz-x;
				op-=j*(j+1);
				return res==0;
			}else{
				int res=j,tot=0;
				for(int x=sz;x>=1;x--)
					if(tmp[x]==2&&res) res--,tmp[x]=0,op+=sz-x+tot+1,tot++;
				return res==0;
			}
		};

		auto fuck_in = [&](int i){
			if(i<0) for(int x=1;x<=-i;x++) d[++cd]=2;
			else for(int x=1;x<=2*i;x++) d[++cd]=1;
		};


		for(int x=1;x<=ca;x++) tmp[x]=a[x];
		if(do_left(ca)){
			int sz=ca; cd=0;
			fuck_in(i);
			for(int x=1;x<=sz;x++)if(tmp[x])d[++cd]=tmp[x];
			for(int x=1;x<=cd;x++)tmp[x]=d[x];

			if(do_right(cd)){
				int sz=cd; cd=0;
				for(int x=1;x<=sz;x++)if(tmp[x])d[++cd]=tmp[x];
				fuck_in(j);
				int now=0;
				for(int x=1;x<=cb;x++){
					if(b[x]==1)now++;
					if(d[x]==1)now--;
					op+=abs(now);
				}
				chkmin(ans, op);
			}
		}

		op=0;
		for(int x=1;x<=ca;x++) tmp[x]=a[x];
		if(do_right(ca)){
			int sz=ca; cd=0;
			for(int x=1;x<=sz;x++)if(tmp[x])d[++cd]=tmp[x];
			fuck_in(j);
			for(int x=1;x<=cd;x++)tmp[x]=d[x];

			if(do_left(cd)){
				int sz=cd; cd=0;
				fuck_in(i);
				for(int x=1;x<=sz;x++)if(tmp[x])d[++cd]=tmp[x];
				int now=0;
				for(int x=1;x<=cb;x++){
					if(b[x]==1)now++;
					if(d[x]==1)now--;
					op+=abs(now);
				}
				chkmin(ans, op);
			}
		}
	}

	printf("%d\n", ans);
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