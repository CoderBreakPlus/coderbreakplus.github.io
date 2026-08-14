// created time: 2026-08-14 07:49:56
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

int c,n,q,t[200005],tt[200005],cnt,fk;

int qmx[200005],hmn[200005],buc[200005];
int qs[200005];

bool is_sorted(int l,int r){if(l>r)return 1; return qs[r]-qs[l]==r-l; }

struct BIT{
	int c[200005];
	void upd(int x,int w){
		assert(x);
		while(x<=cnt){
			c[x]+=w;
			x+=(x&-x);
		}
	}
	int qry(int x){
		int ret=0;
		while(x){
			ret+=c[x];
			x-=(x&-x);
		}
		return ret;
	}
	void clr(){ memset(c,0,sizeof(c)); }
}B;
inline pair<int,int> count(int x,int v){
	int c=B.qry(cnt-v+1);
	return {c,buc[v]-c};
}
int ans0[200005],ans1[200005],ans[200005],xx[200005],yy[200005];

void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++) t[i]=tt[i]=read();
	sort(tt+1,tt+n+1);
	cnt=unique(tt+1,tt+n+1)-(tt+1);
	for(int i=1;i<=n;i++) t[i]=lower_bound(tt+1,tt+cnt+1,t[i])-tt,buc[t[i]]++;

	for(int i=cnt;i>=1;i--)buc[i]+=buc[i+1];

	qmx[1]=t[1];
	for(int i=2;i<=n;i++){
		qmx[i]=max(qmx[i-1],t[i]);
		qs[i]=qs[i-1]+(t[i-1]<=t[i]);
	}
	hmn[n+1]=cnt+1;
	hmn[n]=t[n];
	for(int i=n-1;i>=1;i--)
		hmn[i]=min(hmn[i+1],t[i]);

	auto cel = [&](int x,int y){ return (x+y-1)/y; };

	vector<int>que;
	for(int i=1;i<=q;i++){
		int x=read(),y=n-read()+1;
		if(qs[n]==n-1) ans[i]=0;
		else if(x<y){
			if(is_sorted(x+1,y-1) && qmx[x]<=hmn[x+1] && qmx[y-1]<=hmn[y]){
				ans[i]=2;
				if(is_sorted(y,n)) ans[i]--;
				if(is_sorted(1,x)) ans[i]--;
			}
			else
				ans[i]=-1;
		}else{
			if(is_sorted(1,y-1) && qmx[y-1]<=hmn[y]){
				ans[i]=1;
				continue;
			}
			if(is_sorted(x+1,n) && qmx[x]<=hmn[x+1]){
				ans[i]=1;
				continue;
			}
			que.pb(i); xx[i]=x,yy[i]=y;
			ans0[i]=ans1[i]=2;
		}
	}

	sort(que.begin(),que.end(),[&](int x,int y){ return xx[x]<xx[y]; });
	int cur=0;
	for(auto i: que){
		int x=xx[i],y=yy[i],w=x-y+1;
		while(cur<x) B.upd(cnt-t[++cur]+1,1);
		{
			auto solve = [&](int v){
				auto [c1,c2] = count(x,v);
				chkmax(ans0[i], min(2*cel(c1,w), 2*cel(n-x-c2,w)+1));
			};
			int L=hmn[x+1]+1,R=cnt,V=hmn[x+1];
			while(L<=R){
				int v=(L+R)>>1;
				auto [c1,c2] = count(x,v);
				if(cel(c1,w) > cel(n-x-c2,w)){
					V=v;
					L=v+1;
				}else
					R=v-1;
			}
			if(V>hmn[x+1]) solve(V);
			if(V<cnt) solve(V+1);
		}
	}
	B.clr();
	sort(que.begin(),que.end(),[&](int x,int y){ return yy[x]<yy[y]; });
	cur=0;
	for(auto i: que){
		int x=xx[i],y=yy[i],w=x-y+1;
		while(cur<y-1) B.upd(cnt-t[++cur]+1,1);
		{
			auto solve = [&](int v){
				auto [c1,c2] = count(y-1,v);
				swap(c1,c2); c1=n-y+1-c1,c2=y-1-c2;
				chkmax(ans1[i], min(2*cel(c1,w), 2*cel(y-1-c2,w)+1));
			};
			int L=1,R=qmx[y-1],V=qmx[y-1]+1;
			while(L<=R){
				int v=(L+R)>>1;
				auto [c1,c2] = count(y-1,v);
				swap(c1,c2); c1=n-y+1-c1,c2=y-1-c2;
				if(cel(c1,w) > cel(y-1-c2,w)){
					V=v;
					R=v-1;
				}else
					L=v+1;
			}
			if(V<=qmx[y-1]) solve(V);
			if(V>=1) solve(V-1);
		}
	}
	for(int i: que) ans[i]=min(ans0[i],ans1[i]);
	for(int i=1;i<=q;i++)
		printf("%d\n",ans[i]);
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