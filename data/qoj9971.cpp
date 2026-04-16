// created time: 2026-04-16 07:47:15
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
const int B=450,N=500000;

int n,m,a[N+5],lf[N+5],rh[N+5],bl[N+5];

ll ans[N+5];
pair<int,int> q[N+5]; int tt;
int ql[N+5],qr[N+5];
struct BIT{
	ull b[N];int c[N],mdf[N],cnt;
	inline void upd(int x){
		mdf[++cnt]=x;
		static int y,z;y=x&63,z=x>>6;
		b[z]|=1ull<<y;
		for(++z;z<=n;z+=z&-z)++c[z];
	}
	inline int ask(int x){
		static int y,z;y=x&63,z=x>>6;
		static int res;res=__builtin_popcountll(b[z]&((y==63?0:1ull<<(y+1))-1));
		for(;z;z-=z&-z)res+=c[z];
		return res;
	}
	inline void clr(int x){
		static int z;z=x>>6;
		b[z]=0;
		for(++z;z<=n;z+=z&-z)
			if(c[z])c[z]=0;
			else break;
	}
	void clear(){
		for(int i=1;i<=cnt;i++)
			clr(mdf[i]);
		cnt=0;
	}
}bit;

int qz[500005],buc[500005];

inline bool check(int l,int r){
	return bl[l]!=bl[r+1]&&bl[l-1]!=bl[r];
}
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=0;i<=n+1;i++) rh[bl[i]=(i-1)/B+1]=i;
	for(int i=n+1;i>=0;i--) lf[bl[i]]=i;
	for(int i=1;i<=m;i++){
		int y=read();
		ql[i]=tt+1, qr[i]=tt+y;
		while(y--){
			int l=read(),r=read();
			q[++tt]={l,r};

			if(check(l,r)){
				for(int x=l;x<=rh[bl[l-1]];x++) ans[i]+=bit.ask(a[x]);
				for(int x=lf[bl[r+1]];x<=r;x++) ans[i]+=bit.ask(a[x]);
			}else
				for(int x=l;x<=r;x++) ans[i]+=bit.ask(a[x]);

			if(check(l,r)){
				for(int x=l;x<=rh[bl[l-1]];x++){
					bit.upd(a[x]);
				}
				for(int x=lf[bl[r+1]];x<=r;x++){
					bit.upd(a[x]);
				}
			}else
				for(int x=l;x<=r;x++) bit.upd(a[x]);
		}
		bit.clear();
	}

	for(int i=1;i<=bl[n];i++){
		memset(buc,0,sizeof(buc));
		for(int x=lf[i];x<=rh[i];x++) buc[a[x]]++;
		for(int x=1;x<=n;x++)buc[x]+=buc[x-1];
		for(int x=1;x<lf[i];x++) qz[x]=buc[n]-buc[a[x]];
		for(int x=rh[i]+1;x<=n;x++) qz[x]=buc[a[x]-1];

		for(int x=1;x<=n;x++) qz[x]+=qz[x-1];

		for(int j=1;j<=m;j++){
			for(int k=ql[j];k<=qr[j];k++){
				if(q[k].fi<=lf[i]&&rh[i]<=q[k].se){
					for(int l=k+1;l<=qr[j];l++){
						auto [L,R]=q[l];
						ans[j]+=qz[R]-qz[L-1];
					}
					for(int l=ql[j];l<k;l++){
						auto [L,R]=q[l];
						if(check(L,R)){
							ans[j]+=qz[R]-qz[lf[bl[R+1]]-1];
							ans[j]+=qz[rh[bl[L-1]]]-qz[L-1];
						}else{
							ans[j]+=qz[R]-qz[L-1];
						}
					}
				}
			}
		}
	}
	for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
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