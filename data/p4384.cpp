// created time: 2026-09-04 15:20:42
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

int n,q,id,l[300005],ex[300005];
char s[200005];

int buc[200005],sa[200005],ht[200005],rk[200005],x[200005],y[200005],m;
int f[20][200005];

int get(int x,int y){ return ht[x]<ht[y]?x:y; }

int lc[200005],rc[200005],fa[200005],val[200005],jp[20][200005];
ll ans[300005];

set<int>S[200005];
vector<int>qry[200005];

int query(int l,int r){
	int p=lg2(r-l++);
	return get(f[p][l], f[p][r-(1<<p)+1]);
}
int build(int l,int r){
	if(l==r){
		val[sa[l]]=n-sa[l]+1;
		return sa[l];
	}
	int p=++id, cut=query(l,r);
	// cout<<"building "<<l<<" "<<r<<" p="<<p<<endl;
	fa[lc[p]=build(l,cut-1)]=fa[rc[p]=build(cut,r)]=p;
	val[p]=ht[cut];
	return p;
}
void SA(){
	m=127;
	for(int i=1;i<=n;i++) buc[x[i]=s[i]]++;
	for(int i=1;i<=m;i++) buc[i]+=buc[i-1];
	for(int i=n;i>=1;i--) sa[buc[x[i]]--]=i;

	for(int p=1;p<n;p<<=1){
		memset(buc,0,sizeof(buc));
		for(int i=1;i<=n;i++) buc[x[i]]++;
		for(int i=1;i<=m;i++) buc[i]+=buc[i-1];

		m=0;
		for(int i=n-p+1;i<=n;i++) y[++m]=i;
		for(int i=1;i<=n;i++)
			if(sa[i]>p) y[++m]=sa[i]-p;
		for(int i=n;i>=1;i--) sa[buc[x[y[i]]]--]=y[i];

		swap(x,y);
		m=x[sa[1]]=1;
		for(int i=2;i<=n;i++)
			if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+p]==y[sa[i-1]+p]) x[sa[i]]=m;
			else x[sa[i]]=++m;
		if(m==n) break;
	}
	for(int i=1;i<=n;i++)rk[sa[i]]=i;

	for(int i=1,k=0;i<=n;i++){
		if(rk[i]==1)continue;
		if(k)k--;
		while(s[i+k]==s[sa[rk[i]-1]+k]) k++;
		ht[rk[i]]=k;
	}

	for(int i=1;i<=n;i++) f[0][i]=i;

	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j<=n-(1<<i)+1;j++)
			f[i][j]=get(f[i-1][j], f[i-1][j+(1<<i-1)]);

	id=n;
	build(1,n);
	for(int i=1;i<=id;i++){
		if(i<=n) S[i]={i};
		jp[0][i]=fa[i];
	}
	for(int i=1;i<=19;i++)
		for(int j=1;j<=id;j++) jp[i][j]=jp[i-1][jp[i-1][j]];
}

ll calc(int x){ return (ll)x*(x-1)/2; }

ll sum[200005],sum2[200005];
void solve(int x){
	if(lc[x] && rc[x]){
		solve(lc[x]), solve(rc[x]);
		if(S[rc[x]].size()>S[lc[x]].size())swap(S[lc[x]],S[rc[x]]),swap(sum[lc[x]],sum[rc[x]]),swap(sum2[lc[x]],sum2[rc[x]]);
		swap(S[x],S[lc[x]]);
		sum[x]=sum[lc[x]];
		sum2[x]=sum2[lc[x]];

		auto temp = [&](int i,int ww){
			sum[x]+=i*ww;
			sum2[x]+=calc(i)*ww;
		};
		for(int w: S[rc[x]]){
			auto it=S[x].emplace(w).fi;
			bool f0=(it!=S[x].begin()), f1=(next(it)!=S[x].end());
			if(f0) temp(*prev(it)+n-w,1);
			if(f1) temp(w+n-*next(it),1);
			if(f0&&f1) temp(*prev(it)+n-*next(it),-1);
		}
	}
	if(qry[x].empty())return;
	for(int i: qry[x]){
		int L=*S[x].begin()+ex[i]-1, R=*S[x].rbegin();

		auto sl=S[x].upper_bound(L);
		if(sl!=S[x].end() && *sl+ex[i]<=R) continue;
		auto sr=S[x].upper_bound(R-ex[i]);
		if(sl==sr){
			ans[i]-=(ll)(L-*prev(sl))*(*sr+ex[i]-R-1);
			continue;
		}
		if(L>=R){
			ans[i]=calc(n-ex[i])*S[x].size() + (calc(ex[i])-(ll)ex[i]*ex[i])*(S[x].size()-1);
			ans[i]+=sum[x]*ex[i]-sum2[x];
		}else{
			int st = *S[x].begin(), d = *next(S[x].begin())-*S[x].begin(), sz = S[x].size()-1;
			ll ret=(ll)(L-1)*(n-R);

			auto calc = [&](int i,int j){
				return (ll)(i+j)*(j-i+1)/2*d+(ll)st*(j-i+1);
			};
			auto calc0 = [&](int i,int j){
				return (ll)(i+j)*(j-i+1)/2;
			};
			auto calcs = [&](int i){
				return (ll)i*(i+1)*(2*i+1)/6;
			};
			auto calc2 = [&](int i,int j){
				int len=j-i+1;
				return st*calc(i,j)+(ll)d*st*calc0(i,j)+(ll)d*d*(calcs(j)-calcs(i-1));
			};
			auto calc3 = [&](int i,int j){
				int len=j-i+1;
				return calc2(i,j)+d*calc(i,j);
			};
			{
				int w1 = max(-1, min(sz, (R-ex[i]+1-st)/d));
				ret-=(ll)(calc(0,w1)-w1-1)*(n-R);

				int w2 = max(w1, min(sz, (L-st)/d));
				ret+=calc2(w1+1,w2);

				ret-=(n-ex[i]+1)*(calc(w1+1,w2)-w2+w1)+calc(w1+1,w2);
				ret-=(ll)(sz-w2)*(L-1)*(n-ex[i]+1)-calc(w2+1,sz)*(L-1);
			}
			sz--;
			{
				int w1 = max(-1, min(sz, (R-ex[i]+1-st)/d-1));
				ret+=(ll)(calc(0,w1)-w1-1)*(n-R);
				int w2 = max(w1, min(sz, (L-st)/d));
				ret-=calc3(w1+1,w2);

				ret+=(n-ex[i]+1)*(calc(w1+1,w2)-w2+w1)+calc(w1+2,w2+1);

				ret+=(ll)(sz-w2)*(L-1)*(n-ex[i]+1)-calc(w2+2,sz+1)*(L-1);
			}
			ans[i]-=ret;
		}
	}
}
void procedure(){
	n=read(),q=read();
	scanf("%s",s+1);

	SA();
	for(int i=1;i<=q;i++){
		l[i]=read(),ex[i]=read()-l[i]+1;
		int x=l[i];
		for(int o=19;o>=0;o--)
			if(jp[o][x] && val[jp[o][x]]>=ex[i])x=jp[o][x];
		qry[x].pb(i);
		ans[i] = (ll)(n-2)*(n-1)/2;
	}
	solve(n+1);

	for(int i=1;i<=q;i++)
		printf("%lld\n", ans[i]);
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