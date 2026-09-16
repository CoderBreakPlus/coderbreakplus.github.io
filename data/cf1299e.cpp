// created time: 2026-09-16 09:02:23
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

int n,a[805],pos[805],w[805],rd[805],ans[805];

mt19937_64 rnd(1233);
namespace _ans{
	int p[805];
	void init(){
		for(int i=1;i<=n;i++) p[i]=i;
		shuffle(p+1,p+n+1,rnd);
		if(p[1]>n/2) for(int i=1;i<=n;i++)p[i]=n+1-p[i];
	}
}
bool query(vector<int> vec, int ban=0){
	int sz=(int)vec.size()-!!ban; if(sz==1)return 1;
	cout<<"? "<<sz<<" ";
	for(int x: vec)if(x!=ban) cout<<rd[x]<<" "; cout<<endl;

	#ifdef LOCAL
		int sig=0;
		for(int x: vec) if(x!=ban)sig+=_ans::p[rd[x]];
		return sig%sz==0;
	#endif
	
	int x; cin>>x; return x;
}
void dream_end(){
	for(int i=1;i<=n;i++)ans[rd[i]]=a[i];
	if(ans[1]>n/2)
		for(int i=1;i<=n;i++)ans[i]=n+1-ans[i];
	cout<<"! ";
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	cout<<endl;

	#ifdef LOCAL
		for(int i=1;i<=n;i++) assert(ans[i]==_ans::p[i]);
	#endif
	exit(0);
}
void procedure(){
	cin>>n;
	_ans::init();
	for(int i=1;i<=n;i++)rd[i]=i;
	shuffle(rd+1,rd+n+1,rnd);

	for(int l=1,r=n;l<=2;l++,r--){
		if(l>r)dream_end();
		vector<int>vec;
		for(int i=1;i<=n;i++)if(!a[i])
			vec.pb(i);

		for(int i=1;i<=n;i++)if(!a[i]){
			if(query(vec,i)){
				if(!pos[l]) pos[l]=i;
				else pos[r]=i;
			}
		}
		if(l>1 && query({pos[l],pos[l-1]})) swap(pos[l],pos[r]);
		a[pos[l]]=l, a[pos[r]]=r;
	}
	if(n==4)dream_end();

	for(int i=1;i<=n;i++)if(!a[i])
		w[i]=query({i,pos[1]});

	for(int m=1;(1<<m)<=n;m++){
		for(int x=(1<<m)+1;x<=min(n,(1<<m+1));x++){ // find x
			if(2*x>n) dream_end();
			int y=n+1-x;
			vector<int>all;
			for(int i=1;i<=n;i++)if(!a[i]) all.pb(i);
			for(int i=1;i<=n;i++)if(!a[i]){
				if(w[i]%(1<<m)==x%(1<<m) && query(all,i)){
					pos[x]=i;
					break;
				}
			}
			for(int i=1;i<=n;i++)if(!a[i]&&pos[x]!=i){
				if(w[i]%(1<<m)==y%(1<<m) && query(all,i)){
					pos[y]=i;
					break;
				}
			}
			if(query({pos[x],pos[x-1]})) swap(pos[x],pos[y]);
			a[pos[x]]=x,a[pos[y]]=y;
		}

		vector<int>basis(1<<m+1);
		for(int i=1;i<=(1<<m+1);i++)basis[i%(1<<m+1)]=pos[i];
		for(int i=1;i<=n;i++)if(!a[i]){
			int tmp=basis[w[i]];
			basis[w[i]]=i;
			if(query(basis)) w[i]^=(1<<m);
			basis[w[i]%(1<<m)]=tmp;
		}
	}
	dream_end();
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