// created time: 2026-04-15 18:30:40
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

int n,q,p[1000005],l[1000005],r[1000005];
int stk[1000005],id[1000005],tp;
vector<int>que[1000005];
vector<int>tag[1000005];

int x[2000005],y[2000005],t,vis[2000005],ban[2000005];

struct BIT{
	ll c[1000005];
	void upd(ll x,ll w){
		while(x<=n+1){
			c[x]+=w;
			x+=(x&-x);
		}
	}
	ll qry(ll x){
		ll ret=0;
		while(x){
			ret+=c[x];
			x-=(x&-x);
		}
		return ret;
	}
	void clear(){
		for(ll i=1;i<=n+1;i++)c[i]=0;
	}
}K,B;
ll ans[1000005];

void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++)p[i]=read();

	for(int i=1;i<=q;i++){
		l[i]=read(),r[i]=read()+1;
		que[l[i]].pb(i),ans[i]=0;
	}

	stk[0]=n+1; p[n+1]=0;
	
	unordered_set<int>S;

	auto add_link = [&](int l,int r){
		// stk[x] -> stk[x-1]-1
		x[++t]=l, y[t]=r, vis[t]=ban[t]=0;
		S.emplace(t);

		int pos=2*l-r;
		if(pos>=1) tag[pos].pb(t);

		return t;
	};

	auto upd_link = [&](int i){
		vis[i]=1; S.erase(i);
		B.upd(y[i], (ll)(y[i]-x[i])*x[i]);
		K.upd(y[i], x[i]-y[i]);
	};

	auto del_link = [&](int i){
		ban[i]=1;
		if(vis[i]){
			B.upd(y[i], (ll)(x[i]-y[i])*x[i]);
			K.upd(y[i], y[i]-x[i]);
		}else{
			S.erase(i);
		}
	};

	auto calc = [](ll x){
		ll a=x/2, b=(x+1)/2;
		return a*b;
	};
	for(int i=n;i>=1;i--){
		for(int x: tag[i])
			if(!ban[x]) upd_link(x);
		while(p[i]<p[stk[tp]]){
			// assert(tp);
			del_link(id[tp--]);
		}
		stk[++tp]=i;
		id[tp]=add_link(i,stk[tp-1]);
		for(auto o: que[i]){
			ans[o]=K.qry(r[o])*i+B.qry(r[o]);

			int k=lower_bound(stk, stk+tp+1, r[o], greater<int>())-stk;

			int fr=stk[k]-i, len=r[o]-stk[k];
			if(stk[k]==i){
				ans[o]+=calc(len-1);
			}else{
				if(fr>len) ans[o]+=(ll)fr*len;
				else ans[o]+=calc(fr+len);
			}
			// cout<<"ans = "<<ans[o]<<endl;

			for(auto k: S){
				if(y[k]>r[o]) continue;
				if(x[k]==i){
					ans[o]+=calc(y[k]-x[k]-1);
					continue;
				}
				int fr=x[k]-i, len=y[k]-x[k];
				// cout<<x[k]<<"->"<<y[k]<<endl;
				// cout<<k<<" contri: "<<fr<<" "<<len<<endl;
				if(fr>len) ans[o]+=(ll)fr*len;
				else ans[o]+=calc(fr+len);
			}
		}
	}
	for(int i=1;i<=q;i++) printf("%lld\n",ans[i]),ans[i]=0;
	for(int i=0;i<=n+1;i++) que[i].clear(),tag[i].clear(),stk[i]=id[i]=0;
	t=tp=0;
	K.clear(),B.clear();
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}