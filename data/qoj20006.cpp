// created time: 2026-09-15 16:30:43
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

int n,q,a[200005];
int get(int x,int y){ return a[x]>a[y]?x:y; }
struct Node{
	int ls,rs,val;
	Node(){ ls=rs=0,val=1; }
}t[200005];
int lc[200005],rc[200005];

Node operator+ (const Node &A, const Node &B){
	Node C;
	C.ls=(A.ls+(ull)B.ls*(A.val+1)+A.val)%mod;
	C.rs=((ull)A.rs*(B.val+1)+B.rs+B.val)%mod;
	C.val=((ull)A.val*B.val+A.ls+B.rs+1)%mod;
	return C;
}
struct zkw{
	int t[800005],m;
	void pushup(int p){ t[p]=get(t[p<<1],t[p<<1|1]); }
	void init(){
		m=1;
		while(m<=n+1)m<<=1;
		for(int i=1;i<=n;i++)t[m+i]=i;
		for(int i=m-1;i>=1;i--)pushup(i);
	}
	void upd(int x){
		for((x+=m)>>=1;x;x>>=1) pushup(x);
	}
	int qry(int l,int r){
		// cout<<"querying "<<l<<" "<<r<<endl;
		assert(l-1<=r);
		int mx=0;
		for(l+=m-1,r+=m+1;l^r^1;l>>=1,r>>=1){
			if(~l&1) mx=get(mx,t[l^1]);
			if( r&1) mx=get(mx,t[r^1]);
		}
		return mx;
	}
	int findnxt(int x){
		int val=a[x];
		// cout<<"finding nxt "<<x<<endl;
		for(x+=m;x;x>>=1)
			if((~x&1)&&(a[t[x+1]]>val)){
				x++;
				while(x<m){
					x=(x<<1); if(a[t[x]]<=val)x++;
				}
				// cout<<"we find "<<x-m<<endl;
				return x-m;
			}
		return n+1;
	}
	int findprv(int x){
		int val=a[x];
		for(x+=m;x;x>>=1)
			if((x&1)&&(a[t[x-1]]>val)){
				x--;
				while(x<m){
					x=(x<<1|1); if(a[t[x]]<=val)x--;
				}
				return x-m;
			}
		return 0;
	}
}T;
int build(int l,int r){
	if(l>r) return 0;
	int p=T.qry(l,r);
	t[p]=t[lc[p]=build(l,p-1)]+t[rc[p]=build(p+1,r)];
	return p;
}
int update(int l,int r,int x){
	if(l>r) return 0;
	int p=T.qry(l,r);
	if(x<=p) lc[p]=update(l,p-1,x); else lc[p]=T.qry(l,p-1);
	if(x>=p) rc[p]=update(p+1,r,x); else rc[p]=T.qry(p+1,r);
	t[p]=t[lc[p]]+t[rc[p]];
	return p;
}

void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	T.init();
	int rt=build(1,n);

	while(q--){
		int i=read(),j=read();
		int x=a[i],y=a[j];
		// cout<<"First Upd"<<endl;
		a[i]=y; T.upd(i); rt=update(1,n,i);
		// cout<<"Second Upd"<<endl;
		a[j]=x; T.upd(j); rt=update(1,n,j);
		// for(int i=1;i<=n;i++) cout<<a[i]<<" "; cout<<endl;

		int pos=T.qry(i,j),al=1,ar=1;
		// cout<<"pos="<<pos<<endl;
		bool fl=0,fr=0;

		while(i<pos){
			int nx=T.findnxt(i);
			int p=T.qry(i+1,nx-1);
			// cout<<"jumpR "<<i<<" to "<<nx<<" val="<<t[p].val<<endl;
			al=(ull)al*(t[p].val+fl)%mod;
			fl=1,i=nx;
		}
		while(j>pos){
			int pr=T.findprv(j),p=T.qry(pr+1,j-1);
			ar=(ull)ar*(t[p].val+fr)%mod;
			// cout<<"jumpL "<<j<<" to "<<pr<<" val="<<t[p].val<<endl;
			fr=1,j=pr;
		}
		printf("%llu\n",(ull)al*ar%mod);

		// cout<<t[0].ls<<" "<<t[0].rs<<" "<<t[0].val<<endl;
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