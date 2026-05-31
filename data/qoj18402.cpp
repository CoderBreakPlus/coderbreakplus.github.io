// created time: 2026-05-30 10:46:21
#pragma GCC optimize(3,"inline")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2")
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

int n,q,w[1000005],o[1000005];
int ql[1000005],qr[1000005];
char t[5];

vector<int>tr[4000005];
void ins(int l,int r,int ql,int qr,int x,int p){
	if(r<ql||qr<l) return;
	int mid=(l+r)>>1;
	if(ql<=mid && mid<qr){
		tr[p].pb(x);
		return;
	}
	ins(l,mid,ql,qr,x,p<<1),ins(mid+1,r,ql,qr,x,p<<1|1);
}
ll ans1[1000005],ans2[1000005];
vector<pair<ll,ll>>v[1000005][2];
ll s[1000005][2];

inline void repoint(int x){
	v[x][o[x]] = {{w[x], w[x]}}, v[x][o[x]^1] = {};
	s[x][o[x]] = w[x], s[x][o[x]^1] = 0;
}

inline void push(vector<pair<ll,ll>>&v, ll &s, pair<ll,ll> cur){
	s += cur.se;
	while(!v.empty() && v.back().fi < cur.fi+cur.se){
		cur.se += v.back().se;
		v.pop_back();
	}
	v.push_back(cur);
}
inline void push2(vector<pair<ll,ll>>&v, ll &s, pair<ll,ll> cur){
	s += cur.se;
	if(!v.empty() && v.back().se+v.back().fi > cur.fi){
		v[v.size()-1].se += cur.se;
	}else{
		v.push_back(cur);
	}
}
void solve(int l,int r,int p){
	if(l==r)return;
	int mid=(l+r)>>1;
	solve(l,mid,p<<1),solve(mid+1,r,p<<1|1);
	if(!tr[p].size())return;

	// cout<<"solving on "<<l<<" "<<r<<" "<<p<<endl;
	repoint(mid), repoint(mid+1);
	for(int i=mid+2;i<=r;i++){
		s[i][0]=s[i-1][0],s[i][1]=s[i-1][1];
		v[i][0]=v[i-1][0],v[i][1]=v[i-1][1];

		if(o[i]==1){ // go right
			push(v[i][1],s[i][1],{w[i],w[i]});
		}else{
			ll cur=w[i];
			while(!v[i][1].empty()){
				if(cur>v[i][1].back().fi){
					cur+=v[i][1].back().se;
					s[i][1]-=v[i][1].back().se, v[i][1].pop_back();
				}else{
					pair<ll,ll> tmp=v[i][1].back();
					s[i][1]-=v[i][1].back().se, v[i][1].pop_back();

					tmp.fi+=cur, tmp.se+=cur;
					push(v[i][1],s[i][1],tmp);
					cur=0; break;
				}
			}
			if(cur) push2(v[i][0],s[i][0],{cur,cur});
		}
	}
	for(int i=mid-1;i>=l;i--){
		s[i][0]=s[i+1][0],s[i][1]=s[i+1][1];
		v[i][0]=v[i+1][0],v[i][1]=v[i+1][1];

		if(o[i]==0){ // go left
			push(v[i][0],s[i][0],{w[i],w[i]});
		}else{
			ll cur=w[i];
			while(!v[i][0].empty()){
				if(cur>=v[i][0].back().fi){
					cur+=v[i][0].back().se;
					s[i][0]-=v[i][0].back().se, v[i][0].pop_back();
				}else{
					pair<ll,ll> tmp=v[i][0].back();
					s[i][0]-=v[i][0].back().se, v[i][0].pop_back();

					tmp.fi+=cur, tmp.se+=cur;
					push(v[i][0],s[i][0],tmp);
					cur=0; break;
				}
			}
			if(cur) push2(v[i][1],s[i][1],{cur,cur});
		}
	}
	// cout<<l<<" "<<mid<<" "<<r<<endl;
	for(int x: tr[p]){
		ans1[x]=s[ql[x]][0],ans2[x]=s[qr[x]][1];
		// cout<<ql[x]<<" -> "<<qr[x]<<endl;
		// cout<<"base on "<<s[ql[x]][0]<<" "<<s[qr[x]][1]<<endl;
		
		ll val=s[ql[x]][1]+s[qr[x]][0];

		vector<pair<ll,ll>>v1=v[ql[x]][1];

		vector<pair<ll,ll>>v2=v[qr[x]][0];
		reverse(v1.begin(),v1.end());
		reverse(v2.begin(),v2.end());

		// for(auto [x,y]: v1) cout<<x<<","<<y<<" "; cout<<endl;
		// for(auto [x,y]: v2) cout<<x<<","<<y<<" "; cout<<endl;

		while(!v1.empty() && !v2.empty()){
			if(v1.back().fi >= v2.back().fi) {
				v1[v1.size()-1].fi += v2.back().se;
				v1[v1.size()-1].se += v2.back().se;
				v2.pop_back();
			}else{
				v2[v2.size()-1].fi += v1.back().se;
				v2[v2.size()-1].se += v1.back().se;
				v1.pop_back();
			}
		}
		if(v1.empty()) ans1[x]+=val;
		else ans2[x]+=val;
	}
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++){
		w[i]=read(), scanf("%s",t);
		if(t[0]=='R') o[i]=1; 
	}
	q=read();
	for(int i=1;i<=q;i++){
		ql[i]=read(),qr[i]=read();
		if(ql[i]==qr[i]){
			if(o[ql[i]]==1)ans2[i]=w[ql[i]];
			else ans1[i]=w[ql[i]];
			continue;
		}
		ins(1,n,ql[i],qr[i],i,1);
		// cout<<"inserted "<<ql[i]<<" "<<qr[i]<<endl;
	}
	solve(1,n,1);
	for(int i=1;i<=q;i++){
		printf("%lld %lld\n",ans1[i],ans2[i]);
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