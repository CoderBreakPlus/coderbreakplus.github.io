// created time: 2026-06-13 08:45:05
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
inline int div2(int x){ return (x&1) ? ((x+mod)>>1) : (x>>1); }
const int N = 2e5 + 5;
int n,q,op[N],ql[N],qr[N],x[N],iv[N];
struct Seg{
	int l,r,w;
	Seg(){ }
	Seg(int L,int R,int W){ l=L,r=R,w=W; }
};
inline bool operator<(const Seg& A,const Seg &B){
	return A.l!=B.l?A.l<B.l:(A.r!=B.r?A.r<B.r:A.w<B.w);
}
vector<Seg>seg[N<<2];

int mp[N],pos[N],c,cc,f[25][N];
int lc[N],rc[N],ld[N],rd[N],prv[N];
int le[N],re[N],tag[N],tl[N],tr[N],nxt[N],stk[N],tp;
int get(int x,int y){ return mp[pos[x]]<mp[pos[y]]?x:y; }
int query(int l,int r){
	int p=lg2(r-l+1);
	return get(f[p][l],f[p][r-(1<<p)+1]);
}
void dfs(int x){
	if(x>c)return;
	// cout<<"dfs "<<x<<endl;
	if(!lc[x]) lc[x]=++cc;
	le[lc[x]]=le[x],re[lc[x]]=pos[x];
	dfs(lc[x]);

	if(!rc[x]) rc[x]=++cc;
	le[rc[x]]=pos[x],re[rc[x]]=re[x];
	dfs(rc[x]);
}
void dfs2(int x,vector<Seg> &V){
	if(x>c){
		if(tag[x]) V.pb(le[x],re[x],tag[x]);
		return;
	}
	int w=div2(tag[x]);
	addmod(tag[lc[x]]+=w); dfs2(lc[x],V);
	addmod(tag[rc[x]]+=w); dfs2(rc[x],V);
}
void cdq(int l,int r,int p){
	if(l==r){
		if(op[l]==1) seg[p].pb(ql[l],qr[l],1);
		return;
	}
	int mid=(l+r)>>1;
	cdq(l,mid,p<<1),cdq(mid+1,r,p<<1|1);
	// cout<<"cdq "<<l<<" "<<r<<" "<<p<<endl;
	c=0;
	for(int i=mid+1;i<=r;i++)
		if(op[i]==2&&!mp[x[i]]) mp[x[i]]=i,pos[++c]=x[i];

	seg[p]=seg[p<<1|1];
	if(!c){
		for(auto x: seg[p<<1]) seg[p].pb(x);
	}else{
		sort(pos+1,pos+c+1);
		for(int i=1;i<=c;i++) f[0][i]=i;
		for(int i=1;(1<<i)<=c;i++)
			for(int j=1;j<=c-(1<<i)+1;j++)
				f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);
		tp=0;
		for(int i=1;i<=c;i++){
			while(tp && mp[pos[stk[tp]]]>mp[pos[i]])
				nxt[stk[tp]]=i,lc[i]=stk[tp--];
			if(tp) rc[stk[tp]]=i,prv[i]=stk[tp];
			stk[++tp]=i;
		}
		for(int i=1;i<=c;i++) ld[i]=ld[prv[i]]+1;
		for(int i=c;i>=1;i--) rd[i]=rd[nxt[i]]+1;

		// cout<<"pressing"<<endl;

		int rt=stk[1];
		le[rt]=0,re[rt]=n+1;
		cc=c;
		dfs(rt);

		// cout<<"dfsed"<<endl;

		for(auto [l,r,w]: seg[p<<1]){
			int vl=upper_bound(pos+1,pos+c+1,l)-pos;
			int vr=lower_bound(pos+1,pos+c+1,r)-(pos+1);
			if(vl>vr){
				seg[p].pb(l,r,w);
				continue;
			}
			int vc=query(vl,vr);
			int prob_l=(ull)w*iv[rd[vl]-rd[vc]+1]%mod;
			int prob_r=(ull)w*iv[ld[vr]-ld[vc]+1]%mod;
			addmod(tr[vl]+=prob_l);
			addmod(tl[vr]+=prob_r);
			w=mod-div2(w);
			addmod(tr[vc]+=w),addmod(tl[vc]+=w);
			seg[p].pb(l,pos[vl],prob_l), seg[p].pb(pos[vr],r,prob_r);
		}
		for(int i=1;i<=c;i++)
			tr[nxt[i]]=(tr[nxt[i]]+2ull*tr[i])%mod, addmod(tag[rc[i]]+=tr[i]);
		for(int i=c;i>=1;i--)
			tl[prv[i]]=(tl[prv[i]]+2ull*tl[i])%mod, addmod(tag[lc[i]]+=tl[i]);
		dfs2(rt,seg[p]);
	}
	sort(seg[p].begin(),seg[p].end());
	vector<Seg>vec;
	for(auto [l,r,w]: seg[p]){
		if(vec.empty() || vec.back().l!=l || vec.back().r!=r)
			vec.pb(l,r,w);
		else
			addmod(vec[vec.size()-1].w+=w);
	}
	swap(seg[p],vec);

	// for(auto [l,r,w]:vec){
	// 	cout<<"["<<l<<","<<r<<"] = "<<w<<endl;
	// }
	for(int i=1;i<=max(c,cc);i++)
	prv[i]=nxt[i]=lc[i]=rc[i]=ld[i]=rd[i]=le[i]=re[i]=mp[pos[i]]=tag[i]=tl[i]=tr[i]=0;
}
void procedure(){
	n=read(),q=read();
	for(int i=1;i<=q;i++){
		op[i]=read();
		if(op[i]==1) ql[i]=read(),qr[i]=read();
		else x[i]=read();
	}
	cdq(1,q,1);
	int ans=0;
	for(auto [l,r,w]: seg[1])
		ans=(ans+(ull)(r-l)*w)%mod;
	printf("%d\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	iv[0]=1;
	for(int i=1;i<=100000;i++) iv[i]=div2(iv[i-1]);
	// math_init();
	while(T--) procedure();
	return 0;
}