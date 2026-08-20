// created time: 2026-08-20 14:20:55
#include<vector>
#pragma GCC optimize(3,"inline")
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2")
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

const int B = 400;
int n,m,q,t[100005],a[100005];
int l[100005],r[100005],k[100005],ans[100005];

vector<int>pos[100005];

int c[100005],idx,id[100005],tmp[100005];
int buc[100005];
int BUCC[200005];
int *bucc = BUCC + 100000;

vector<int>qry[B+5][B+5];
int cnt[B+5][B+5];

void procedure(){
	n=read(),m=read(),q=read();
	for(int i=1;i<=m;i++)pos[i].clear();
	for(int i=1;i<=n;i++)t[i]=read(),pos[t[i]].pb(i);
	for(int i=1;i<=n;i++)a[i]=read();

	for(int i=1;i<=q;i++){
		l[i]=read(),r[i]=read(),k[i]=read();
		ans[i]=-1;
	}

	int L=1;
	while(L<=m){
		int R=L,s=pos[L].size();
		while(R+1<=m&&s+pos[R+1].size()<=B)s+=pos[++R].size();
		// cout<<"here "<<L<<"->"<<R<<endl;

		if(L==R){
			for(int i=1;i<=n;i++)tmp[i]=0;
			for(int x:pos[L])tmp[x]=a[x];
			for(int i=1;i<=n;i++)tmp[i]+=tmp[i-1];

			for(int i=1;i<=q;i++)
				if(!~ans[i]&&tmp[r[i]]-tmp[l[i]-1]<=k[i])
					ans[i]=L;
		}else{
			idx=0;
			for(int i=L;i<=R;i++)for(int x:pos[i])c[++idx]=x;
			sort(c+1,c+idx+1);
			// for(int i=1;i<=idx;i++) cout<<c[i]<<" "; cout<<endl;

			for(int i=0;i<=n;i++)id[i]=0;
			for(int i=1;i<=idx;i++)id[c[i]]=i;
			for(int i=1;i<=n;i++)chkmax(id[i],id[i-1]);

			for(int x=0;x<=idx;x++)
				for(int y=x;y<=idx;y++)
					cnt[x][y]=0,vector<int>().swap(qry[x][y]);

			for(int i=1;i<=q;i++)if(!~ans[i])
				cnt[id[l[i]-1]][id[r[i]]]++;

			for(int x=0;x<=idx;x++)
				for(int y=x;y<=idx;y++)
					qry[x][y].reserve(cnt[x][y]);

			for(int i=1;i<=q;i++)if(!~ans[i])
				qry[id[l[i]-1]][id[r[i]]].pb(i);

			for(int x=0;x<=idx;x++){
				for(int i=L;i<=R;i++)buc[i]=0;
				for(int i=-idx;i<=idx;i++)bucc[i]=0;
				bucc[0]=R-L+1; // start with 0s
				int mn=0;
				for(int y=x;y<=idx;y++){
					// cout<<"considering "<<x<<","<<y<<" mn="<<mn<<endl;
					for(int i: qry[x][y])if(mn<=k[i]){
						// cout<<"solve for "<<i<<endl;
						for(int j=L;j<=R;j++)
							if(buc[j]<=k[i]){
								ans[i]=j;
								// cout<<j<<" is "<<buc[j]<<endl;
								break;
							}
					}
					int p=c[y+1];
					bucc[buc[t[p]]]--;
					if(a[p]==-1)
						chkmin(mn,buc[t[p]]-1);
					else
						if(!bucc[mn]) mn++;

					bucc[buc[t[p]]+=a[p]]++;
				}
			}
		}
		L=R+1;
	}
	for(int i=1;i<=q;i++)
		printf("%d\n",ans[i]);
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