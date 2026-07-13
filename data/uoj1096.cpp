// created time: 2026-07-11 11:06:59
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

int c,n,x,q,q2,e;
char s[400005];
int rk[400005],id[400005];
pair<int,int> val[400005];

int w[200005];
int l[2000005],r[2000005];

ull pw[200005];

struct Node{
	int c; ull v;
	Node(){ c=v=0; }
	Node(int a,ull b){
		c=a,v=b;
	}
}t[800005];
Node ret[2000005];
inline Node operator+ (const Node &A,const Node &B){
	Node C;
	C.v=A.v+B.v*pw[A.c];
	C.c=A.c+B.c;
	return C;
}
inline void operator+= (Node &A,const Node &B){
	A.v+=B.v*pw[A.c];
	A.c+=B.c;
}
int m;
void pushup(int p){t[p]=t[p<<1]+t[p<<1|1];}
void build(){
	m=1;
	while(m<=n+1)m<<=1;
	for(int i=1;i<2*m;i++)t[i]=Node();
}
void upd(int x){
	t[x+m]=Node(1,w[x]), x+=m;
	for(x>>=1;x;x>>=1)pushup(x);
}
Node s1[105],s2[105]; int t1,t2;
Node query(int l,int r){
	t1=t2=0; Node ok;
	for(int lp=m+l-1,rp=m+r+1;lp^rp^1;lp>>=1,rp>>=1){
		if(~lp&1) s1[++t1]=t[lp^1];
		if(rp&1) s2[++t2]=t[rp^1];
	}
	for(int i=1;i<=t1;i++)ok+=s1[i];
	for(int i=t2;i>=1;i--)ok+=s2[i];
	return ok;
}

int ord[400005];
vector<int>qry[400005];

Node pre[200005];
bool solved[2000005];

void procedure(){	
	c=read(),n=read(),x=read(),q=read(),q2=read(),e=read();
	pw[0]=1;
	for(int i=1;i<=n;i++) pw[i]=pw[i-1]*x;
	std::mt19937 rng(e);
	auto rnd = [&](uint32_t L, uint32_t R) -> uint32_t {
		uint64_t range = (uint64_t)R - L + 1;
		uint64_t bucket = (1ULL << 32) / range;
		uint64_t limit = bucket * range;
		uint32_t v;
		do {
			v = rng();
		} while ((uint64_t)v >= limit);
		return L + (uint32_t)((uint64_t)v / bucket);
	};

	scanf("%s",s+1);
	for(int i=1;i<=n;i++)s[n+i]=s[i];
	for(int i=1;i<=2*n;i++) rk[i]=s[i];
	for(int i=1;i<=n;i++) w[i]=read();

	for(int i=1;i<=q2;i++){
		l[i]=read(),r[i]=read();
	}
	for(int i=q2+1;i<=q;i++){
		l[i]=rnd(1,n),r[i]=rnd(1,n);
		if(l[i]>r[i]) swap(l[i],r[i]);
	}

	for(int i=1;i<=q;i++) qry[l[i]].pb(i);
	for(int p=1,c=0;p*2<=n;c++){
		for(int i=1;i<=n;i++){
			val[i]={rk[i],i+p<=n?rk[i+p]:0};
		}
		for(int i=n+1;i<=2*n;i++){
			val[i]={rk[i],i-p>n?rk[i-p]:0};
		}
		for(int i=1;i<=2*n;i++)id[i]=i;
		sort(id+1,id+2*n+1,[](int x,int y){ return val[x]<val[y]; });

		int cur=1;
		for(int i=1;i<=2*n;i++){
			if(val[id[i]]!=val[id[i-1]]) rk[id[i]]=++cur;
			else rk[id[i]]=cur;
		}

		p<<=1;

		for(int i=1;i<=2*n;i++) ord[i]=i;
		sort(ord+1, ord+2*n+1, [](int x,int y){
			return rk[x]!=rk[y]?rk[x]>rk[y]:x<y;
		});                                                                                                                                                                             
		build();

		for(int o=1;o<=2*n;o++){
			int x=ord[o];
			if(x<=n){
				for(int i: qry[x]){
					if(solved[i]) continue;
					if(l[i]+p*2-2>=r[i]){
						ret[i]=pre[l[i]]+query(l[i]+p-1,min(r[i],l[i]+p*2-2));
						solved[i]=1;
					}
				}
				pre[x]+=query(x+p-1,x+p*2-2);
			}else{
				upd(x-n);
			}
		}
	}

	ull md=0;
	for(ull i=1;i<=q;i++){
		md^=ret[i].v*x+i*i*i;
	}
	printf("%llu\n",md);
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