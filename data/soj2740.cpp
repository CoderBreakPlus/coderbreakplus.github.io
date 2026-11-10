// created time: 2026-11-10 18:43:26
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
const int M=60;

int n,ord[M+5],buc[M+5];
ull a[1000005],b[M+5],msk[M+5];
int pos[M+5],id[M+5],vid[M+5];

int pre[1000005];
void procedure(){
	n=read();
	ll ans=0;
	int lst=0,tl=0;
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(!a[i]){
			ans+=(++lst);
			continue;
		}
		int x=-1,p=0;
		for(int o=0;o<=M;o++)
			if(!buc[o]){ x=o;break; }

		ull val=a[i],_msk=(1ull<<x);
		ord[++tl]=i; buc[x]=i;

		// msk: 所代表的线性基编号集合
		// pos: 上一个代替位置
		// id: 当前点集对应的集合的最小编号点
		// buc[id[o]] 对应的是原序列真实位置 

		bool ins=0;
		for(int o=0;o<=M;o++){
			if((~val>>o)&1)continue;
			if(!b[o]){
				b[o]=val,msk[o]=_msk,id[o]=x,pos[o]=p;
				ins=1; break;
			}else{
				if(buc[x]>buc[id[o]])
					swap(b[o],val),swap(msk[o],_msk),swap(id[o],x),swap(pos[o],p);
				val^=b[o],_msk^=msk[o];
			}
		}
		if(!ins){
			for(int o=0;o<=M;o++)
				if(msk[o]>>x&1) msk[o]^=_msk;
			_msk^=(1ull<<x);
			for(int o=0;o<=M;o++)
				if(b[o]) vid[id[o]]=o;
			for(int o=0;o<=M;o++)if(_msk>>o&1)
				chkmax(pos[vid[o]],buc[x]);
			remove(ord+1,ord+tl+1,buc[x]); tl--;
			buc[x]=0;
		}
		for(int o=0;o<=M;o++)if(b[o]){
			pre[buc[id[o]]]=pos[o];
		}

		int mx=i; lst=0;
		for(int j=tl;j>=1;j--){
			int x=ord[j],y=pre[x];
			chkmin(mx,y);
			lst+=max(0,mx-ord[j-1]);
		}
		ans+=lst;
	}
	printf("%lld\n",ans);
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