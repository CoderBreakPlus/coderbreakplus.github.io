// created time: 2026-08-17 16:12:43
#include<bits/stdc++.h>
#pragma GCC optimize(3,"Ofast","inline","unroll-loops")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 1e9+7;
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

int n,m,k,t,w[100005],c[100005],ord[100005],seq[100005],d[100005];
int u[200005],v[200005];

vector<int>E[100005];

struct Info{
	int c;ll v;
	Info(){ c=0,v=-1e18; }
	Info(int cc,ll vv){ c=cc,v=vv; }
}f[105][100005],g[105][100005],ans[100005],tr[400005];
vector<int>vec[100005];

inline Info& operator+= (Info &A,const Info &B){
	if(A.v>B.v) return A;
	if(A.v==B.v)addmod(A.c+=B.c);
	else A=B;
	return A;
}
inline Info operator* (const Info &A,const Info &B){ return Info((ull)A.c*B.c%mod,A.v+B.v); }
inline Info operator+ (Info A,const Info &B){ return A+=B; }
inline Info add(Info A,ll ww){ return Info(A.c,A.v+ww); }
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)E[i].clear();
	for(int i=1;i<=n;i++){
		w[i]=read(),c[i]=read(),d[i]=0;
	}
	for(int i=1;i<=m;i++){
		u[i]=read(),v[i]=read();
		E[u[i]].pb(v[i]); d[v[i]]++;
	}
	k=read(),t=read();
	int tim=0;
	queue<int>q;
	for(int i=1;i<=n;i++)
		if(!d[i]) q.push(i);
	while(!q.empty()){
		int x=q.front();q.pop();
		seq[++tim]=x,ord[x]=tim;
		for(int y:E[x])
			if(!--d[y])q.push(y);
	}
	for(int x=1;x<=n;x++){
		w[x]%=k;
		for(int i=0;i<k;i++)
			f[i][x]=g[i][x]=Info();
		ans[x]=Info();
	}
	f[w[1]][1]=Info(1,c[1]);
	for(int i=1;i<=n;i++){
		int x=seq[i];
		for(int v=0;v<k;v++){
			for(int y:E[x]) f[(v+w[y])%k][y]+=add(f[v][x],c[y]);
		}
	}

	g[w[n]][n]=Info(1,c[n]);
	for(int i=n;i>=1;i--){
		int x=seq[i];
		for(int v=0;v<k;v++)
			for(int y:E[x]) g[(v+w[x])%k][x]+=add(g[v][y],c[x]);
	}

	for(int i=1;i<=n;i++)vec[i].clear();
	vector<Info> edge_val(m + 1, Info());
	for(int i=1;i<=m;i++){
		for(int s=0;s<k;s++){
			edge_val[i] += f[s][u[i]] * g[(t+k-s)%k][v[i]];
		}
		vec[ord[u[i]]+1].pb(i);
		vec[ord[v[i]]].pb(-i);
	}

	auto pushup = [&](int x){
		tr[x] = tr[x<<1] + tr[x<<1|1];
	};
	
	for(int i=1;i<=2*m+1;i++) tr[i]=Info();

	for(int i=1;i<=n;i++){
		int x=seq[i];
		for(int p: vec[i]){
			if(p>0){
				tr[p+m] = edge_val[p];
				for((p+=m)>>=1;p;p>>=1) pushup(p);
			}else{
				int edge_idx = -p;
				int idx = edge_idx + m;
				tr[idx] = Info();
				for(idx>>=1;idx;idx>>=1) pushup(idx);
			}
		}
		ans[x] += tr[1];
	}
	Info total_ans = f[t][n];
	for(int i=1;i<=n;i++){
		if (i == 1 || i == n) {
			puts("-1");
		} else if (ord[i] < ord[1] || ord[i] > ord[n]) {
			if (total_ans.v >= 0) printf("%lld %d\n", total_ans.v, total_ans.c);
			else puts("-1");
		} else {
			if(ans[i].v >= 0) printf("%lld %d\n", ans[i].v, ans[i].c);
			else puts("-1");
		}
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