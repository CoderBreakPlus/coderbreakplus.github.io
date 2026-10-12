// created time: 2026-10-12 18:56:44
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __uint128_t u128;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll

const ll mod = (ll)1e18 + 3;
inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
template<typename T>inline void addmod(T &x){ if(x>=mod) x-=mod; }

#define mid ((l+r)>>1)
int n,q;
ll a[200005],pw[200005],qz[200005];

ll calc(int l,int r){
	ll sum=0,div=0;
	for(int i=r;i>=l;i--){
		if((r-i)&1) sum-=(a[i]<<r-i),div-=(1ll<<r-i);
		else sum+=(a[i]<<r-i),div+=(1ll<<r-i);
	}
	return sum/div;
}
struct Info{
	int sz; ll val;
	Info(){ }
	Info(int a,ll b){ sz=a,val=b; }
}t[800005];
Info operator+ (const Info &A,const Info &B){
	return Info(A.sz+B.sz, ((u128)((B.sz&1)?mod-A.val:A.val)*pw[B.sz]+B.val)%mod);
}
void pushup(int p){ t[p]=t[p<<1]+t[p<<1|1]; }
void locate(int p,int v){ t[p]=Info(1,a[v]); }
void update(int l,int r,int x,int p){
	if(l==r) return locate(p,l);
	if(x<=mid) update(l,mid,x,p<<1);
	else update(mid+1,r,x,p<<1|1);
	pushup(p);
}
void build(int l,int r,int p){
	if(l==r){
		locate(p,l);
	}else{
		build(l,mid,p<<1),build(mid+1,r,p<<1|1);
		pushup(p);
	}
	// cout<<"here "<<l<<"->"<<r<<" "<<t[p].sz<<","<<t[p].val<<endl;
}
Info tot; bool flg;
void query(int l,int r,int ql,int qr,int p){
	if(r<ql||qr<l)return;
	if(ql<=l&&r<=qr){
		if(!flg)tot=t[p],flg=1;
		else tot=tot+t[p];
		return;
	}
	query(l,mid,ql,qr,p<<1),query(mid+1,r,ql,qr,p<<1|1);
}
ll qry(int l,int r){
	flg=0;
	query(1,n,l,r,1);
	return tot.val;
}
void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=read();
	pw[0]=1;
	for(int i=1;i<=n;i++) addmod(pw[i]=pw[i-1]*2);
	qz[0]=1;
	for(int i=1;i<=n;i++)
		addmod(qz[i]=qz[i-1]+((i&1)?mod-pw[i]:pw[i]));

	build(1,n,1);
	while(q--){
		int op=read();
		if(op==1){
			int i=read(),x=read();
			a[i]=x;
			update(1,n,i,1);
		}else{
			int l=read(),r=read();
			ll sum=0,fk=0;
			for(int i=r;i>=l;i--){
				if((r-i)&1) sum-=(ll)a[i]<<(r-i),fk-=(1ll<<r-i);
				else sum+=(ll)a[i]<<(r-i),fk+=(1ll<<r-i);
			}

			ll div=calc(l,min(l+30,r))%mod+2*mod;
			ll hsh=qry(l,r);
			// cout<<"hsh = "<<hsh<<endl;
			bool flg=0;
			for(int w=-10;w<=10;w++)
				if((u128)qz[r-l]*(div+w)%mod==hsh){flg=1;break;}
			puts(flg?"Yes":"No");
		}
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