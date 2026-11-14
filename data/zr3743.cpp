// created time: 2026-11-14 08:04:13
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 1e9+9;
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
inline void upd(int &a,ull b){ a=(a+b)%mod; }
int k,len[105];
char s[105][10005];
int mn[105][105];
vector<int>f[105][105],g[105][105][26];

void procedure(int c){
	k=read();
	for(int i=1;i<=k;i++){
		scanf("%s",s[i]);
		len[i]=strlen(s[i]);
	}
	// if(c==228){
	// 	cerr<<k<<endl;
	// 	for(int i=1;i<=k;i++)cerr<<s[i]<<endl;
	// 	exit(0);
	// }
	for(int l=1;l<=k;l++){
		for(int r=l;r<=k;r++){
			mn[l][r]=len[l];
			if(r>l)chkmin(mn[l][r],mn[l][r-1]);
			f[l][r]=vector<int>(mn[l][r]+1,0);
			for(int z=0;z<26;z++)
				g[l][r][z]=vector<int>(mn[l][r]+1,0);
			// cout<<l<<"->"<<r<<" sz="<<mn[l][r]<<endl;
		}
	}

	for(int l=k;l>=1;l--){
		for(int r=l;r<=k;r++){
			int w=mn[l][r];
			// cout<<"solving "<<l<<" "<<r<<endl;
			for(int i=w;i>=0;i--){
				// cout<<"i="<<i<<endl;
				if(i==w){
					if(l==r){
						f[l][r][w]=1;
					}else{
						bool flg=1;
						for(int x=l+1;x<=r;x++)
							if(len[x]==w)flg=0;
						if(flg)
						f[l][r][w]=f[l+1][r][w];
					}
				}else{
					for(int z=0;z<26;z++){
						ll sum=0;
						if(z)sum=g[l][r][z-1][i];

						for(int x=r;x>=l;x--){
							if(s[x][i]!='?'&&s[x][i]-'a'!=z)break;
							if(x==l)sum+=f[l][r][i+1];
							else if(z){
								sum+=(ull)g[l][x-1][z-1][i]*f[x][r][i+1];
								if(sum>=8ull*mod*mod)
									sum-=8ull*mod*mod;
							}
						}
						g[l][r][z][i]=sum%mod;
					}
					f[l][r][i]=g[l][r][25][i];
				}
			}
		}
	}
	printf("%d\n",f[1][k][0]);
}
int main(){
	// assert(freopen("book.in","r",stdin));
	// assert(freopen("book.out","w",stdout));
	ll T=read();
	// math_init();
	for(int i=1;i<=T;i++){
		procedure(i);
	}
	return 0;
}