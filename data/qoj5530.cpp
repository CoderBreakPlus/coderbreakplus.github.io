// created time: 2026-08-21
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
const ll mod=998244353;
const ll inf=2e9;
const int N=4e6+5;
const int M=2e5+5;
const int V=2e6+5;
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
ll jie[N],inv[N];
void init(int n=N-3){
	jie[0]=1;
	for(int i=1;i<=n;i++) jie[i]=1ll*jie[i-1]*i%mod;
	inv[n]=ksm(jie[n],mod-2);
	for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
int a,b,c,d,sum;
void solve(int Ca){
	cin>>a>>b>>c>>d;
	sum=c+d+d-a-a-b;
	if(sum==0){cout<<"0\n";return;}
	if(sum<0) swap(a,d),swap(b,c),sum=-sum;
	int res=0;
	for(int i:{0,a}){
		int j=a-i;
		for(auto x:{-1,(int)(!!i)}) for(auto y:{-1,(int)(!!j)}){
			int x2=i+(x==-1),y2=j+(y==-1);
			int u=b-(x==-1)-(y==-1),v=c-(x==1)-(y==1),w=d-x2-y2-u*2;
			if(u<0||v<0||w<0) continue;
			ll tmp=jie[u+v+w]*inv[u]%mod*inv[v]%mod*inv[w]%mod;
			res=(res+tmp)%mod;
		}
		if(!a) break;
	}
	if(a){
		for(auto x:{-1,1}) for(auto y:{-1,1}){
			int u=b-(x==-1)-(y==-1),v=c-(x==1)-(y==1),w=d-(a+(x==-1)+(y==-1))-u*2;
			if(u<0||v<0||w<0) continue;
			ll tmp=jie[u+v+w]*inv[u]%mod*inv[v]%mod*inv[w]%mod;
			res=(res+1ll*tmp*(a-1))%mod;
		}
	}
	cout<<res<<"\n";
}
int main(){
	#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	#endif
	#ifndef ONLINE_JUDGE
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	init();
	int Ca=1;
	cin>>Ca;
	for(int i=1;i<=Ca;i++){
		solve(i);
	}
	return 0;
}