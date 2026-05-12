// created time: 2026-05-12 16:45:58
// https://qoj.ac/contest/1906/problem/10076
#include<bits/extc++.h>
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

int n,q,a[100005],prv1[100005],nxt1[100005],prv2[100005],nxt2[100005],stk[100005];
int f1[20][100005],f2[20][100005];
int get1(int x,int y){
	int p=lg2(y-x+1);
	return max(f1[p][x],f1[p][y-(1<<p)+1]);
}
int get2(int x,int y){
	int p=lg2(y-x+1);
	return min(f2[p][x],f2[p][y-(1<<p)+1]);
}

int prev1(int x,int v){
	int l=1,r=x,ans=x;
	while(l<=r){
		int mid=(l+r)>>1;
		if(get1(mid,x)<=v)ans=mid,r=mid-1;
		else l=mid+1;
	}
	return ans-1;
}
int prev2(int x,int v){
	int l=1,r=x,ans=x;
	while(l<=r){
		int mid=(l+r)>>1;
		if(get2(mid,x)>=v)ans=mid,r=mid-1;
		else l=mid+1;
	}
	return ans-1;
}
int next1(int x,int v){
	int l=x,r=n,ans=x;
	while(l<=r){
		int mid=(l+r)>>1;
		if(get1(x,mid)<=v)ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans+1;
}
int next2(int x,int v){
	int l=x,r=n,ans=x;
	while(l<=r){
		int mid=(l+r)>>1;
		if(get2(x,mid)>=v)ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans+1;
}
vector<int>buc[100005];
__gnu_pbds::gp_hash_table<int,ll>mp[100005];

void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++)a[i]=read(),f1[0][i]=f2[0][i]=a[i],nxt1[i]=nxt2[i]=n+1,buc[a[i]].pb(i);
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j<=n-(1<<i)+1;j++)
			f1[i][j]=max(f1[i-1][j],f1[i-1][j+(1<<i-1)]),
			f2[i][j]=min(f2[i-1][j],f2[i-1][j+(1<<i-1)]);
	for(int i=1,tp=0;i<=n;i++){
		while(tp && a[stk[tp]]<=a[i]) tp--;
		if(tp) prv1[i]=stk[tp];
		stk[++tp]=i;
	}
	for(int i=n,tp=0;i>=1;i--){
		while(tp && a[stk[tp]]<=a[i]) tp--;
		if(tp) nxt1[i]=stk[tp];
		stk[++tp]=i;
	}

	for(int i=1,tp=0;i<=n;i++){
		while(tp && a[stk[tp]]>=a[i]) tp--;
		if(tp) prv2[i]=stk[tp];
		stk[++tp]=i;
	}
	for(int i=n,tp=0;i>=1;i--){
		while(tp && a[stk[tp]]>=a[i]) tp--;
		if(tp) nxt2[i]=stk[tp];
		stk[++tp]=i;
	}

	while(q--){
		int x=read(),y=read();
		// cout<<x<<","<<y<<endl;
		if(mp[x][y]){
			printf("%lld\n",mp[x][y]-1);
			continue;
		}

		ll ret=0;
		int sx=buc[x].size(),sy=buc[y].size();
		if(!sx||!sy){ puts("0"); continue; }

		if(sx<=sy){
			// cout<<"fuck1"<<endl;
			int k=0,B=(sx+sy-1)/sy;
			for(int i=0;i<sx;i++){
				int pos=buc[x][i];
				while(k+B<sy && buc[y][k+B]<pos) k+=B;
				int l=k,r=min(sy-1,k+B);k--;
				while(l<=r){
					int mid=(l+r)>>1;
					if(buc[y][mid]<pos) k=mid,l=mid+1;
					else r=mid-1;
				}
				k++;
				// cout<<"i="<<i<<" k="<<k<<endl;

				int L=prv2[pos],R=nxt2[pos]; if(i) chkmax(L,buc[x][i-1]);
				auto upd = [&](int x){
					if(x>pos) chkmin(R,x); else chkmax(L,x);
				};
				if(k && k<sy){
					upd(prv1[buc[y][k-1]]), upd(nxt1[buc[y][k]]);
					upd(nxt1[buc[y][k-1]]), upd(prv1[buc[y][k]]);
				}else{
					chkmax(L,prev1(pos,y));
					chkmin(R,next1(pos,y));
				}


				int L2=L; if(k) chkmax(L2,buc[y][k-1]);
				int R2=R; if(k<sy) chkmin(R2,buc[y][k]);

				ret+=(ll)(pos-L)*(R-pos)-(ll)(pos-L2)*(R2-pos);
			}
		}else{
			// cout<<"here"<<endl;
			// for(auto pos: buc[x]) cout<<pos<<" "; cout<<endl;
			// for(auto pos: buc[y]) cout<<pos<<" "; cout<<endl;
			swap(x,y),swap(sx,sy);
			int k=0,B=(sx+sy-1)/sy;
			for(int i=0;i<sx;i++){
				int pos=buc[x][i];
				while(k+B<sy && buc[y][k+B]<pos) k+=B;
				int l=k,r=min(sy-1,k+B);k--;
				while(l<=r){
					int mid=(l+r)>>1;
					if(buc[y][mid]<pos) k=mid,l=mid+1;
					else r=mid-1;
				}
				k++;
				// cout<<"i="<<i<<" k="<<k<<endl;

				int L=prv1[pos],R=nxt1[pos]; if(i) chkmax(L,buc[x][i-1]);
				auto upd = [&](int x){
					if(x>pos) chkmin(R,x); else chkmax(L,x);
				};
				if(k && k<sy){
					upd(prv2[buc[y][k-1]]), upd(nxt2[buc[y][k]]);
					upd(nxt2[buc[y][k-1]]), upd(prv2[buc[y][k]]);
				}else{
					chkmax(L,prev2(pos,y));
					chkmin(R,next2(pos,y));
				}


				int L2=L; if(k) L2=max(L2,buc[y][k-1]);
				int R2=R; if(k<sy) R2=min(R2,buc[y][k]);

				// cout<<L<<" "<<R<<" "<<L2<<" "<<R2<<endl;

				ret+=(ll)(pos-L)*(R-pos)-(ll)(pos-L2)*(R2-pos);
			}
			swap(x,y),swap(sx,sy);
		}
		printf("%lld\n",ret);
		mp[x][y]=ret+1;
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