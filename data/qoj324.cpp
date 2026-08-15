// created time: 2026-08-15
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

int n,p,s[25],t[25],w[25],id[25],f[1<<22],g[1<<22],h[1<<22];
const int INF = 0x7f7f7f7f;

int type[25],st[25];
void procedure(){
	n=read(),p=read();
	for(int i=1;i<=n;i++) s[i]=read(),t[i]=s[i]+read()-1,w[i]=read(),id[i]=i;

	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			if(s[i]>s[j]){
				swap(s[i],s[j]);swap(t[i],t[j]);
				swap(w[i],w[j]);swap(id[i],id[j]);
			}
		}

	// for(int i=1;i<=n;i++) cout<<s[i]<<" "<<t[i]<<" "<<w[i]<<endl;

	s[n+1]=INF;

	memset(f,0x7f,sizeof(f));
	f[0]=1;
	for(int i=0;i<(1<<n);i++){
		int tim=f[i];
		if(tim==INF)continue;
		// for(int k=0;k<n;k++)cout<<((i>>k)&1);
		// cout<<" tim="<<f[i]<<endl;

		for(int k=0;k<n;k++)if((~i>>k)&1){
			for(int j=0;j<=n;j++)if(max(tim,t[j]+1)<s[j+1]){
				int st=max(tim,t[j]+1);
				int ed=st+w[k+1];
				// cout<<"try "<<st<<" "<<ed<<endl;
				if(ed<s[k+1] && ed<f[i^(1<<k)]){

					bool flg=0;
					for(int x=0;x<n;x++)if((i>>x)&1)
						flg|=(st<=s[x+1] && s[x+1]<=ed);


					// for(int x=0;x<n;x++)cout<<(((i^(1<<k))>>x)&1);
					// cout<<" find a way "<<st<<" "<<ed<<endl;
					if(!flg){
						f[i^(1<<k)]=ed;
						g[i^(1<<k)]=k+1,h[i^(1<<k)]=st;
						break;
					}
				}
			}
		}
	}
	if(p==2){
		for(int p=0;p<(1<<n);p++){
			int q=(1<<n)-1-p;
			if(f[p]<INF&&f[q]<INF){
				puts("YES");
				while(p){
					int x=g[p];
					type[id[x]]=1,st[id[x]]=h[p];
					p^=(1<<x-1);
				}
				while(q){
					int x=g[q];
					type[id[x]]=2,st[id[x]]=h[q];
					q^=(1<<x-1);
				}
				for(int j=1;j<=n;j++)
					printf("%d %d\n",type[j],st[j]);
				return;
			} 
		}
	}else{
		if(f[(1<<n)-1]<INF){
			puts("YES");
			int p=(1<<n)-1;
			while(p){
				int x=g[p];
				type[id[x]]=1,st[id[x]]=h[p];
				p^=(1<<x-1);
			}
			for(int j=1;j<=n;j++)
				printf("%d %d\n",type[j],st[j]);
			return;
		}
	}
	puts("NO");
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