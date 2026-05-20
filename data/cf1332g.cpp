// created time: 2026-05-19 20:11:44
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

int n,q,b[200005],a[200005];
struct Node{
	int r;
	vector<int>ret;
	Node(){ r=1e9; }
}ans[200005];

bool operator< (const Node &A, const Node &B){
	return A.r<B.r;
}
vector<int>d0,d1;

int mx[200005],mn[200005];
int gmax(int x,int y){ return a[x]>a[y]?x:y; }

void upd(int a,int b,int c,int d){
	// if(a==4&&b==6&&c==7&&d==8)
	// cout<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
	assert(a<b&&b<c&&c<d);
	Node tmp; tmp.r=d, tmp.ret={a,b,c,d};
	chkmin(ans[a],tmp);
}
#define pii pair<int,int>
int cnt[200005],m;
vector<pair<int,int>>vij[200005];

struct zkw{
	int n,c[200005];
	void init(int N){
		n=N;
		for(int i=1;i<=n;i++)c[i]=0;
	}
	void upd(int x,int w){
		while(x<=n)chkmax(c[x],w),x+=(x&-x);
	}
	int qry(int x){
		int ret=0;
		while(x)chkmax(ret,c[x]),x-=(x&-x);
		return ret;
	}
}tr;
void solve(int l,int r){
	if(r-l<3)return;
	int mid=(l+r)>>1;

	m=0;
	for(int i=l;i<=r;i++) cnt[++m]=b[i];
	sort(cnt+1,cnt+m+1);
	m=unique(cnt+1,cnt+m+1)-(cnt+1);

	for(int i=l;i<=r;i++) a[i]=lower_bound(cnt+1,cnt+m+1,b[i])-cnt;

	mx[mid]=mid, mx[mid+1]=mid+1;
	for(int i=mid-1;i>=l;i--) mx[i]=gmax(mx[i+1],i);
	for(int i=mid+2;i<=r;i++) mx[i]=gmax(mx[i-1],i);

	tr.init(m);
	vector<tuple<int,int,int>>cur;
	for(int i=mid+2;i<=r;i++){
		if(a[i-1]<=a[i])continue;
		cur.pb(a[i],-i,a[i-1]);
	}
	for(int j=l+1;j<=mid;j++){
		if(a[j-1]<=a[j])continue;
		cur.pb(a[j],j,a[j-1]);
	}
	sort(cur.begin(),cur.end());

	for(auto [x,y,z]:cur){
		if(y<0){
			int i=-y,j=tr.qry(a[i-1]-1);
			if(j)upd(j-1,j,i-1,i);
		}else{
			int j=y;
			tr.upd(a[j-1],j);
		}
	}
	{
		for(int i=1;i<=m;i++)vij[i].clear();
		for(int i=mid+2;i<=r;i++){
			if(a[i-1]>=a[i])continue;
			vij[a[i-1]].pb(a[i],i);
		}
		for(int j=l+1;j<=mid;j++){
			if(a[j-1]<=a[j]||a[mx[j]]<=a[j-1])continue;
			vij[a[j]].pb(a[mx[j]],-j);
		}
		for(int v=1;v<=m;v++){
			sort(vij[v].begin(),vij[v].end());
			int i = 1e9;
			for(auto [x,y]: vij[v]){
				if(y<0){
					int j=-y;
					if(i<=n)upd(j-1,j,mx[j],i);
				}else chkmin(i,y);
			}
		}
	}
	{
		for(int i=1;i<=m;i++)vij[i].clear();
		for(int i=mid+2;i<=r;i++){
			if(a[i-1]>=a[i]||a[mx[i-1]]<=a[i])continue;
			vij[a[i-1]].pb(a[mx[i-1]],-i);
		}
		for(int j=l+1;j<=mid;j++){
			if(a[j-1]<=a[j])continue;
			vij[a[j]].pb(a[j-1],j);
		}

		for(int v=1;v<=m;v++){
			sort(vij[v].begin(),vij[v].end());
			int j=0;
			for(auto [x,y]: vij[v]){
				if(y<0){
					int i=-y;
					if(j)upd(j-1,j,mx[i-1],i);
				}else chkmax(j,y);
			}
		}
	}
	solve(l,mid+1),solve(mid,r);
}
void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++){
		b[i]=read();
		if(b[i-1]>b[i]) d0.pb(i-1);
		if(b[i-1]<b[i]) d1.pb(i-1);
	}

	d0.pb(n),d1.pb(n);
	solve(1,n);
	for(int i=1;i<=n;i++)b[i]=1e9+1-b[i];
	solve(1,n);

	for(int i=n-1;i>=1;i--)chkmin(ans[i],ans[i+1]);

	for(int i=1;i<=q;i++){
		int l=read(),r=read();
		if(r-l<2){puts("0");continue;}
		int f0=*lower_bound(d0.begin(),d0.end(),l);
		int f1=*lower_bound(d1.begin(),d1.end(),l);
		// cout<<"f0="<<f0<<", f1="<<f1<<endl;

		vector<int>ret;
		if(f0<f1&&f1<r){
			ret={f0,f1,f1+1};
		}else if(f1<f0&&f0<r){
			ret={f1,f0,f0+1};
		}

		if(ans[l].r<=r)
			ret=ans[l].ret;

		printf("%d\n",(int)ret.size());
		#ifndef LOCAL
		for(int i=0;i<ret.size();i++)printf("%d%c",ret[i]," \n"[i+1==ret.size()]);
		#endif
		fflush(stdout);

		for(int i=0;i<ret.size();i++)for(int j=i+1;j<ret.size();j++)for(int k=j+1;k<ret.size();k++)
			assert(!(b[ret[i]]<=b[ret[j]] && b[ret[j]]<=b[ret[k]])),
			assert(!(b[ret[i]]>=b[ret[j]] && b[ret[j]]>=b[ret[k]]));
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