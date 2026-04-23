// created time: 2026-04-22
#include<bits/stdc++.h>
#define F(i,a,b) for(long long i=(a);i<=(b);i++)
using namespace std;
#define ll long long
const ll V=121,N=4e5+5,INF=2e18;
ll T,n,a[N],stk[N],top,f[N][V],res;
void solve(){
	cin>>n,res=top=0;
	F(i,0,n)F(j,0,V-1) f[i][j]=INF;
	F(i,1,n) cin>>a[i];
	F(r,1,n){
		while(top&&a[stk[top]]>a[r]) top--;stk[++top]=r;
		ll l[4]={-1,-1,-1,-1};
		F(i,1,3){
			ll L=1,R=top;
			while(L<=R){
				ll mid=(L+R)>>1;
				if((a[r]-1)/a[stk[mid]]+1<=i) l[i]=mid,R=mid-1;
				else L=mid+1;
			}
			if(~l[i]) l[i]=stk[l[i]-1]+1;
		}
		F(i,0,V-2)F(j,1,3)if(~l[j]&&i+j<V) f[r][i+j]=min(f[r][i+j],i?f[l[j]-1][i]:l[j]);
		F(i,1,V-1) f[r][i]=min(f[r][i],f[r][i-1]),res+=i*((i==1?r+1:f[r][i-1])-f[r][i]);
    }cout<<res<<'\n';
}
int main(){cin>>T;while(T--) solve();return 0;}
