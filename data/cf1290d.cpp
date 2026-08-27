// created time: 2026-08-27 09:16:02
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

int n,k,ord[2005][2005];
vector<int>vec[2005];
int a[10005],cnt;

int buc[10005],que[1000005],hd,tl;

int query(int x){
	cnt++;
	#ifdef INTERACTIVE
		int ret=!buc[a[x]];
		buc[que[++tl]=a[x]]++;
		if(tl-hd>=k) buc[que[hd++]]--;
		// if(ret)cout<<"N"<<endl;
		// else cout<<"Y"<<endl;
		return ret;
	#endif
	#ifndef INTERACTIVE
		cout<<"? "<<x<<endl;
		char s[5];
		if(!(cin>>s))exit(0);
		return s[0]=='N';
	#endif
}

void print(int x){
	vector<int>tmp;
	for(int w: vec[x]){
		if(query(w))tmp.pb(w);
	}
	swap(vec[x],tmp);
}
void clear(){
	#ifdef INTERACTIVE
		while(hd<=tl)buc[que[tl--]]--;
	#endif
	#ifndef INTERACTIVE
		cout<<"R"<<endl;
	#endif
}
void solve(int l,int r){
	if(l==r) return;
	int mid=(l+r)>>1;
	for(int i=mid+1;i<=r;i++){
		for(int j=l,k=i;j<=mid;j++,k=(k==r?mid+1:k+1))
			print(j), print(k);
		clear();
	}
	for(int i=mid+1;i<=r;i++)
		print(i),print(l),clear();
	solve(l,mid),solve(mid+1,r);
}
void procedure(){
	cin>>n>>k;

	#ifdef INTERACTIVE
		for(int i=1;i<=n;i++)cin>>a[i];
	#endif
	for(int i=1;i<=n/k;i++)
		for(int j=(i-1)*k+1;j<=i*k;j++)vec[i].pb(j);
	solve(1,n/k);

	if(n/k==1)print(1);
	
	int ans=0;
	for(int i=1;i<=n/k;i++)ans+=vec[i].size();
	cout<<"! "<<ans<<endl;

	// cout<<"cnt="<<cnt<<endl;
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