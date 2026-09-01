// created time: 2026-09-01 19:09:01
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

int n;
char s[1005];
int f[1005],nxt[1005][26],vis[26];
int tab[1005],tab2[1005];

int q[1005],t;
bool ok(){
	int c=0;
	for(int i=1;i<=n;i++)c+=tab[i];
	return c==1;
}
bool check(int x){
	t=0;
	for(int i=1;i<=n;i++)
		if(tab[i])q[++t]=i;
	for(int i=1;i<t;i++)
		if(nxt[q[i]][x]==nxt[q[i+1]][x])return 1;
	return nxt[q[t]][x]==nxt[q[1]][x];
}

vector<char>out;
void op(int x){
	out.pb(x+'a');
	memset(tab2,0,sizeof(tab2));
	for(int i=1;i<=n;i++)
		if(tab[i])tab2[nxt[i][x]]=1;
	swap(tab,tab2);
}
bool cur[26];

void procedure(){
	n=read();
	scanf("%s",s+1);

	for(int i=1;i<=n;i++)
		vis[s[i]-'a']=1,tab[i]=1;

	for(int i=2;i<=n;i++){
		f[i]=f[i-1];
		while(f[i]&&s[1+f[i]]!=s[i])f[i]=f[f[i]];
		if(s[1+f[i]]==s[i])f[i]++;
	}
	// cout<<f[n]<<endl;

	if(n%(n-f[n])==0) printf("%d\n",n/(n-f[n])),n=n-f[n];
	else puts("1");

	for(int i=1;i<=n;i++){
		for(int j=0;j<26;j++)if(vis[j]){
			for(int k=i+1;k<=n;k++)
				if(s[k]==j+'a'){nxt[i][j]=k;break;}
			if(nxt[i][j])continue;
			for(int k=1;k<=i;k++)
				if(s[k]==j+'a'){nxt[i][j]=k;break;}
		}
	}

	printf("%d\n",n*n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)putchar(s[j]);
	puts("");

	// cout<<"finish"<<endl;
	// int lst=-1;
	// vector<int>fuck;

	// while(!ok()){
	// 	bool flg=0;
	// 	for(int x=0;x<26;x++)if(vis[x]){
	// 		if(check(x)) {
	// 			op(x);
	// 			flg=1;
	// 			lst=-1;
	// 			break;
	// 		}
	// 	}
	// 	if(!flg){
	// 		for(int x=0;x<26;x++)if(vis[x]&&!cur[x]){
	// 			op(x);
	// 			cur[x]=1,flg=1;
	// 			break;
	// 		}
	// 		assert(flg);
	// 	}
	// }
	// printf("%d\n",(int)out.size());
	// for(char x:out)putchar(x);
	// puts("");
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