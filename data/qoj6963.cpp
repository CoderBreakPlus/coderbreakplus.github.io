// created time: 2026-08-10
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

int n,m,q,l[1000005],r[1000005];
char s[1000005],t[1000005];

namespace SAM{
	int len[1000005],fa[1000005],son[1000005][26],lst,idx;
	inline void ins(int p,int v){
		len[p]=len[lst]+1;
		while(lst&&!son[lst][v]){
			son[lst][v]=p;
			lst=fa[lst];
		}
		if(!son[lst][v]) son[lst][v]=p;
		else{
			int q=son[lst][v];
			if(len[q]==len[lst]+1){
				fa[p]=q;
			}else{
				int r=++idx;
				len[r]=len[lst]+1,fa[r]=fa[q];
				memcpy(son[r],son[q],sizeof(son[q]));
				fa[p]=fa[q]=r;
				while(son[lst][v]==q) son[lst][v]=r,lst=fa[lst];
			}
		}
		lst=p;
	}
	void clear(){
		for(int i=0;i<=idx;i++) len[i]=fa[i]=0,memset(son[i],0,sizeof(son[i]));
		lst=idx=0;
	}
}
int bor[1000005];
int sz[1000005],tt,buc[1000005];

int ext[1000005];
ll qz[1000005],cc[1000005];

void procedure(){
	n=read(),m=read(),q=read();
	scanf("%s",s+1);
	scanf("%s",t+1);
	for(int i=2;i<=n;i++){
		bor[i]=bor[i-1];
		while(bor[i]&&s[1+bor[i]]!=s[i])bor[i]=bor[bor[i]];
		if(s[1+bor[i]]==s[i])bor[i]++;
	}
	int x=bor[n];
	while(x>1) {
		sz[++tt]=n-x;
		buc[n-x]++;
		x=bor[x];
	}

	for(int i=1;i<=n;i++) buc[i]+=buc[i-1];
	SAM::idx=n-2;
	for(int i=2;i<n;i++)SAM::ins(i-1,s[i]-'a');

	int cur=0,sb=0;
	for(int i=1;i<=m;i++){
		int v=t[i]-'a';
		while(cur&&!SAM::son[cur][v])
			cur=SAM::fa[cur],sb=SAM::len[cur];
		if(SAM::son[cur][v])cur=SAM::son[cur][v],sb++;
		ext[i]=sb;
		// cout<<i<<" ext="<<ext[i]<<" "; cout<<endl;
	}

	for(int i=1;i<=m;i++) qz[i]=qz[i-1]+buc[ext[i]];

	int tl=0; ll all=0;
	for(int i=1;i<=n;i++){
		while(tl<tt && sz[tl+1]<=i) all+=sz[++tl];
		cc[i]=(ll)(i+1)*tl-all;
	}
	for(int i=1;i<=q;i++){
		l[i]=read(),r[i]=read();
		int L=l[i],R=r[i],pt=l[i]-1;
		while(L<=R){
			int mid=(L+R)>>1;
			if(mid-ext[mid]+1<l[i]) pt=mid,L=mid+1;
			else R=mid-1;
		}
		// cout<<"pt = "<<pt<<" sum = "<<qz[r[i]]<<"-"<<qz[pt]<<"+"<<cc[pt-l[i]+1]<<endl;
		printf("%lld\n",qz[r[i]]-qz[pt]+cc[pt-l[i]+1]);
	}

	tt=0;
	for(int i=1;i<=n;i++)buc[i]=0;
	SAM::clear();
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