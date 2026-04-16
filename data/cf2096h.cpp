// created time: 2026-04-16 17:15:03
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
const int iv2 = (mod+1)/2;
int n,m,l[200005],r[200005];

int sta[1<<18];

inline int calc(int i,int x){
	if(x==-1) return 0;

	int p=(i?__builtin_ctz(i):m);
	int now=0;
	int sb=1-2*__builtin_parity(x&i);
	now-=(x&(1<<p));
	now+=((x&((1<<p)-1))+1);
	return now*sb;
}

int tmp[1<<18],ans[1<<18],iv[19];

int c0[1<<18],c1[1<<18];

void fwt(int *a,int M){
	for(int t=1;t<(1<<M);t<<=1)
		for(int j=0;j<(1<<M);j+=(t<<1))
			for(int k=0;k<t;k++){
				int p=a[j+k], q=a[j+k+t];
				addmod(a[j+k]=p+q);
				addmod(a[j+k+t]=p+mod-q);
			}
}
void ifwt(int *a,int M){
	for(int t=1;t<(1<<M);t<<=1)
		for(int j=0;j<(1<<M);j+=(t<<1))
			for(int k=0;k<t;k++){
				int p=a[j+k], q=a[j+k+t];
				addmod(a[j+k]=p+q);
				addmod(a[j+k+t]=p+mod-q);
			}
	for(int j=0;j<(1<<M);j++) a[j]=(ull)a[j]*iv[M]%mod;
}

int tmp0[1<<18], tmp1[1<<18];

void convolution(int M){
	for(int k=0;k<M;k++){
		for(int s=0;s<(1<<M);s+=(1<<k+1)){
			for(int i=0;i<(1<<k);i++){
				tmp0[i]=(ull)c0[s+i]*c0[s+(1<<k)+i]%mod;
				tmp0[i+(1<<k)]=(ull)c1[s+i]*c1[s+(1<<k)+i]%mod;

				tmp1[i]=(ull)c1[s+i]*c0[s+(1<<k)+i]%mod;
				tmp1[i+(1<<k)]=(ull)c0[s+i]*c1[s+(1<<k)+i]%mod;
			}
			memcpy(c0+s,tmp0,sizeof(int)<<(k+1));
			memcpy(c1+s,tmp1,sizeof(int)<<(k+1));

			if(k==M-1){
				ifwt(c0+s,k); ifwt(c0+s+(1<<k),k);
				ifwt(c1+s,k); ifwt(c1+s+(1<<k),k);
			}else{
				for(auto f:{c0+s,c1+s}){
					for(int i=0;i<(1<<k);i++){
						int p=f[i],q=f[i+(1<<k)];
						addmod(f[i]=p+q);
						addmod(f[i+(1<<k)]=p+mod-q);
					}
				}
			}
		}
	}
}
void procedure(){
	n=read(),m=read();
	memset(ans,0,sizeof(int)<<m);
	for(int i=1;i<=n;i++) l[i]=read()-1,r[i]=read();

	for(int p=0;p<=m;p++){
		int eps=0,val=1;

		int M=m-p;
		memset(sta,0,sizeof(int)<<M);

		for(int i=0;i<(1<<M);i++)c0[i]=1,c1[i]=0;
		int flg=0;
		for(int i=1;i<=n;i++){
			memset(tmp,0,sizeof(int)<<M);

			vector<pair<int,int>>fuck;
			int vr=(r[i]&((1<<p)-1))+1-(r[i]&(1<<p));
			if(vr) fuck.pb(r[i]>>p,vr+mod*(vr<0));
			
			if(~l[i]){
				int vl=-(l[i]&((1<<p)-1))-1+(l[i]&(1<<p));
				if(vl) fuck.pb(l[i]>>p,vl+mod*(vl<0));
			}

			if(!fuck.size()){ flg=1; break; }
			if(fuck.size()==1) { eps^=fuck[0].fi, val=(ull)val*fuck[0].se%mod; continue; }

			eps^=fuck[0].fi; val=(ull)val*fuck[0].se%mod;

			fuck[1].fi^=fuck[0].fi;
			fuck[1].se=(ull)fuck[1].se*INV(fuck[0].se)%mod;

			int pos=fuck[1].fi, vv=fuck[1].se;

			int v1=((ull)c0[pos]*vv+c1[pos])%mod;
			int v0=((ull)c1[pos]*vv+c0[pos])%mod;
			c0[pos]=v0, c1[pos]=v1;
		}
		if(flg)continue;
		convolution(M);
		
		for(int i=0;i<(1<<M);i++)addmod(sta[i]=c0[i]+c1[i]);
		memcpy(tmp,sta,sizeof(int)<<M);
		for(int j=0;j<(1<<M);j++)sta[j]=(ull)tmp[j^eps]*val%mod;
		fwt(sta, M);
		for(int i=0;i<(1<<M);i++)
			if(i&1) ans[i<<p]=sta[i];
		if(p==m) ans[0]=sta[0];
	}
	ifwt(ans, m);
	int x=1, out=0;


	for(int i=0;i<(1<<m);i++){
		out^=((ull)ans[i]*x%mod);
		addmod(x*=2);
	}
	printf("%d\n",out);
}
int main(){
	iv[0]=1;
	for(int i=1;i<=18;i++)
		iv[i]=(ull)iv[i-1]*iv2%mod;
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.ans","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}