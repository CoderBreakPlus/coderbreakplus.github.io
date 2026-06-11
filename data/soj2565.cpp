// created time: 2026-06-11 13:48:18
#pragma GCC optimize(3,"inline")
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2")
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
inline uint read(){
	uint x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
inline uint lg2(uint x){ return 31^__builtin_clz(x); }
template<typename T>inline void addmod(T &x){ if(x >= mod) x -= mod; }
template<typename T>inline void chkmax(T &a,T b){ a=max(a,b); }
template<typename T>inline void chkmin(T &a,T b){ a=min(a,b); }

const int N = 1.5e6+100;
const int B = 32;
const int D = 24;
const int G = 17;

uint n,q,o,x[N],y[N],c[N],s[N],md;
uint a[D][N],pl[D][N],pr[D][N],st[D][G][N/B],pre[D][N],suf[D][N],msk[D][N];

bool vl[N],vr[N];
uint xp[N],yp[N];
void solve(uint l,uint r,uint d){
	chkmax(md,d);
	if(l==r){
		a[d][l]=c[s[l]];
		return;
	}
	uint mid=(l+r)>>1;
	solve(l,mid,d+1),solve(mid+1,r,d+1);
	for(uint i=l;i<=mid;i++)vl[s[i]]=1,vr[s[i]]=0;
	for(uint i=mid+1;i<=r;i++)vl[s[i]]=0,vr[s[i]]=1;
	inplace_merge(s+l,s+mid+1,s+r+1,[](uint a,uint b){ return x[a]<x[b]; });
	for(uint i=l;i<=r;i++){
		a[d][i]=c[s[i]];
		pl[d][i]=vl[s[i]],pr[d][i]=vr[s[i]];
		if(i>l)pl[d][i]+=pl[d][i-1],pr[d][i]+=pr[d][i-1];
		else pl[d][i]+=l-1,pr[d][i]+=mid;
	}
}

inline uint get_st(uint l,uint r,uint d){
	if(l>r)return 0;
	int p=lg2(r-l+1);
	return max(st[d][p][l],st[d][p][r-(1<<p)+1]);
}
uint get(uint l,uint r,uint d){
	if(l/B==r/B){
		uint fl=l/B*B;
		return a[d][l+__builtin_ctz(msk[d][r]>>(l-fl))];
	}
	return max({suf[d][l],pre[d][r],get_st(l/B+1,r/B-1,d)});
}
inline void query(uint l,uint r,uint ql,uint qr,uint sl,uint sr,uint d,uint &ans){
	if(sr<sl) return;	
	if(ql<=l && r<=qr){
		chkmax(ans,get(sl,sr,d));
		return;
	}
	if(get(sl,sr,d)<=ans) return;
	uint mid=(l+r)>>1;
	auto gl = [&](uint x){ if(__builtin_expect(x==l-1,0)) return l-1; return pl[d][x]; };
	auto gr = [&](uint x){ if(__builtin_expect(x==l-1,0)) return mid; return pr[d][x]; };
	if(ql<=mid)query(l,mid,ql,qr,gl(sl-1)+1,gl(sr),d+1,ans);
	if(mid<qr)query(mid+1,r,ql,qr,gr(sl-1)+1,gr(sr),d+1,ans);
}
void procedure(){
	n=read(),q=read(),o=read();
	for(uint i=1;i<=n;i++) x[i]=read(),y[i]=read(),c[i]=read(),s[i]=i;
	sort(s+1,s+n+1,[](uint a,uint b){ return y[a]<y[b]; });
	yp[0]=0;
	for(uint i=1;i<=n;i++){
		yp[i]=yp[i-1];
		while(yp[i]<n&&y[s[yp[i]+1]]<=i) ++yp[i];
	}
	solve(1,n,0);
	xp[0]=0;
	for(uint i=1;i<=n;i++){
		xp[i]=xp[i-1];
		while(xp[i]<n&&x[s[xp[i]+1]]<=i) ++xp[i];
	}
	for(int d=0;d<=md;d++){
		for(int l=0,r=B-1;l<=n;l+=B,r+=B){
			uint stk[B+5],tp=0,cur=0;
			for(int j=l;j<=r;j++){
				pre[d][j]=a[d][j];
				if(j>l)chkmax(pre[d][j],pre[d][j-1]);
				while(tp && a[d][stk[tp]]<=a[d][j])
					cur^=(1u<<(stk[tp--]-l));
				cur^=(1u<<((stk[++tp]=j)-l));
				msk[d][j]=cur;
			}
			for(int j=r;j>=l;j--){
				suf[d][j]=a[d][j];
				if(j<r)chkmax(suf[d][j],suf[d][j+1]);
			}
			st[d][0][l/B]=pre[d][r];
		}
		for(int i=1;(1<<i)<=n/B;i++)
			for(int j=0;j<=n/B-(1<<i)+1;j++)
				st[d][i][j]=max(st[d][i-1][j],st[d][i-1][j+(1<<i-1)]);
	}
	uint lst=0;
	while(q--){
		uint l=read(),r=read(),s=read(),t=read();
		if(o)l^=lst,r^=lst,s^=lst,t^=lst;
		lst=0;
		query(1,n,yp[s-1]+1,yp[t],xp[l-1]+1,xp[r],0,lst);
		printf("%u\n",lst);
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