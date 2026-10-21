// created time: 2026-10-21 09:11:50
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

int n,m,x[200005],a[200005],b[200005],seq[200005],ord[200005];

struct zkw{
	int M,t[800005];
	void init(){
		M=1;
		while(M+1<=m)M<<=1;
		fill(t+1,t+2*M+2,0x3f3f3f3f);
	}
	void pushup(int x){ t[x]=min(t[x<<1],t[x<<1|1]); }
	void upd(int x,int w){ for(t[x+=M]=w;x>1;) pushup(x>>=1); }
	int qry(int l,int r){
		int ret=0x3f3f3f3f;
		for(l+=M-1,r+=M+1;l+1<r;l>>=1,r>>=1){
			if(~l&1) chkmin(ret,t[l^1]);
			if( r&1) chkmin(ret,t[r^1]);
		}
		return ret;
	}
}T;
#define mid ((l+r)>>1)
struct Seg{
	int cnt[1600005],tag[1600005];
	void init(){
		memset(cnt,0,sizeof(int)*8*n);
		memset(tag,0,sizeof(int)*8*n);
	}
	void pushup(int p){
		tag[p]=(cnt[p]>0||(tag[p<<1]&&tag[p<<1|1]));
	}
	void update(int l,int r,int ql,int qr,int v,int p){
		if(r<ql||qr<l) return;
		if(ql<=l&&r<=qr) return cnt[p]+=v,pushup(p);
		update(l,mid,ql,qr,v,p<<1),update(mid+1,r,ql,qr,v,p<<1|1);
		pushup(p);
	}
	int queryL(int l,int r,int ql,int qr,int p){
		if(tag[p]) return max(0,min(r,qr)-max(l,ql)+1);
		if(r<ql||qr<l||l==r) return 0;

		int rsz=max(0,min(r,qr)-max(mid+1,ql)+1);
		int val=queryL(mid+1,r,ql,qr,p<<1|1);
		if(val<rsz) return val;
		else return queryL(l,mid,ql,qr,p<<1)+rsz;
	}
	int queryR(int l,int r,int ql,int qr,int p){
		if(tag[p]) return max(0,min(r,qr)-max(l,ql)+1);
		if(r<ql||qr<l||l==r) return 0;

		int lsz=max(0,min(mid,qr)-max(l,ql)+1);
		int val=queryR(l,mid,ql,qr,p<<1);
		if(val<lsz) return val;
		else return lsz+queryR(mid+1,r,ql,qr,p<<1|1);
	}
	bool cover(int l,int r,int ql,int qr,int p){
		if(r<ql||qr<l||tag[p]) return 1;
		if(ql<=l&&r<=qr) return 0;
		return cover(l,mid,ql,qr,p<<1)&&cover(mid+1,r,ql,qr,p<<1|1);
	}
}S;

int ans[200005];
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		x[i]=read(),a[i]=read(),b[i]=read();
		seq[i]=i;
	}
	T.init(),S.init();
	sort(seq+1,seq+m+1,[&](int x,int y){return a[x]<a[y];});
	for(int i=1;i<=m;i++)ord[seq[i]]=i,seq[i]=a[seq[i]];

	for(int l=1,r=1;l<=m;l++){
		while(r<=m){
			if(x[r]){
				if(S.cover(1,n,a[r],b[r],1))break; 
				T.upd(ord[r],b[r]);
			}else{
				int vl=a[r]-S.queryL(1,n,1,a[r]-1,1);
				int vr=b[r]+S.queryR(1,n,b[r]+1,n,1);
				int pos=lower_bound(seq+1,seq+m+1,vl)-seq;

				if(T.qry(pos,m)<=vr) break;
				S.update(1,n,a[r],b[r],1,1);
			}
			++r;
		}
		ans[l]=r;
		if(x[l]) T.upd(ord[l],0x3f3f3f3f);
		else S.update(1,n,a[l],b[l],-1,1);
	}

	int q=read();
	while(q--){
		int l=read(),r=read();
		puts(r<ans[l]?"YES":"NO");
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