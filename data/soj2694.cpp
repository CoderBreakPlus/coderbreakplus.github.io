// created time: 2026-10-10
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fi first
#define se second
#define pb emplace_back
template<typename T>void chkmin(T &a,T B){ a=min(a,B); }
template<typename T>void chkmax(T &a,T B){ a=min(a,B); }
inline ll read(){
	ll x=0,f=1; char ch=getchar();
	while(ch>'9'||ch<'0'){ if(ch=='-')f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*f;
}
int n,q,c[300005],a[300005],w[300005],ans[300005];
int sum[300005],dd[300005];

void procedure(){
	n=read(),q=read();
	for(int i=0;i<n;i++) c[i]=read();
	for(int i=1;i<=q;i++)
		a[i]=read(),sum[i]=(sum[i-1]+a[i])%n,dd[i]=__gcd(sum[i],n);

	for(int d=1;d<=n;d++)if(n%d==0){
		for(int i=0;i<d;i++){
			w[i]=n+1;
			for(int j=i;j<n;j+=d) chkmin(w[i],c[j]);
		}
		int now=n+1;
		for(int i=1;i<=q;i++){
			chkmin(now,w[sum[i]%d]);
			if(dd[i]==d) ans[i]=now;
		}
	}
	for(int i=1;i<=q;i++) printf("%d ",ans[i]);
	puts("");
}
int main(){
	#ifdef LOCAL
		assert(freopen("player.in","r",stdin));
		assert(freopen("player.out","w",stdout));
	#endif
	procedure();
}
