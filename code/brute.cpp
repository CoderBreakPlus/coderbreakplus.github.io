// created time: 2026-10-09 11:10:25
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
const int N=3e5;

int n,p[N+5],ip[N+5];
vector<pair<int,int>>q[N+5];

int stk[N+5],tp;

int tmp[N+5],pos[N+5],qz[N+5],m,idx;
int _prv[N+5],_nxt[N+5];

ll ans[N+5];

void procedure(){
	n=read();
	int B=sqrt(n);
	for(int i=1;i<=n;i++)p[i]=read(),ip[p[i]]=i;

	idx=0;
	for(int i=1;i<=n;i++){
		int k=read();
		q[i].clear();
		while(k--) q[i].pb(read(),++idx),ans[idx]=0;
	}

	for(int i=0;i<n;i+=B){
		m=0;
		for(int j=1;j<=n;j++){
			qz[j]=qz[j-1];
			if(p[j]<=i)
				tmp[++m]=p[j],pos[m]=j,qz[j]++;
		}
		for(int i=1;i<=m;i++) _prv[i]=0,_nxt[i]=m+1;

		tp=0;
		for(int i=1;i<=m;i++){
			while(tp && tmp[stk[tp]]<tmp[i]) _nxt[stk[tp--]]=i;
			if(tp) _prv[i]=stk[tp];
			stk[++tp]=i;
		}

		int s[B+5],tl=0;
		for(int x=i+1;x<=n&&x<=i+B;x++){
			s[++tl]=ip[x];
			inplace_merge(s+1,s+tl,s+tl+1);
			if(q[x].empty()) continue;

			int prv[B+5],nxt[B+5]; tp=0;
			for(int j=1;j<=tl;j++) prv[j]=0,nxt[j]=tl+1;
			for(int j=1;j<=tl;j++){
				while(tp && p[s[stk[tp]]]<p[s[j]]) nxt[stk[tp--]]=j;
				if(tp) prv[j]=stk[tp];
				stk[++tp]=j;
			}

			for(auto [len,id]: q[x]){
				for(int j=1;j<=tl;j++){
					if(!prv[j]||nxt[j]>tl){
						ans[id]+=len;
						continue;
					}
					int sz=qz[s[nxt[j]]]-qz[s[prv[j]]]+nxt[j]-prv[j];
					ans[id]+=min(len,sz);
				}
				auto solve = [&](int l,int r,bool vl,bool vr){
					if(l>r) return;
					for(int i=l;i<=r;i++){
						if((_prv[i]<l&&vl) || (_nxt[i]>r&&vr))
							ans[id]+=len;
						else
							ans[id]+=min(min(r+1,_nxt[i])-max(l-1,_prv[i]),len);
					}
				};

				solve(1,qz[s[1]],1,0);
				for(int j=1;j<tl;j++)
					solve(qz[s[j]]+1,qz[s[j+1]],0,0);
				solve(qz[s[tl]]+1,m,0,1);
			}
		}
	}
	for(int i=1;i<=idx;i++) 
		printf("%lld\n",ans[i]);
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