// created time: 2026-04-20 08:01:25
// https://qoj.ac/contest/1887/problem/10032
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
const int mod = 1e9+7;
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
int fac[N+5],inv[N+5];
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
 
int n,a[100005],tmp[100005],m;
int buc[100005],cur[100005],b[100005];
 
int coef(int a,int b){
	if(a<b||b<0)return 0;
	int ans=0;

	if(a==b) return fac[a];
	for(int i=0;i<=b;i++){
		if(i&1) ans=(ans+(ull)(mod-binom(b,i))*qpow(m-i,a))%mod;
		else ans=(ans+(ull)binom(b,i)*qpow(m-i,a))%mod;
	}
	return ans;
}

bool tester;

struct BIT{
	int c[100005];
	void clear(){
		for(int i=1;i<=m;i++)c[i]=0;
	}
	void upd(int x,int w){
		while(x<=m){
			c[x]+=w;
			x+=(x&-x);
		}
	}
	int qry(int x){
		int ret=0;
		while(x){
			ret+=c[x];
			x-=(x&-x);
		}
		return ret;
	}
}b0,b1;
void procedure(){
	n=read(),m=0;
	for(int i=1;i<=n;i++) a[i]=read(),b[i]=0,tmp[++m]=a[i];
 
	sort(tmp+1,tmp+m+1);
	m=unique(tmp+1,tmp+m+1)-(tmp+1);
 
	for(int i=1;i<=m;i++)buc[i]=cur[i]=0;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(tmp+1,tmp+m+1,a[i])-tmp;
	}
	set<int>S2,B1;
	for(int i=1;i<=n;i++){
		buc[a[i]]++;
		if(buc[a[i]]==2)S2.emplace(a[i]);
	}
	for(int i=1;i<=m;i++)if(buc[i]==1)B1.emplace(i);

	set<int>rest;
	for(int i=1;i<=m;i++)rest.emplace(i);
 
	bool have1=0;
	for(int i=1;i<=m;i++)
		if(buc[i]==1) have1=1;
 
	int ok=0, res=m, st=0, val=0;
	 
	for(int i=1;i<=n;i++){
		if(n-i+1==res)
			break;
		// if(a[i]==m)continue;
		if(a[i]<m)
		if(n-i==res){
			int temp = m+1;
			auto it = B1.upper_bound(a[i]);
			if(it!=B1.end()) temp = *it;

			it = rest.upper_bound(a[i]);
			if(it!=rest.end()) temp = min(temp, *it);

			if(S2.size()){
				for(int j=a[i]+1;j<temp;j++){
					if(S2.size()>1 || (S2.size()==1 && (!cur[j] || *S2.begin()!=j))){
						temp=j;
						break;
					}
				}
			}
			if(temp<=m){
				st = i;
				val = temp;
			}
		}else{
			if(have1){
				st=i, val=a[i]+1;
			}else if(S2.size())
			for(int j=a[i]+1;j<=m;j++){
				if(S2.size()>1 || (S2.size()==1 && (!cur[j] || *S2.begin()!=j))){
					st = i;
					val = j;
					break;
				}
			}
		}
		if(!cur[a[i]])res--,rest.erase(a[i]);
		cur[a[i]]++;
		if(cur[a[i]]==2){
			if(S2.count(a[i])) S2.erase(a[i]);
		}
	}
	if(!st){
		puts("-1");
		return;
	}
	for(int i=1;i<=m;i++)cur[i]=0;

	int S1=0;
	S2.clear();
	for(int i=1;i<=m;i++)if(buc[i]>=2)S2.emplace(i);

	for(int i=1;i<st;i++)b[i]=a[i];
	b[st]=val;
	res=m;
	for(int i=1;i<=st;i++){
		res-=(!(cur[b[i]]++));
		if(buc[b[i]]>=2 && cur[b[i]]==2) S2.erase(b[i]);
		if(buc[b[i]]==1 && cur[b[i]]==2) S1++;
	}

	rest.clear();
	for(int i=1;i<=m;i++)rest.emplace(i);

	b0.clear(),b1.clear();
	for(int i=st+1;i<=n;i++){
		if(n-i+1==res){
			int chk=0;
			for(auto j:rest){
				chk++;
				bool red=(!cur[j]);
	            cur[j]++;
	            bool f=0;
	 
            	if(S2.size()&&(S2.size()>=2||*S2.begin()!=j||cur[j]<=1)){
            		f=1;
            	}else
            		f=(S1||(buc[j]==1 && cur[j]>=2));
				if(!f){
					cur[j]--;
					continue;
				}
	 
				b[i]=j,res-=red;
				if(buc[j]>=2&&cur[j]==2) S2.erase(j);
				S1+=(buc[j]==1&&cur[j]==2);
				break;
			}
			assert(chk<=10);
		}else{
			int chk=0;
			for(int j=1;j<=m;j++){
				chk++;
				bool red=(!cur[j]);
				bool core=(n-i==res-red);
	 
	            cur[j]++;
	 
	            bool f=0;
	 
	            if(core){
	            	if(S2.size()&&(S2.size()>=2||*S2.begin()!=j||cur[j]<=1)){
	            		f=1;
	            	}else
	            		f=(S1||(buc[j]==1 && cur[j]>=2));
	            }else{
	            	f=have1||S2.size();
				}
				if(!f){
					cur[j]--;
					continue;
				}
	 
				b[i]=j,res-=red;
				if(buc[j]>=2&&cur[j]==2) S2.erase(j);
				S1+=(buc[j]==1&&cur[j]==2);
				break;
			}
			assert(chk<=10);
		}
		if(rest.count(b[i]))rest.erase(b[i]);
		if(!b[i]){
			puts("-1");
			return;
		}
	}
	int ans=1; res=m;
	for(int i=1;i<=m;i++) buc[i]=0;

	b0.clear(),b1.clear();
	for(int i=1;i<=m;i++)b0.upd(i,1);

	auto on = [&](int i){
		if(!buc[i]){
			res --; 
			b0.upd(i, -1);
			b1.upd(i, 1);
		}
		buc[i] ++;
	};
	auto off = [&](int i){
		buc[i] --;
		if(!buc[i]){
			res ++;
			b0.upd(i, 1);
			b1.upd(i, -1);
		}
	};

	// if(!tester)
	for(int w=1;w<=n;w++){
		if(a[w]!=b[w]){
			int cnt0=0,cnt1=0;
			for(int j=a[w]+1;j<b[w];j++){
				cnt0+=!buc[j];
				cnt1+=(buc[j]>0);
			}
			if(cnt0)ans=(ans+(ull)cnt0*coef(n-w,res-1))%mod;
			if(cnt1)ans=(ans+(ull)cnt1*coef(n-w,res))%mod;
 
			on(a[w]);
			for(int i=w+1;i<=n;i++){
				int cnt0=b0.qry(m)-b0.qry(a[i]);
				int cnt1=b1.qry(m)-b1.qry(a[i]);
				if(cnt0)ans=(ans+(ull)cnt0*coef(n-i,res-1))%mod;
				if(cnt1)ans=(ans+(ull)cnt1*coef(n-i,res))%mod;
				on(a[i]);
			}
			for(int i=n;i>=w;i--)
				off(a[i]);
 
			on(b[w]);
			for(int i=w+1;i<=n;i++){
				int cnt0=b0.qry(b[i]-1);
				int cnt1=b1.qry(b[i]-1);
				if(cnt0)ans=(ans+(ull)cnt0*coef(n-i,res-1))%mod;
				if(cnt1)ans=(ans+(ull)cnt1*coef(n-i,res))%mod;
				on(b[i]);
			}
			break;
		}
		on(a[w]);
	}
	printf("%d\n", ans);
}
 
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	math_init();
	ll T=read();
	tester=(T==600);
	while(T--) procedure();
	return 0;
}