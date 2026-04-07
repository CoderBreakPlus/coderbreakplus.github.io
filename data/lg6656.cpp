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

int n; char str[1000005];
struct SA{
	char s[1000005];
	int m,x[1000005],y[1000005],rk[1000005],sa[1000005],ht[1000005],buc[1000005],id;

	int f[20][1000005];
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
			// for(int x=sa[rk[i]-1];x<=n;x++)cout<<s[x];cout<<endl;
			// for(int x=i;x<=n;x++)cout<<s[x];cout<<endl;
			// cout<<"compare "<<sa[rk[i]-1]<<","<<i<<" ht="<<k<<endl;
		}
		for(int i=1;(1<<i)<=n;i++)
			for(int j=1;j<=n-(1<<i)+1;j++)
				f[i][j]=min(f[i-1][j],f[i-1][j+(1<<i-1)]);
	}
	int lcp(int x,int y){
		if((x=rk[x])>(y=rk[y])) swap(x,y);
		int p=lg2(y-x++);
		return min(f[p][x],f[p][y-(1<<p)+1]);
	}
}T0,T1;
int lcp(int x,int y){
	return T0.lcp(x,y);
}
int lcs(int x,int y){
	return T1.lcp(n-x+1,n-y+1);
}

int cmp(int x,int y){ return T0.rk[x]<T0.rk[y]; }
vector<tuple<int,int,int>>runs;

void get(int l,int r){
	if(r>n||str[l]!=str[r])return;
	int r1=r+lcp(l,r)-1, l1=l-lcs(l,r)+1;
	if(r1-l1+1>=2*(r-l)) runs.pb(l1,r1,r-l);
}
int z[1000005],ly[1000005],tot;
void lyndon(int op){
	z[0]=n+1,tot=0;
	for(int i=n;i>=1;i--){
		while(tot && cmp(i,z[tot])==op) --tot;
		ly[i]=z[tot];
		z[++tot]=i;
	}
}
void procedure(){
	scanf("%s",str+1);
	n=strlen(str+1);
	memcpy(T0.s,str,sizeof(str));
	reverse(str+1,str+n+1);
	memcpy(T1.s,str,sizeof(str));
	reverse(str+1,str+n+1);

	T0.main(),T1.main();
	for(int op:{0,1}){
		lyndon(op);
		for(int i=1;i<=n;i++) get(i,ly[i]);
	}
	sort(runs.begin(),runs.end());
	runs.erase(unique(runs.begin(),runs.end()),runs.end());
	printf("%d\n",(int)runs.size());
	for(auto [l,r,p]: runs){
		printf("%d %d %d\n",l,r,p);
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