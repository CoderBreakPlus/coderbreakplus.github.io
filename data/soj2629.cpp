// created time: 2026-04-06 19:31:09
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
inline void addmod(int &x){ if(x >= mod) x -= mod; }
inline void addmod(ll &x){ if(x >= mod) x -= mod; }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }
const ull MOD = (ll)1e18 + 3, base = 1e5;

int n;
char t[300005];
ull pw[300005];
struct Solver{
	int a[300005],ans[300005][2][2];
	char s[300005];
	struct SA{
		ull hsh[300005];
		char s[300005];
		int m,x[300005],y[300005],rk[300005],sa[300005],ht[300005],buc[300005],id;

		int f[20][300005];
		int lcp(int x,int y){
			if((x=rk[x])>(y=rk[y])) swap(x,y);
			int p=lg2(y-x++);
			return min(f[p][x],f[p][y-(1<<p)+1]);
		}
		ull gethsh(int l,int r){
			return (hsh[r]+(__int128)(MOD-hsh[l-1])*pw[r-l+1])%MOD;
		}
		void main(){
			m=127;
			for(int i=1;i<=n;i++) x[i]=s[i],buc[x[i]]++;
			for(int i=1;i<=m;i++) buc[i]+=buc[i-1];
			for(int i=n;i>=1;i--) sa[buc[x[i]]--]=i;

			for(int v=1;v<=n;v<<=1){
				id=0;
				for(int i=n-v+1;i<=n;i++) y[++id]=i;
				for(int i=1;i<=n;i++)
					if(sa[i]>v) y[++id]=sa[i]-v;

				memset(buc,0,sizeof(buc));

				for(int i=1;i<=n;i++) buc[x[i]]++;
				for(int i=1;i<=m;i++) buc[i]+=buc[i-1];
				for(int i=n;i>=1;i--) sa[buc[x[y[i]]]--]=y[i];

				swap(x,y);
				m=x[sa[1]]=1;
				for(int i=2;i<=n;i++)
					if(y[sa[i]]==y[sa[i-1]] && y[sa[i]+v]==y[sa[i-1]+v]) x[sa[i]]=m;
					else x[sa[i]]=++m;
			}
			for(int i=1;i<=n;i++) rk[sa[i]]=i;
			for(int i=1,k=0;i<=n;i++){
				if(rk[i]==1)continue;
				if(k) k--;
				while(s[i+k]==s[sa[rk[i]-1]+k]) k++;
				ht[rk[i]]=f[0][rk[i]]=k;
			}
			for(int i=1;(1<<i)<=n;i++)
				for(int j=1;j<=n-(1<<i)+1;j++)
					f[i][j]=min(f[i-1][j],f[i-1][j+(1<<i-1)]);
			for(int i=1;i<=n;i++)
				hsh[i]=((__int128)hsh[i-1]*base+s[i])%MOD;
		}
	}T0,T1;
	int lcp(int x,int y){
		return T0.lcp(x,y);
	}
	int lcs(int x,int y){
		return T1.lcp(n-x+1,n-y+1);
	}
	ull hash0(int x,int y){
		return T0.gethsh(x,y);
	}
	ull hash1(int x,int y){
		return T1.gethsh(n-y+1,n-x+1);
	}

	int cmp(int x,int y){ return T0.rk[x]<T0.rk[y]; }
	vector<tuple<int,int,int>>runs;

	void get(int l,int r){
		if(r>n||s[l]!=s[r])return;
		int r1=r+lcp(l,r)-1, l1=l-lcs(l,r)+1;
		if(r1-l1+1>=2*(r-l)) runs.pb(l1,r1,r-l);
	}
	int z[300005],ly[300005],tot;
	void lyndon(int op){
		z[0]=n+1,tot=0;
		for(int i=n;i>=1;i--){
			while(tot && cmp(i,z[tot])==op) --tot;
			ly[i]=z[tot];
			z[++tot]=i;
		}
	}

	int sum[300005];
	struct node{
		int fail,son[26];
		int len;
		int dif,slink;
	}tree[300005];
	int nodecnt,last;
	inline void init(){nodecnt=last=1;tree[0].fail=tree[1].fail=1;tree[1].len=-1;}
	inline int find(int p,int i){
		while(i-tree[p].len<1||s[i-tree[p].len-1]!=s[i])p=tree[p].fail;
		return p;
	}
	inline int insert(int p,int c,int i){
		p=find(p,i);
		if(!tree[p].son[c]){
			int v=++nodecnt;
			tree[v].fail=tree[find(tree[p].fail,i)].son[c];
			tree[p].son[c]=v;
			tree[v].len=tree[p].len+2;
			tree[v].dif=tree[v].len-tree[tree[v].fail].len;
			tree[v].slink=(tree[v].dif==tree[tree[v].fail].dif?tree[tree[v].fail].slink:tree[v].fail);
		}
		return tree[p].son[c];
	}
	void main(){
		memcpy(T0.s,s,sizeof(s));
		reverse(s+1,s+n+1);
		memcpy(T1.s,s,sizeof(s));
		reverse(s+1,s+n+1);

		T0.main(),T1.main();
		for(int op:{0,1}){
			lyndon(op);
			for(int i=1;i<=n;i++) get(i,ly[i]);
		}
		sort(runs.begin(),runs.end());
		runs.erase(unique(runs.begin(),runs.end()),runs.end());

		for(int i=1;i<=n;i++){
			addmod(ans[i][0][0] = ans[i-1][0][0] + a[i]);
		}
		for(auto [l,r,p]: runs){
			for(int i=l+2*p-1;i<=min(l+3*p-2,r);i++){
				bool bd = (hash0(i-2*p+1,i)==hash1(i-2*p+1,i));
				int add=0;
				for(int x=i;x<=r;x+=2*p){
					addmod(add += a[x-2*p+1]);
					addmod(ans[x][1][0] += add);
					if(bd) addmod(ans[x][1][1] += add);
				}
				add=0;
				for(int x=i+p;x<=r;x+=2*p){
					addmod(add += a[x-2*p+1]);
					addmod(ans[x][1][0] += add);
					if(bd) addmod(ans[x][1][1] += add);
				}
			}
		}

		init();
		for(int i=1;i<=n;i++){
			last=insert(last,s[i]-'a',i);
			for(int x=last;x;x=tree[x].slink){
				sum[x]=a[i-(tree[tree[x].slink].len+tree[x].dif)+1];
				if(tree[x].fail!=tree[x].slink)addmod(sum[x]+=sum[tree[x].fail]);
				addmod(ans[i][0][1] += sum[x]);
			}
		}


		for(int i=1;i<=n;i++){
			addmod(ans[i][1][0]+=mod-ans[i][1][1]);
			addmod(ans[i][0][1]+=mod-ans[i][1][1]);

			addmod(ans[i][0][0]+=mod-ans[i][1][1]);
			addmod(ans[i][0][0]+=mod-ans[i][1][0]);
			addmod(ans[i][0][0]+=mod-ans[i][0][1]);
		}
	}
}S0,S1;

int tp,ans[3][3];

void procedure(){
	scanf("%d%d%s",&n,&tp,t+1);
	memcpy(S0.s,t,sizeof(t));
	reverse(t+1,t+n+1);
	memcpy(S1.s,t,sizeof(t));
	pw[0]=1;
	for(int i=1;i<=n;i++) pw[i]=(__int128)pw[i-1]*base%MOD;

	for(int i=1;i<=n;i++) S0.a[i]=read();
	for(int i=n;i>=1;i--) S1.a[i]=read();
	
	S0.main(),S1.main();

	for(int i=1;i<n;i++){
		for(int a:{0,1})for(int b:{0,1})
		for(int c:{0,1})for(int d:{0,1})
			ans[a+c][b+d]=(ans[a+c][b+d]+(ull)S0.ans[i][a][b]*S1.ans[n-i][c][d])%mod;
	}
	if(tp==1){
		printf("%d\n",ans[2][2]);
	}else{
		for(int a:{0,1,2}){
			for(int b:{0,1,2}) printf("%d ",ans[a][b]);
			puts("");
		}
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