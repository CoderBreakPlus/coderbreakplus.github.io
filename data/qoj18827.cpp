// created time: 2026-06-30 08:16:08
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
const int B = 300, N = 1e5;

int n,q,bl[N+5],fa[N+5],jp[N+5],lf[N+5],rh[N+5],tag[N+5];

bool vis[N+5];
void reconst(int x){
	vis[x]=1;
	for(int i=lf[x];i<=rh[x];i++){
		if(fa[i]<lf[x]) jp[i]=fa[i];
		else jp[i]=jp[fa[i]],vis[x]=0;
	}
}

void upd(int l,int r,int x,int a){
	chkmax(l,lf[x]),chkmin(r,rh[x]);
	if(vis[x]){
		if(l==lf[x]&&r==rh[x]) tag[x]=max((int)-1e9,tag[x]-a);
		else for(int i=l;i<=r;i++)
		fa[i]=max((int)-1e9,fa[i]-a),jp[i]=fa[i];
	}else{
		for(int i=l;i<=r;i++) fa[i]=max(1,fa[i]-a);
		reconst(x);
	}
}
int fast(int x){ return max(1,jp[x]+tag[bl[x]]); }
int slow(int x){ return max(1,fa[x]+tag[bl[x]]); }
void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++) rh[bl[i]=(i-1)/B+1]=i,fa[i]=i-1;
	for(int i=n;i>=1;i--) lf[bl[i]]=i;

	for(int i=1;i<=bl[n];i++)reconst(i);

	// auto fuck = [&](){
	// 	cnt++;
	// 	if(cnt%10000==0) cout<<cnt<<endl;
	// 	return void();
	// };
	while(q--){
		int op=read();
		if(op==1){
			int p=read(),a=read();
			for(int i=bl[p];i<=bl[n];i++) upd(p,n,i,a);
		}else{
			int x=read(),y=read();
			while(x!=y){
				// fuck();
				if(bl[x] != bl[y]){
					if(bl[x] < bl[y]) swap(x,y);
					x = fast(x);
				}else{
					int fx=fast(x),fy=fast(y);
					if(fx!=fy) x=fx,y=fy;
					else while(x!=y){
						// fuck();
						if(x<y) swap(x,y);
						x=slow(x);
					}
				}
			}
			printf("%d\n",x);
		}
	}
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