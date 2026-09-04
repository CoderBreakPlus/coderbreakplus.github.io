// created time: 2026-09-04 09:42:05
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

int n,a[200005],b[200005],o[200005],aa[200005],bb[200005];

struct Mat{
	int a[2][2];
	Mat(){ memset(a,0,sizeof(a)); }
	Mat(int x,int y,int z,int w){ a[0][0]=x,a[0][1]=y,a[1][0]=z,a[1][1]=w; }
	int* operator[](int x){ return a[x]; }
	const int* operator[](int x)const{ return a[x]; }
};

Mat operator* (const Mat &A, const Mat &B){
	Mat C;
	for(int i:{0,1})for(int j:{0,1})for(int k:{0,1})
		C[i][k]=(C[i][k]+(ull)A[i][j]*B[j][k])%mod;
	return C;
}
struct Seg{
	Mat t[800005];
	void pushup(int p){
		t[p]=t[p<<1]*t[p<<1|1];
	}
	void update(int p,int l,int r,int x,Mat w){
		if(l==r){
			t[p]=w;
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid)update(p<<1,l,mid,x,w);
		else update(p<<1|1,mid+1,r,x,w);
		pushup(p);
	}
	Mat query(int p,int l,int r,int ql,int qr){
		if(r<ql||qr<l) return Mat(1,0,0,1);
		if(ql<=l && r<=qr) return t[p];
		int mid=(l+r)>>1;
		return query(p<<1,l,mid,ql,qr)*query(p<<1|1,mid+1,r,ql,qr);
	}
}S0,S1;

int sb[200005],c[400005];
void upd(int x,int w){
	while(x<=2*n){
		c[x]+=w;
		x+=(x&-x);
	}
}
int qry(int x){
	int ret=0;
	while(x){
		ret+=c[x];
		x-=(x&-x);
	}
	return ret;
}
void upd_one(int i,int j){
	if(j>n||j<1)return;
	int cnt=sb[j]+(j<i);
	Mat now(cnt,0,0,cnt);

	S0.update(1,1,n,j,now);

	int oo=a[j]<b[i];	
	now[0][oo]++,now[1][oo]++;

	S1.update(1,1,n,j,now);
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++){
		o[i]=i;
		a[i]=aa[i]=read(),b[i]=bb[i]=read();
		if(a[i]>b[i])swap(a[i],b[i]),swap(aa[i],bb[i]);
	}
	sort(o+1,o+n+1,[&](int x,int y){ return b[x]>b[y]; });
	for(int i=1;i<=n;i++) a[i]=aa[o[i]],b[i]=bb[o[i]];

	for(int i=1;i<=n;i++){
		sb[i]=qry(b[i]-1);
		upd(a[i],1);
	}
	int ans=0;
	for(int j=1;j<=n;j++)upd_one(1,j);

	vector<int>vec;
	for(int j=1;j<=n;j++)vec.pb(j);
	sort(vec.begin(),vec.end(),[&](int x,int y){ return a[x]<a[y]; });

	for(int i=1;i<=n;i++){
		int x = lower_bound(b+1,b+n+1,a[i],greater<>())-(b+1);
		addmod(ans += (Mat(1,0,0,0)*S1.query(1,1,n,1,i-1)*S1.query(1,1,n,i+1,x)*S0.query(1,1,n,x+1,n))[0][0]);
		if(i<n){
			upd_one(i+1, i);
			while(!vec.empty() && a[vec.back()]>b[i+1]){
				upd_one(i+1, vec.back());
				vec.pop_back();
			}
		}
	}
	printf("%d\n",ans);
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