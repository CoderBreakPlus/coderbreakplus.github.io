// created time: 2026-05-03 13:27:41
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e7+5,MOD=998244353;
int n,X,C,q,a[MAXN];
int stk[MAXN],tp,pre[MAXN],s[MAXN];
int fl[MAXN],fr[MAXN];
ll W(ll x) { return x*(x+1)>>1; }
signed main() {
	scanf("%d%d%d%d",&n,&X,&C,&q);
	iota(a+1,a+n+1,1);
	for(int i=1,l,r;i<=C;++i) {
		l=(1ll*X*(X^i))%n+1;
		r=(X^(1ll*i*i))%n+1;
		swap(a[l],a[r]);
	}
	for(int i=n;i>=1;--i) {
		while(tp&&a[stk[tp]]<a[i]) pre[stk[tp--]]=i+1;
		stk[++tp]=i,s[i]=tp;
	}
	for(int i=1;i<=tp;++i) pre[stk[i]]=1;
	stk[tp=0]=0;
	for(int i=1,sum=0;i<n;++i) {
		while(tp&&s[stk[tp]]>s[i]) {
			sum=(sum-1ll*(s[stk[tp]]-1)*(stk[tp]-stk[tp-1]))%MOD,--tp;
		}
		sum=(sum+1ll*(s[i]-1)*(i-stk[tp]))%MOD,stk[++tp]=i;
		if(sum<0) sum+=MOD;
		fl[i+1]=(fl[i]+sum)%MOD;
	}
	stk[tp=0]=n;
	for(int i=n-1,sum=0;i>=1;--i) {
		while(tp&&s[stk[tp]]>s[i]) {
			sum=(sum-1ll*(s[stk[tp]]-1)*(stk[tp-1]-stk[tp]))%MOD,--tp;
		}
		sum=(sum+1ll*(s[i]-1)*(stk[tp]-i))%MOD,stk[++tp]=i;
		if(sum<0) sum+=MOD;
		fr[i]=(fr[i+1]+sum)%MOD;
	}
	for(int i=1;i<=n;++i) s[i]=(s[i]+s[i-1])%MOD;
	int res=0;
	for(int o=1,l,r;o<=q;++o) {
		l=(1ll*X*o+(X^(1ll*X*o)))%n+1;
		r=(X-o+(X^(X+o)))%n+1;
		if(l>r) swap(l,r);
		int ans=(1ll*(r-l+1)*(s[r]-s[l-1])%MOD+fl[n]-fl[r]-fr[l])%MOD;
		ans=(ans-1ll*(l-1)*(s[n]-s[r])%MOD-1ll*(n-r)*s[l-1]%MOD)%MOD;
		if(ans<0) ans+=MOD;
		res^=ans;
	}
	printf("%d\n",res);
	return 0;
}
