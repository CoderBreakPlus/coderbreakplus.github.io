// created time: 2026-11-23 11:40:06
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

const int N=200005, B=19;
char s[2*N],a[N],b[N];
int n,k,f[401005],sum[2][800005];
struct Node{
	int fl,son[26],len,dif,slink;
}t[2*N];
int up[2*N][B];

int cnt,lst;
void init(){ cnt=lst=1; t[0].fl=t[1].fl=1,t[1].len=-1; }
inline int find(int p,int i){
	while(i-t[p].len<1 || s[i-t[p].len-1]!=s[i]) p=t[p].fl;
	return p;
}
inline int insert(int p,int c,int i){
	p=find(p,i);
	if(!t[p].son[c]){
		int v=++cnt;
		t[v].fl=t[find(t[p].fl,i)].son[c];
		t[p].son[c]=v;
		t[v].len=t[p].len+2;
		t[v].dif=t[v].len-t[t[v].fl].len;

		if(t[v].dif==t[t[v].fl].dif)
			t[v].slink=t[t[v].fl].slink;
		else
			t[v].slink=t[v].fl;

		up[v][0]=t[v].fl;
		for(int j=1;j<B;j++)
			up[v][j]=up[up[v][j-1]][j-1];
	}
	return t[p].son[c];
}
void procedure(){
	n=read(), k=read();
	scanf("%s%s",a+1,b+1);
	if(!k){
		printf("%d\n",strcmp(a+1,b+1)==0);
		return;
	}
	for(int i=1;i<=n;i++) s[2*i-1]=a[i],s[2*i]=b[i];
	init();
	f[0]=1;
	int last=0;
	for(int i=1;i<=2*n;i++){
		int r=i/2;
		int *cur=f+r*(k+1);
		if(!(i&1)){
			if(a[r]==b[r]) copy_n(cur-(k+1),k+1,cur);
			else last=r;
		}
		lst=insert(lst,s[i]-'a',i);
		for(int x=lst;x;x=t[x].slink){
			int len=t[t[x].slink].len+t[x].dif;
			int p=i-len;
			for(int c=0;c<2;c++){
				int *g=sum[c]+x*k;
				if(t[x].fl!=t[x].slink)
					copy_n(sum[c]+t[x].fl*k,k,g);
				else
					fill_n(g,k,0);
				if(!(p&1) && (p/2)%2==c){
					int *pre=f+(p/2)*(k+1);
					for(int j=0;j<k;j++) addmod(g[j]+=pre[j]);
				}
			}
			int lim=2*(r-last);
			if((i&1) || t[x].len<=lim) continue;
			int y=x;
			if(len<=lim){
				int d=t[x].dif;
				int steps=(lim-len)/d+1;
				for(int j=0;steps;j++,steps>>=1)
					if(steps&1) y=up[y][j];
			}
			int *g=sum[r&1]+y*k;
			for(int j=0;j<k;j++) addmod(cur[j+1]+=g[j]);
		}
	}
	printf("%d\n",f[n*(k+1)+k]);
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
