// created time: 2026-05-21 09:14:20
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

int n,m,Bl,bl[100005],lf[100005],p[100005],ip[100005]; ll ans[500005],cur;
int l[500005],r[500005];
vector<int>v[100005];

int pr[100005],nx[100005],buc[100005];
int A[100005],B[100005],C[100005],V[100005],tp;

int calc(int x,int y){if(!x||!y||x==n+1||y==n+1)return 0; return max(ip[x]-ip[y],ip[y]-ip[x]);}
void link(int x,int y){
	nx[x]=y,pr[y]=x;
	// cout<<"link "<<x<<" "<<y<<endl;
}
void undo(){
	// cout<<"undo"<<endl;
	while(tp){
		cur-=V[tp];
		link(A[tp],B[tp]),link(B[tp],C[tp]);
		tp--;
	}
}
void del(int b,bool ultra=0){
	int a=pr[b],c=nx[b],val=calc(a,c)-calc(a,b)-calc(b,c);
	cur+=val;
	if(ultra)A[++tp]=a,B[tp]=b,C[tp]=c,V[tp]=val;
	link(a,c);
}
void procedure(){
	n=read(),m=read(),Bl=max(1,int(n/sqrt(m)));
	for(int i=1;i<=n;i++)ip[p[i]=read()]=i,bl[i]=(i-1)/Bl+1;
	for(int i=n;i>=1;i--)lf[bl[i]]=i;
	for(int i=1;i<=m;i++){
		l[i]=read(),r[i]=read();
		v[bl[l[i]]].pb(i);
	}
	for(int i=1;i<=bl[n];i++){
		if(v[i].empty())continue;
		memset(buc,0,sizeof(buc));
		buc[0]=buc[n+1]=1;
		for(int j=lf[i];j<=n;j++) buc[p[j]]=1;
		cur=0;

		int prv=0;
		for(int j=1;j<=n+1;j++)
			if(buc[j]){
				link(prv,j);
				cur+=calc(prv,j);
				prv=j;
			}
		sort(v[i].begin(),v[i].end(),[](int x,int y){return r[x]>r[y]; });
		int pt=n;
		for(int x:v[i]){
			while(pt>r[x]) del(p[pt--]);
			for(int w=lf[i];w<l[x];w++) del(p[w],1);
			ans[x]=cur, undo();
		}
	}
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
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