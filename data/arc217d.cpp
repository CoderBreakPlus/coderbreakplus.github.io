#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const ll mod = 998244353;
inline ll read(){
	ll x=0, f=1; char ch=getchar();
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
inline ll INV(ll x){ return qpow(x, mod-2); };

int n,m,a[500005],f[20][500005],stk[500005],val[500005],tp;
int seq[500005],t;
int get(int x,int y){
	int ret=(a[x]==a[y]?x<y:a[x]<a[y])?x:y;
	// cout<<x<<","<<y<<" get="<<ret<<endl;
	return ret;
}

int query(int x,int y){
	// cout<<"query "<<x<<" "<<y<<endl;
	int p=lg2(y-x+1);
	int ret=get(f[p][x],f[p][y-(1<<p)+1]);
	// cout<<"ret="<<ret<<endl;
	return ret;
}
void ins(int x,int cur){
	// cout<<"add "<<x<<" cur="<<cur<<endl;
	int y=a[x]+cur;
	if(!tp || val[tp]>y) stk[++tp]=x,val[tp]=y;
}
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read(),f[0][i]=i;
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j<=n-(1<<i)+1;j++)
			f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);
	stk[tp=1]=query(1,n),val[1]=a[stk[1]];
	t=0;

	int cur=0;
	ull ans=0;
	for(int i=1;i<=m;i++){
		if(tp && i==val[tp]){
			int pos=stk[tp--];
			while(t && seq[t]>pos) cur-=a[seq[t--]];
			if(seq[t]+1<pos){
				// cout<<"during "<<seq[t]+1<<" -> "<<pos-1<<" find:\n";
				ins(query(seq[t]+1,pos-1),cur);
			}
			cur+=a[seq[++t]=pos];
			if(seq[t]+1<=n) ins(query(seq[t]+1,n),cur);
		}
		ans^=(1ull*i*cur);
		// cout<<i<<","<<cur<<endl;
		// for(int i=1;i<=tp;i++) cout<<stk[i]<<" "<<val[i]<<endl;
		// cout<<endl;
	}
	printf("%llu\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}