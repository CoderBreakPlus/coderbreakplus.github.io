// created time: 2026-04-29 11:35:12
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
inline ll INV(ll x){ return qpow(x, mod-2); }

int n,a[100005],tmp[100005],rt[100005],cnt;
vector<int>pos[100005];
int lc[10000005],rc[10000005],val[10000005],fid;
void update(int l,int r,int x,int bef,int &p){
	p=++fid;
	val[p]=val[bef]+1;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(x<=mid) rc[p]=rc[bef],update(l,mid,x,lc[bef],lc[p]);
	else lc[p]=lc[bef],update(mid+1,r,x,rc[bef],rc[p]);
}
int query(int l,int r,int ql,int qr,int p){
	if(!p||r<ql||qr<l)return 0;
	if(ql<=l&&r<=qr)return val[p];
	int mid=(l+r)>>1;
	return query(l,mid,ql,qr,lc[p])+query(mid+1,r,ql,qr,rc[p]);
}
int s[100005],st,t[100005],tt,ans;
int calc(int x,int y){
	if(x>y)swap(x,y);
	int ret=query(1,n,x+1,y-1,rt[a[x]-1])-query(1,n,x+1,y-1,rt[a[y]-1])+query(1,n,x+1,y-1,rt[a[x]])-query(1,n,x+1,y-1,rt[a[y]])+(a[x]>a[y])-(a[x]<a[y]);
	return ret;
}

void solve(int l,int r,int ql,int qr){
	if(l>r) return;
	int mid=(l+r)>>1, jc=ql, val=calc(s[ql],t[mid]);
	for(int i=ql+1;i<=qr;i++){
		int cur=calc(s[i],t[mid]);
		if(cur>val){
			val=cur;
			jc=i;
		}
	}
	ans=max(ans, val);
	solve(l,mid-1,ql,jc);
	solve(mid+1,r,jc,qr);
}
struct BIT{
	int c[100005];
	void upd(int x,int w){
		while(x<=n){
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
}B;

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),tmp[++cnt]=a[i];
	sort(tmp+1,tmp+cnt+1);cnt=unique(tmp+1,tmp+cnt+1)-(tmp+1);

	for(int i=1;i<=n;i++)a[i]=lower_bound(tmp+1,tmp+cnt+1,a[i])-tmp,pos[a[i]].pb(i);

	ll out=0;
	for(int i=n;i>=1;i--) out+=B.qry(a[i]-1),B.upd(a[i],1);
	if(!out&&cnt==n){
		puts("1");
		return;
	}
	// cout<<"out="<<out<<endl;
	// cout<<"out="<<out<<endl;


	for(int i=1;i<=cnt;i++){
		int prv=rt[i-1],now=0;
		for(auto x:pos[i]){
			update(1,n,x,prv,now);
			prv=now,now=0;
		}
		rt[i]=prv;
	}

	// int ok=0;
	// for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++){
	// 	// ok=max(ok,calc(i,j));
	// 	if(calc(i,j)==889){
	// 		cout<<i<<" "<<j<<endl;
	// 	}
	// }
	for(int i=1;i<=n;i++)
		if(!st || a[i]>a[s[st]]) s[++st]=i;
	for(int i=n;i>=1;i--)
		if(!tt || a[i]<a[t[tt]]) t[++tt]=i;
	reverse(t+1,t+tt+1);
	solve(1,tt,1,st);

	// cout<<"ans="<<ans<<endl;
	printf("%lld\n",out-ans);
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