// created time: 2026-10-10
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fi first
#define se second
#define pb emplace_back
#define mkp make_pair
template<typename T>void chkmin(T &a,T B){ a=min(a,B); }
template<typename T>void chkmax(T &a,T B){ a=max(a,B); }
inline ll read(){
	ll x=0,f=1; char ch=getchar();
	while(ch>'9'||ch<'0'){ if(ch=='-')f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*f;
}

int n,q,op[200005],x[200005],a[200005],aa[200005],p[200005],dfn[200005],sz[200005],out[200005],seq[200005],tim;
vector<int>E[200005];

struct zkw{
	int t[800005],m;
	void init(){
		m=1;
		while(m<=n+1)m<<=1;
		memset(t,0x3f,sizeof(t));
	}
	void pushup(int x){ t[x]=min(t[x<<1],t[x<<1|1]); }
	void upd(int x,int y){ for(t[x+=m]=y;x>1;) pushup(x>>=1); }
	int qry(int l,int r){
		int ret=0x3f3f3f3f;
		for(l+=m-1,r+=m+1;l+1<r;l>>=1,r>>=1){
			if(~l&1) chkmin(ret,t[l^1]);
			if( r&1) chkmin(ret,t[r^1]);
		}
		return ret;
	}
}T;
struct BIT{
	ll c[400005],N;
	void clear(int n){ N=n; fill(c+1,c+n+1,0); }
	void upd(int x,ll w){ while(x<=N) c[x]+=w,x+=(x&-x); }
	ll qry(int x){ ll ret=0; while(x) ret+=c[x],x-=(x&-x); return ret; }
}B,B1;
void init(int x){
	dfn[x]=++tim,sz[x]=1;
	for(int y:E[x]) init(y),sz[x]+=sz[y];
	out[x]=tim;
}
vector<pair<ll,ll>>vec[200005];
vector<tuple<ll,ll,ll>>opt, thing;

ll ans[200005];
ll lsh[400005],cnt;

void procedure(){
	n=read(); T.init();
	for(int i=1;i<=n;i++)a[i]=aa[i]=read();
	for(int i=2;i<=n;i++)E[p[i]=read()].pb(i);
	init(1);
	B.clear(n);

	for(int i=1;i<=n;i++){
		T.upd(dfn[i],a[i]),B.upd(dfn[i],a[i]);
	}
	q=read();
	for(int i=1;i<=q;i++){
		int op=read(),x=read();
		::op[i]=op,::x[i]=x;
		if(op==1){
			int y=read();
			vec[x].pb(i,y);
			T.upd(dfn[x],y);
			B.upd(dfn[x],y-aa[x]);
			aa[x]=y;
		}else{
			ans[i]=B.qry(out[x])-B.qry(dfn[x]-1);
			// cout<<"qry mn = "<<T.qry(dfn[x],out[x])<<endl;
			ans[i]-=T.qry(dfn[x],out[x]);
		}
	}
	// cout<<"fucked"<<endl;

	for(int i=1;i<=n;i++){
		// cout<<"node "<<i<<endl;
		cnt=0;
		lsh[++cnt]=aa[i]=a[i];
		for(auto [t,v]: vec[i]) lsh[++cnt]=v;
		for(int j: E[i]){
			lsh[++cnt]=aa[j]=a[j];
			for(auto [t,v]: vec[j]) lsh[++cnt]=v;
		}
		sort(lsh+1,lsh+cnt+1); cnt=unique(lsh+1,lsh+cnt+1)-(lsh+1);
		auto find=[&](int x){ return lower_bound(lsh+1,lsh+cnt+1,x)-lsh; };

		opt.clear();
		for(auto [t,v]: vec[i]) opt.pb(t,i,find(v));
		for(int j: E[i]) for(auto [t,v]: vec[j]) opt.pb(t,j,find(v));
		B.clear(cnt),B1.clear(cnt);

		aa[i]=find(aa[i]);
		for(int j: E[i]){
			aa[j]=find(aa[j]);
			B.upd(aa[j],1),B1.upd(aa[j],lsh[aa[j]]);
		}
		
		auto calc=[&](int x){
			ll sz=B.qry(x), val=B1.qry(x);
			return val+(ll)(E[i].size()-sz)*lsh[x];
		};

		ll cur=calc(aa[i]);
		thing.pb(1,dfn[i],-cur);
		// cout<<"cur = "<<cur<<endl;

		sort(opt.begin(),opt.end());
		for(auto [t,x,v]: opt){
			thing.pb(t,dfn[i],cur);
			if(x==i){
				thing.pb(t,dfn[i],-(cur=calc(aa[i]=v)));
			}else{
				B.upd(aa[x],-1),B1.upd(aa[x],-lsh[aa[x]]);
				aa[x]=v;
				B.upd(aa[x],1),B1.upd(aa[x],lsh[aa[x]]);
				thing.pb(t,dfn[i],-(cur=calc(aa[i])));
			}
			// cout<<"after "<<t<<" cur = "<<cur<<endl;
		}
	}
	sort(thing.begin(),thing.end(),greater<>());
	B.clear(n);
	for(int i=1;i<=q;i++){
		while(!thing.empty() && get<0>(thing.back())<=i){
			auto [a,b,c]=thing.back(); thing.pop_back();
			// cout<<"here "<<i<<" upd "<<a<<","<<b<<","<<c<<endl;
			B.upd(b,c);
		}
		if(op[i]==2){
			printf("%lld\n",ans[i]+=B.qry(out[x[i]])-B.qry(dfn[x[i]]-1));
		}
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("tree.in","r",stdin));
		assert(freopen("tree.out","w",stdout));
	#endif
	procedure();
}
