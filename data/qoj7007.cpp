// created time: 2026-08-15
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

const int B = 300;

int n,m,op[100005],l[100005],r[100005],il[100005],ir[100005],x[100005];
ll a[100005];

int c[100005],sz;

ll vL[100005],vR[100005];
int pL[100005],pR[100005],bl[100005];

ll tag[100005],cov[100005];
int tl[100005],tr[100005];

ll getv(int x){ return cov[bl[x]]?:a[x]+tag[bl[x]]; }
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=m;i++) op[i]=read(),l[i]=read(),r[i]=read(),x[i]=read();

	for(int ql=1,qr=min(B,m);ql<=m;ql=qr+1,qr=min(ql+B-1,m)){
		c[sz=1]=1;
		for(int i=ql;i<=qr;i++){
			c[++sz]=l[i];
			if(r[i]<n)c[++sz]=r[i]+1;
			if(op[i]==3){
				c[++sz]=x[i];
				if(x[i]<n)c[++sz]=x[i]+1;
			}
		}
		sort(c+1,c+sz+1);sz=unique(c+1,c+sz+1)-(c+1);
		c[sz+1]=n+1;

		for(int i=1;i<=sz;i++){
			tl[i]=tr[i]=c[i]-1;
			tag[i]=0,cov[i]=0;

			ll val=0;
			for(int j=c[i];j<c[i+1];j++){
				bl[j]=i;
				if(a[j]>=val) vL[++tl[i]]=val=a[j],pL[tl[i]]=j;
			}
			val=0;
			for(int j=c[i+1]-1;j>=c[i];j--)
				if(a[j]>=val) vR[++tr[i]]=val=a[j],pR[tr[i]]=j;
		}
		for(int i=ql;i<=qr;i++){
			il[i]=lower_bound(c+1,c+sz+1,l[i])-c;
			ir[i]=lower_bound(c+1,c+sz+1,r[i]+1)-(c+1);

			if(op[i]==1){
				for(int j=il[i];j<=ir[i];j++)
					if(cov[j]) cov[j]+=x[i];
					else tag[j]+=x[i];
			}else if(op[i]==2){
				for(int j=il[i];j<=ir[i];j++)
					cov[j]=x[i];
			}else{
				int pos=lower_bound(c+1,c+sz+1,x[i])-c;
				int ret=(il[i]<=pos&&pos<=ir[i]);
				ll cur=getv(x[i]),val=cur;

				for(int j=pos+1;j<=ir[i];j++){
					bool cf=(j>=il[i]);
					if(cov[j]){
						if(cov[j]>=val) ret+=cf*(c[j+1]-c[j]),val=cov[j];
						else if(val==cur) ret+=cf*(c[j+1]-c[j]);
						continue;
					}
					if(val==cur){
						if(vL[tl[j]]+tag[j]<=cur) ret+=cf*(c[j+1]-c[j]);
						else{
							int t=upper_bound(vL+c[j],vL+tl[j]+1,val-tag[j])-vL;
							ret+=cf*(tl[j]-t+1+pL[t]-c[j]);
						}
					}else{
						int t=lower_bound(vL+c[j],vL+tl[j]+1,val-tag[j])-vL;
						ret+=cf*(tl[j]-t+1);
					}
					chkmax(val,vL[tl[j]]+tag[j]);
				}

				val=cur;
				for(int j=pos-1;j>=il[i];j--){
					bool cf=(j<=ir[i]);
					if(cov[j]){
						if(cov[j]>=val) ret+=cf*(c[j+1]-c[j]),val=cov[j];
						else if(val==cur) ret+=cf*(c[j+1]-c[j]);
						continue;
					}
					if(val==cur){
						if(vR[tr[j]]+tag[j]<=cur) ret+=cf*(c[j+1]-c[j]);
						else{
							int t=upper_bound(vR+c[j],vR+tr[j]+1,val-tag[j])-vR;
							ret+=cf*(tr[j]-t+1+c[j+1]-1-pR[t]);
						}
					}else{
						int t=lower_bound(vR+c[j],vR+tr[j]+1,val-tag[j])-vR;
						ret+=cf*(tr[j]-t+1);	
					}
					chkmax(val,vR[tr[j]]+tag[j]);
				}
				printf("%d\n",ret);
			}
		}

		for(int i=1;i<=sz;i++)
			if(cov[i])
				for(int j=c[i];j<c[i+1];j++) a[j]=cov[i];
			else
				for(int j=c[i];j<c[i+1];j++) a[j]+=tag[i];
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