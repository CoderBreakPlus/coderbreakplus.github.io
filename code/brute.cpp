// created time: 2026-05-19 20:11:44
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
struct Node{
	int r;
	vector<int>ret;
	Node(){ r=1e9; }
}ans[200005];

bool operator< (const Node &A, const Node &B){
	return A.r<B.r;
}
vector<int>d0,d1;

int getmax(int x,int y){ return a[x]>a[y]?x:y; }
int getmin(int x,int y){ return a[x]<a[y]?x:y; }

int mx[20][200005],mn[20][200005];

int qmax(int l,int r){
	int p=lg2(r-l+1);
	return getmax(mx[p][l],mx[p][r-(1<<p)+1]);
}
int qmin(int l,int r){
	int p=lg2(r-l+1);
	return getmin(mn[p][l],mn[p][r-(1<<p)+1]);
}

#define pii pair<int,int>
void solve(int l,int r){
	if(r-l<3)return;
	int mid=(l+r)>>1;
	vector<pii>vec;
	for(int i=l;i<=r;i++)vec.pb(a[i],i);
	sort(vec.begin(),vec.end());

	{
		int L=a[mid],R=a[mid];
		int lpos=mid,rpos=mid;
		int lp=lower_bound(vec.begin(),vec.end(),(pii){a[mid],mid})-vec.begin(),rp=lp;

		priority_queue<int>qL;
		int qR=1e9;

		for(int i=mid-1;i>=l;i--){
			if(L<=a[i]&&a[i]<=R)continue;
			if(a[i]>R)R=a[i],rpos=i;
			else if(a[i]<L)L=a[i],lpos=i;
			while(lp>=0 && vec[lp].fi>L){
				if(vec[lp].se<=mid) qL.push(vec[lp].se);
				else chkmin(qR,vec[lp].se);
				lp--;
			}
			while(rp<vec.size() && vec[rp].fi<R){
				if(vec[rp].se<=mid) qL.push(vec[rp].se);
				else chkmin(qR,vec[rp].se);
				rp++;
			}
			while(!qL.empty()&&qL.top()>=i)qL.pop();
			Node tmp; tmp.r=qR, tmp.ret={qL.top(),i,lpos^rpos^i,qR};
			if(!qL.empty()) chkmin(ans[qL.top()], tmp);
		}
	}
	{
		int L=a[mid+1],R=a[mid+1];
		int lpos=mid+1,rpos=mid+1;
		int lp=lower_bound(vec.begin(),vec.end(),(pii){a[mid+1],mid+1})-vec.begin(),rp=lp;

		priority_queue<int,vector<int>,greater<int>>qR;
		int qL=0;

		for(int i=mid-1;i>=l;i--){
			if(L<=a[i]&&a[i]<=R)continue;
			if(a[i]>R)R=a[i],rpos=i;
			else if(a[i]<L)L=a[i],lpos=i;
			while(lp>=0 && vec[lp].fi>L){
				if(vec[lp].se>mid) qR.push(vec[lp].se);
				else chkmax(qL,vec[lp].se);
				lp--;
			}
			while(rp<vec.size() && vec[rp].fi<R){
				if(vec[lp].se>mid) qR.push(vec[lp].se);
				else chkmax(qL,vec[lp].se);
				rp++;
			}
			while(!qR.empty()&&qR.top()<=i)qR.pop();
			Node tmp; tmp.r=qR.top(), tmp.ret={qL,lpos^rpos^i,i,qR.top()};
			if(!qR.empty()) chkmin(ans[qL], tmp);
		}
	}
	solve(l,mid);solve(mid+1,r);
}
void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=read();

	while(q--){
		int l=read(),r=read();
		int ans=0;
		for(int i=l;i<r;i++) for(int j=i+1;j<r;j++) for(int k=j+1;k<=r;k++)
			if(!(a[i]<=a[j]&&a[j]<=a[k]) && !(a[i]>=a[j]&&a[j]>=a[k])) ans=3;

		for(int i=l;i<r;i++) for(int j=i+1;j<r;j++)
			for(int k=j+1;k<r;k++) for(int l=k+1;l<=r;l++){
				// if(i==1&&j==2&&k==7&&l==8){
				// 	cout<<a[k]<<"<"<<min(a[i],a[l])<<endl;
				// 	cout<<min(a[i],a[l])<<"<"<<a[j]<<endl;
				// }
				if(min(a[j],a[k])<min(a[i],a[l])&&max(a[i],a[l])<max(a[j],a[k]))ans=4;
			}
		printf("%d\n",ans);
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.ans","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}