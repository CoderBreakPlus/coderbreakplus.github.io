// created time: 2026-09-03 10:41:59
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

int n,C,x0,k[200005],L[200005],R[200005],A[200005],B[200005],c[200005],w[200005],id;
int cc[200005],tmp[400005],sz,tc;

vector<int>v[200005];
ll dp[200005];

int pos[10000005],pc;
ll ival[10000005];
const int M = 1600000;
ll t_seq[2*M];
ll *t=t_seq, *tt=t_seq+M;

void modify(int p,int l,int r,int ql,int qr,ll v){
	if(r<ql||qr<l)return;
	if(ql<=l&&r<=qr){
		if(tt[p]<v){
			pos[++pc]=p+M, ival[pc]=tt[p];
			tt[p]=v;
		}
		return;
	}
	if(t[p]<v){
		pos[++pc]=p, ival[pc]=t[p];
		t[p]=v;
	}
	int mid=(l+r)>>1;
	modify(p<<1,l,mid,ql,qr,v),modify(p<<1|1,mid+1,r,ql,qr,v);
}
ll query(int p,int l,int r,int ql,int qr){
	if(r<ql||qr<l) return -1e18;
	if(ql<=l && r<=qr) return max(t[p],tt[p]);
	int mid=(l+r)>>1;
	return max({tt[p], query(p<<1,l,mid,ql,qr), query(p<<1|1,mid+1,r,ql,qr)});
}
void undo(){ t_seq[pos[pc]]=ival[pc]; pc--; }
void undo(int low){ while(pc>low) undo(); }

vector<int> cset[200005];
vector<int> tr[800005];

void ins(int p,int l,int r,int ql,int qr,int x){
	if(r<ql||qr<l) return;
	if(ql<=l&&r<=qr){tr[p].pb(x);return;}
	int mid=(l+r)>>1;
	ins(p<<1,l,mid,ql,qr,x),ins(p<<1|1,mid+1,r,ql,qr,x);
}

void solve(int p,int l,int r){
	int bef=pc;
	for(int k: tr[p]){
		// cout<<"modify "<<A[k]<<"->"<<B[k]<<" dp = "<<dp[k]<<endl;
		modify(1,1,sz,A[k],B[k],dp[k]);
	}
	if(l==r){
		for(int k: cset[l]){
			chkmax(dp[k], w[k]+query(1,1,sz,L[k],R[k]));
			// cout<<"solving for "<<k<<" query "<<query(1,1,sz,L[k],R[k])<<endl;
		}
		return;
	}else{
		int mid=(l+r)>>1;
		solve(p<<1,l,mid),solve(p<<1|1,mid+1,r);
	}
	undo(bef);
}
void procedure(){
	n=read(),C=read(),x0=read();
	for(int i=1;i<=n;i++){
		k[i]=read();
		while(k[i]--){
			++id;
			L[id]=read(),R[id]=read(),A[id]=read(),B[id]=read(),c[id]=read(),w[id]=read();
			if(i==1&&!(L[id]<=x0&&x0<=R[id]))--id;
			else{
				v[i].pb(id);
				tmp[++sz]=L[id],tmp[++sz]=R[id];
			}
		}
	}
	sort(tmp+1,tmp+sz+1); sz=unique(tmp+1,tmp+sz+1)-(tmp+1);
	for(int i=1;i<=id;i++){
		L[i]=lower_bound(tmp+1,tmp+sz+1,L[i])-tmp;
		R[i]=upper_bound(tmp+1,tmp+sz+1,R[i])-(tmp+1);
		A[i]=lower_bound(tmp+1,tmp+sz+1,A[i])-tmp;
		B[i]=upper_bound(tmp+1,tmp+sz+1,B[i])-(tmp+1);
	}
	memset(t_seq,0xc0,sizeof(t_seq));
	memset(dp,0xc0,sizeof(dp));

	for(int k: v[1]) dp[k]=w[k];

	for(int i=2;i<=n;i++){
		// cout<<"i="<<i<<endl;
		tc=0;
		for(int k: v[i-1]) tmp[++tc]=c[k];
		for(int k: v[i]) tmp[++tc]=c[k];
		sort(tmp+1,tmp+tc+1);tc=unique(tmp+1,tmp+tc+1)-(tmp+1);

		for(int i=1;i<=tc;i++) cset[i].clear();
		for(int i=1;i<=(tc<<2);i++) tr[i].clear();

		for(int k: v[i-1]){
			cc[k]=lower_bound(tmp+1,tmp+tc+1,c[k])-tmp;
			// cout<<"bef "<<A[k]<<"->"<<B[k]<<" c="<<cc[k]<<" dp="<<dp[k]<<endl;
			ins(1,1,tc,1,cc[k]-1,k);
			ins(1,1,tc,cc[k]+1,tc,k);
		}
		for(int k: v[i]) cset[cc[k]=lower_bound(tmp+1,tmp+tc+1,c[k])-tmp].pb(k);
		solve(1,1,tc);

		// for(int k: v[i]){
		// 	cout<<"now "<<L[k]<<"->"<<R[k]<<" c="<<cc[k]<<" dp="<<dp[k]<<endl;
		// }
	}
	ll ans=-1e18;
	for(int k: v[n]) chkmax(ans,dp[k]);
	if(ans<0)puts("-1");
	else printf("%lld\n",ans);
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