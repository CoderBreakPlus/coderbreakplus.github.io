// created time: 2026-09-15 07:22:01
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

int n,a[300005],a1[300005],m;
vector<pair<int,int>>ans;

void real_op(int x,int y){
	assert(a[x]!=a[y]);
	a[x]=a[y]=(a[x]^a[y]);
	ans.pb(x,y);
}


namespace Nozero{
	vector<pair<int,int>>vec;
	int p1,p2;
	int *a;
	int vid[300005],id[300005],pos[300005],seq[300005];
	void op(int x,int y){
		assert(a[x]!=a[y]);
		a[x]=a[y]=(a[x]^a[y]);
		vec.pb(x,y);
	}

	void three(int i,int j,int k){
		assert(i!=j&&i!=k&&j!=k);
		if(a[i]!=a[k]){
			op(j,k);
			op(i,j);
			op(j,k);
		}
		swap(seq[i],seq[k]);
		swap(pos[seq[i]],pos[seq[k]]);
	}
	void swapping(int x,int y){
		if(a[x]==a[y]){
			swap(seq[x],seq[y]);
			swap(pos[seq[x]],pos[seq[y]]);
			return;
		}
		if(x==pos[p1]) return three(pos[p1],pos[p2],y);
		if(x==pos[p2]) return three(pos[p2],pos[p1],y);
		if(y==pos[p1]) return three(pos[p1],pos[p2],x);
		if(y==pos[p2]) return three(pos[p2],pos[p1],x);

		int sx=seq[x],sy=seq[y];
		three(pos[p1],pos[p2],pos[sx]);
		three(pos[p2],pos[p1],pos[sy]);
		three(pos[p2],pos[p1],pos[sx]);
	}

	void main(int n,int *A){
		vec.clear();
		if(n<=1)return;
		a=A;
		// cout<<"n="<<n<<endl;
		// for(int i=1;i<=n;i++) cout<<a[i]<<" "; cout<<endl;
		for(int i=1;i<=n;i++)vid[i]=pos[i]=seq[i]=i;

		p1=1,p2=2;
		if(a[p1]!=a[p2])op(p1,p2);

		sort(vid+1,vid+n+1,[&](int x,int y){ return a[x]<a[y]; });

		for(int i=1;i<=n;i++) id[vid[i]]=i;

		for(int i=1;i<=n;i++)if(i!=p1&&i!=p2){
			if(pos[i]!=id[i]){
				swapping(pos[i],id[i]);
			}
		}
		for(int i=1;i<n;i++)assert(a[i]<=a[i+1]);
	}
}
int pos[300005];
void procedure(){
	n=read(), m=0;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)if(a[i]){
		a1[++m]=a[i],pos[m]=i;
	}
	// cout<<"m="<<m<<endl;
	Nozero::main(m,a1);
	ans.clear();

	for(auto [x,y]: Nozero::vec)
		real_op(pos[x], pos[y]);

	// cout<<"real_oped"<<endl;
	for(int i=1;i<=n;i++) 
		if(!a[i] && a[i-1]) real_op(i-1,i);
	printf("%d\n",(int)ans.size());
	for(auto [x,y]: ans)
		printf("%d %d\n",x,y);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	// math_init();
	for(int i=1;i<=T;i++){
		// cout<<"testcase "<<i<<endl;
		procedure();
	}
	return 0;
}