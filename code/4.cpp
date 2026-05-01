#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const ll mod = 998244353;
inline ll read(){
	ll x=0, f=1; char ch=getchar();
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
inline ll INV(ll x){ return qpow(x, mod-2); };

int n,p[100005],vis[100005],cnt[100005];
vector<pair<int,int>>pr[100005];

vector<int>buc[100005],v1[100005],v2[100005];

int sta[100005],cur;
void modify_buc(int x,int y,int v){
	// cout<<"modify "<<x<<" "<<y<<" "<<v<<endl;

	bool f=(y>=lg2(sta[x]));
	// cout<<"here "<<y<<" but "<<v2[x].size()<<endl;
	if(f) cur=(ull)cur*v2[x][lg2(sta[x])]%mod;
	if(buc[x][y])sta[x]^=(1<<y);
	buc[x][y]+=v;
	if(buc[x][y])sta[x]^=(1<<y);

	// cout<<"new "<<x<<" have "<<lg2(sta[x])<<endl;
	if(f) cur=(ull)cur*v1[x][lg2(sta[x])]%mod;
}
void add(int x,int v){
	// cout<<"add "<<x<<","<<v<<endl;
	for(auto [a,b]:pr[x]) modify_buc(a,b,v);
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)cnt[i]=vis[i]=0;
	for(int i=1;i<=n;i++)p[i]=read();

	for(int i=1;i<=n;i++){
		if(!vis[i]){
			int x=i,c=0;
			while(!vis[x]){
				vis[x]=1,c++;
				x=p[x];
			}
			cnt[c]++;
		}
	}
	// for(int i=1;i<=n;i++)cout<<i<<" cnt="<<cnt[i]<<endl;
	for(int i=2;i<=n;i++){
		fill(buc[i].begin(),buc[i].end(),0);
		buc[i][0]=1;
		sta[i]=1;
	}

	cur=1;
	for(int i=1;i<=n;i++)for(int o=1;o<=cnt[i];o++)add(i,1);

	// cout<<"cur="<<cur<<endl;

	int ans=0;
	for(int i=1;i<=n;i++){
		if(!cnt[i])continue;
		add(i,-1);
		for(int j=1;j<i;j++){
			add(j,1),add(i-j,1);
			ans=(ans+(ull)cnt[i]*i%mod*cur)%mod;
			// cout<<"contri "<<cnt[i]*i<<" * "<<cur<<endl;
			add(j,-1),add(i-j,-1);
		}
		add(i,1);
	}
	// cout<<"ans="<<ans<<endl;

	for(int i=1;i<=n;i++){
		if(cnt[i]<=1)continue;
		add(i,-2); add(2*i,1);
		// cout<<"cur="<<cur<<endl;
		ans=(ans+(ull)cnt[i]*(cnt[i]-1)%mod*i%mod*i%mod*cur)%mod;
		add(2*i,-1); add(i,2);
	}
	vector<int>vec;
	for(int i=1;i<=n;i++)if(cnt[i])vec.pb(i);
	for(auto a:vec)for(auto b:vec)if(a^b){
		add(a,-1),add(b,-1),add(a+b,1);
		ans=(ans+(ull)cnt[a]*cnt[b]%mod*a%mod*b%mod*cur)%mod;
		// cout<<"contri "<<cnt[a]*cnt[b]*a*b<<" * "<<cur<<endl;
		add(a,1),add(b,1),add(a+b,-1);
	}
	if(ans&1)printf("%d\n",(ans+mod)>>1);
	else printf("%d\n",ans>>1);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	for(int i=1;i<=1e5;i++){
		int x=i;
		for(int j=2;j*j<=x;j++){
			int c=0;
			while(x%j==0)
				x/=j,c++;
			pr[i].emplace_back(j,c);
		}
		if(x>1)pr[i].emplace_back(x,1);
	}
		// cout<<"solving "<<endl;
	for(int i=2;i<=1e5;i++){
		int w=1e5,c=0;
		while(w>=i) w/=i,c++;
		buc[i].resize(c+1,0);
		v1[i]=v2[i]=buc[i];


		int ii=INV(i);
		v1[i][0]=v2[i][0]=1;
		for(int x=1;x<=c;x++)
			v1[i][x]=(ull)v1[i][x-1]*i%mod,
			v2[i][x]=(ull)v2[i][x-1]*ii%mod;

		// if(i==2) cout<<v2[i].size()<<" created"<<endl;
	}
	ll T=read();
	// math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}