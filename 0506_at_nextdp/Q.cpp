// created time: 2026-05-05 14:56:46
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
const int N = 500000;
int fac[N+5],inv[N+5],dv;
void math_init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline int binom(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int perm(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[x-y]%mod;
}
namespace Lagrange {
    vector<int> interpolate(const vector<int>& f) {
        int k = f.size();
        if (k == 0) return {};
        
        vector<int> M(k + 1, 0);
        M[0] = 1;
        for (int i = 0; i < k; ++i) {
            // M(x) = M(x) * (x - i)
            for (int j = i + 1; j >= 0; --j) {
                int term1 = (j > 0) ? M[j - 1] : 0;
                int term2 = (1LL * M[j] * (mod - i)) % mod;
                M[j] = (term1 + term2) % mod;
            }
        }

        vector<int> fact(k, 1), invFact(k, 1);
        for (int i = 1; i < k; ++i) fact[i] = 1LL * fact[i - 1] * i % mod;
        invFact[k - 1] = INV(fact[k - 1]);
        for (int i = k - 2; i >= 0; --i) invFact[i] = 1LL * invFact[i + 1] * (i + 1) % mod;

        vector<int> poly(k, 0); 
        vector<int> Q(k, 0);
        
        for (int i = 0; i < k; ++i) {
            int den = 1LL * invFact[i] * invFact[k - 1 - i] % mod;
            if ((k - 1 - i) % 2 == 1) den = (mod - den) % mod;
            
            int coef = 1LL * f[i] * den % mod;

            Q[k - 1] = M[k];
            for (int j = k - 2; j >= 0; --j) {
                Q[j] = (M[j + 1] + 1LL * i * Q[j + 1]) % mod;
            }

            for (int j = 0; j < k; ++j) {
                poly[j] = (poly[j] + 1LL * coef * Q[j]) % mod;
            }
        }
        return poly;
    }
}
int n,m,l[4005],r[4005],f[4005],g[4005],hz[4005],tmp[4005],ans[4005];

vector<int>E[4005];
struct Seg{
	int val[16005],tag[16005];
	void build(int l,int r,int p){
		val[p]=0,tag[p]=1;
		if(l==r) return;
		int mid=(l+r)>>1;build(l,mid,p<<1),build(mid+1,r,p<<1|1);
	}
	void upd(int p,int w){
		val[p]=(ull)val[p]*w%mod;
		tag[p]=(ull)tag[p]*w%mod;
	}
	void pushup(int p){ addmod(val[p]=val[p<<1]+val[p<<1|1]); }
	void pushdown(int p){
		if(tag[p]>1)upd(p<<1,tag[p]),upd(p<<1|1,tag[p]),tag[p]=1;
	}
	void update(int l,int r,int ql,int qr,int v,int p){
		if(r<ql||qr<l)return;
		if(ql<=l&&r<=qr){upd(p,v);return;}
		int mid=(l+r)>>1;pushdown(p);
		update(l,mid,ql,qr,v,p<<1),update(mid+1,r,ql,qr,v,p<<1|1);
		pushup(p);
	}
	void modify(int l,int r,int x,int v,int p){
		if(l==r){ addmod(val[p]+=v);return; }
		int mid=(l+r)>>1;pushdown(p);
		if(x<=mid)modify(l,mid,x,v,p<<1);
		else modify(mid+1,r,x,v,p<<1|1);
		pushup(p);
	}
	int query(int l,int r,int ql,int qr,int p){
		if(r<ql||qr<l)return 0;
		if(ql<=l&&r<=qr)return val[p];
		int mid=(l+r)>>1;pushdown(p);
		addmod(dv=query(l,mid,ql,qr,p<<1)+query(mid+1,r,ql,qr,p<<1|1));
		return dv;
	}
}S;
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		l[i]=read(),r[i]=read();
		E[r[i]].pb(l[i]);
	}
	for(int i=1;i<=m;i++){
		E[i].pb(0);
		sort(E[i].begin(),E[i].end());
	}

	for(int v=0;v<=m+1;v++){
		// memset(f,0,sizeof(f));
		// f[1]=1;
		S.build(1,m+1,1);
		S.modify(1,m+1,1,1,1);
		for(int i=1;i<=m;i++){
			// for(int j=1;j<=i;j++)hz[j]=1;
			// for(auto x:E[i]) addmod(hz[x]*=2);
			// for(int j=i-1;j>=1;j--)hz[j]=(ull)hz[j]*hz[j+1]%mod;

			S.modify(1,m+1,i+1,S.query(1,m+1,1,i,1),1);
			// for(int j=1;j<=i;j++){
			// 	addmod(f[i+1]+=f[j]);
			// }
			for(int j=E[i].size()-1,k=v;j>=0;j--,addmod(k*=2)){
				int nxt=i;
				if(j+1<E[i].size())nxt=E[i][j+1];

				// for(int d=E[i][j]+1;d<=nxt;d++){
				// 	f[d]=(ull)f[d]*k%mod*v%mod;
				// }
				S.update(1,m+1,E[i][j]+1,nxt,k,1);
			}
		}
		tmp[v]=S.val[1];
		// for(int i=1;i<=m+1;i++)addmod(tmp[v]+=f[i]);
	}
	vector<int>vec(tmp, tmp+m+2);
	vec = Lagrange::interpolate(vec);

	for(int i=0;i<=m;i++) ans[i]=vec[i];

	for(int i=0;i<=m;i++){
		for(int j=0;j<i;j++){
			ans[i]=(ans[i]+(ull)(mod-ans[j])*binom(m-j,i-j))%mod;
		}
		if(i)printf("%d\n",ans[i]);
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	math_init();
	while(T--) procedure();
	return 0;
}