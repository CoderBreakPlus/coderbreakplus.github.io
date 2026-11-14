// created time: 2026-11-14 08:43:09
#include<bits/stdc++.h>
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
typedef __int128 i128;
struct CRT5 {
	static i128 norm(i128 x, i128 mod) {
		x %= mod;
		return x < 0 ? x + mod : x;
	}
	static i128 exgcd(i128 a, i128 b, i128 &x, i128 &y) {
		if (!b) {
			x = 1, y = 0;
			return a;
		}
		i128 u, v;
		i128 g = exgcd(b, a % b, u, v);
		x = v;
		y = u - a / b * v;
		return g;
	}
}crt;

int n,k,a[1000005],p[1000005],f[1000005];

int len[5][1000005],res[5][1000005];
int L[5],g[5][5];

ll M[5];
i128 period,W[5],val[5][5];

int can[5][5][5],valid[5],chosen[5];
int limit;

struct Node {
	i128 t;
	int x;
	bool operator < (const Node &o) const {
		return t < o.t;
	}
};
vector<Node> ans;

inline void keep(i128 t,int x){
	ans.pb(Node{t,x});
	if((int)ans.size()==limit){
		nth_element(ans.begin(),ans.begin()+k,ans.end());
		ans.resize(k);
	}
}

int player;

void dfs(int d,int used,i128 sum){
	int msk=valid[d]&(~used)&31;
	for(int j=0;j<d;j++)
		if(g[j][d]>1)
			msk&=can[j][chosen[j]][d];
	while(msk){
		int s=__builtin_ctz((unsigned)msk);
		msk&=msk-1;
		i128 nxt=sum+val[d][s];
		if(nxt>=period) nxt-=period;
		if(d==4){
			keep(nxt,player);
		}else{
			chosen[d]=s;
			dfs(d+1,used|(1<<s),nxt);
		}
	}
}

void write(i128 x){
	char s[50];
	int t=0;
	do{
		s[t++]=char('0'+x%10);
		x/=10;
	}while(x);
	while(t) putchar(s[--t]);
}

void procedure(){
	n=read(),k=read();
	for(int i=1;i<=5*n;i++) a[read()]=i;
	for(int i=1;i<=5*n;i++) p[i]=read();

	for(int i=1;i<=5*n;i++)
		f[i]=p[5*((i-1)%n)+(i-1)/n+1];
	for(int i=1;i<=5*n;i++) p[i]=f[i];

	memset(len,-1,sizeof(len));

	for(int i=0;i<5;i++){
		int x=a[i+1],w=0;
		do{
			res[i][x]=w++;
			x=p[x];
		}while(x!=a[i+1]);
		L[i]=w;
		do{
			len[i][x]=w;
			x=p[x];
		}while(x!=a[i+1]);
	}

	for(int i=0;i<5;i++)
		for(int j=i+1;j<5;j++)
			if(L[i]>L[j]){
				swap(L[i],L[j]);
				for(int x=1;x<=5*n;x++){
					swap(len[i][x],len[j][x]);
					swap(res[i][x],res[j][x]);
				}
			}

	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			g[i][j]=__gcd(L[i],L[j]);

	map<int,pair<int,int>> fac;
	for(int i=0;i<5;i++){
		int x=L[i];
		for(int d=2;d*d<=x;d++){
			if(x%d) continue;
			int w=1;
			while(x%d==0) x/=d,w*=d;
			if(w>fac[d].fi) fac[d]=mkp(w,i);
		}
		if(x>1 && x>fac[x].fi) fac[x]=mkp(x,i);
	}

	fill(M,M+5,1);
	for(auto [prime,v]:fac) M[v.se]*=v.fi;

	period=1;
	for(int i=0;i<5;i++) period*=M[i];

	for(int i=0;i<5;i++){
		if(M[i]==1){
			W[i]=0;
			continue;
		}
		i128 u,v,q=period/M[i];
		crt.exgcd(q%M[i],M[i],u,v);
		W[i]=q*crt.norm(u,M[i]);
	}

	limit=k+max(k,1<<12);
	ans.reserve(limit);

	for(player=1;player<=n;player++){
		int r[5][5];
		bool ok=1;

		for(int i=0;i<5;i++){
			valid[i]=0;
			for(int s=0;s<5;s++){
				int x=player+s*n;
				if(len[i][x]==-1) continue;
				valid[i]|=1<<s;
				r[i][s]=res[i][x];
			}
			if(!valid[i]){
				ok=0;
				break;
			}
		}
		if(!ok) continue;

		for(int i=0;i<5;i++)
			for(int s=0;s<5;s++)
				if(valid[i]>>s&1)
					val[i][s]=W[i]*r[i][s]%period;

		for(int i=0;i<5;i++)
			for(int j=i+1;j<5;j++){
				if(g[i][j]==1) continue;
				for(int s=0;s<5;s++){
					if(!(valid[i]>>s&1)) continue;
					int msk=0;
					for(int t=0;t<5;t++)
						if((valid[j]>>t&1) &&
						   (r[i][s]-r[j][t])%g[i][j]==0)
							msk|=1<<t;
					can[i][s][j]=msk;
				}
			}

		dfs(0,0,0);
	}
	if(ans.empty()){
		puts("-1");
		return;
	}
	if((int)ans.size()>k){
		nth_element(ans.begin(),ans.begin()+k,ans.end());
		ans.resize(k);
	}
	sort(ans.begin(),ans.end());
	int sz=ans.size();
	for(int i=0;i<k;i++){
		const Node &v=ans[i%sz];
		write(v.t+(i128)(i/sz)*period+1);
		putchar(' ');
		write(v.x);
		putchar('\n');
	}
}

int main(){
	assert(freopen("shuffle.in","r",stdin));
	assert(freopen("shuffle.out","w",stdout));
	procedure();
	return 0;
}