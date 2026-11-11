// created time: 2026-11-11 20:30:32
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MP make_pair
mt19937 rnd(time(0));
const int MAXN=55;
const int MOD=1e9+7; 
ll ksm(ll a,int b){ll r=1;while(b){if(b&1)r=r*a%MOD;a=a*a%MOD,b>>=1;}return r;} 
ll fac[MAXN],inf[MAXN];
ll f[MAXN][MAXN][MAXN];
int n;
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	fac[0]=inf[0]=1;
	for(int i=1;i<MAXN;i++) inf[i]=ksm(fac[i]=fac[i-1]*i%MOD,MOD-2);
	auto add=[&](ll &x,ll y){x+=y;if(x>=MOD)x-=MOD;}; 
	for(int i=n;i>=0;i--){
		f[i][0][0]=1;
		for(int a=0;a<=n;a++)
			for(int b=0;b<=n;b++)if(a+b>0&&i!=0||a+b==1&&i==0){
				for(int j=0;a+b+j<=n;j++)
					for(int k=0;k<=j;k++)if(f[i+1][j][k]){
						if(k<=b){
							int A=a+k,B=b-k;
							if(A>=B) add(f[i][j+a+b][A-B],f[i+1][j][k]*inf[a]%MOD*inf[b]%MOD); 
						}
						if(k&&k<=a){
							int A=a-k,B=b+k;
							if(A>=B) add(f[i][j+a+b][A-B],f[i+1][j][k]*inf[a]%MOD*inf[b]%MOD);   
						} 
					}
			}
	}
	cout<<f[0][n][1]*fac[n]%MOD;
	return 0;	
}
/* brute code:
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MP make_pair
mt19937 rnd(time(0));
const int MAXN=55;
const int MOD=1e9+7;
ll ksm(ll a,int b){ll r=1;while(b){if(b&1)r=r*a%MOD;a=a*a%MOD,b>>=1;}return r;} 
ll fac[MAXN],inf[MAXN];
int n;ll ans=0;
int c[MAXN][2],d[MAXN][2];
void check(int m){
	ll cse=fac[n];
	memcpy(d,c,sizeof(c));
	for(int i=0;i<=m;i++) cse=cse*inf[d[i][0]]%MOD*inf[d[i][1]]%MOD;
	for(int i=m;i>=1;i--){
		int t=min(d[i][0],d[i][1]);
		d[i][0]-=t,d[i][1]-=t;
		if(d[i][0]>d[i-1][0]||d[i][1]>d[i-1][1]) return;
		if(d[i][0]){
			d[i-1][0]-=d[i][0];d[i-1][1]+=d[i][0];
		}else{
			d[i-1][1]-=d[i][1];d[i-1][0]+=d[i][1];
		}
	}
	ans+=cse;
}
void dfs(int p,int les){
	if(les==0) {check(p-1);return;} 
	for(int i=0;i<=les;i++)
		for(int j=0;j<=les;j++)
			if(i+j<=les&&(i+j!=0&&p||!p&&i+j==1)){
				c[p][0]=i;c[p][1]=j;
				dfs(p+1,les-i-j);
			}
	return;
}
int main(){
	ios::sync_with_stdio(false);
	fac[0]=inf[0]=1;
	for(int i=1;i<MAXN;i++) inf[i]=ksm(fac[i]=fac[i-1]*i%MOD,MOD-2);
	cin>>n;
	if(n>=15) assert(0);
	dfs(0,n);
	cout<<ans%MOD*ksm(2,MOD-2)%MOD<<endl;
	return 0;
}


*/