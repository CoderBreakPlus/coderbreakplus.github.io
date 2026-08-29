// created time: 2026-08-29 14:42:00
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MP make_pair
mt19937 rnd(time(0));
const int MOD=998244353;
const int MAXN=3e5+5; 
int c[MAXN][3];bool is[MAXN];
int n,fa[MAXN],len[MAXN];ll fac[MAXN],inf[MAXN],ans[MAXN];
ll ksm(ll a,int b){ll res=1;while(b){if(b&1)res=res*a%MOD;a=a*a%MOD,b>>=1;}return res;} 
inline int find(int x){
	while(x^fa[x]) x=fa[x]=fa[fa[x]];
	return x;
}
int main(){
	ios::sync_with_stdio(false);
	fac[0]=inf[0]=1;
	for(int i=1;i<MAXN;i++) inf[i]=ksm(fac[i]=fac[i-1]*i%MOD,MOD-2); 
	cin>>n;
	for(int i=1;i<=n;i++) fa[i]=i,len[i]=1;
	c[0][1]=n;
	for(int i=1;i<=n;i++){
		for(int j:{0,1,2}) c[i][j]=c[i-1][j];is[i]=is[i-1];
		int x,y;cin>>x>>y;x=find(x),y=find(y);
		if(x==y){
			c[i][len[x]%3]--;
			is[i]|=(len[x]%3!=0);
		}else{
			c[i][len[x]%3]--;
			c[i][len[y]%3]--;
			fa[x]=y;len[y]+=len[x];
			c[i][len[y]%3]++;
		}
	}
	ll f=1,g=1,x=0,y=0;// (x,y),(x+1,y+1)
	auto plus_x=[&](){// (x,y) -> (x+2,y-1)
		ll _f=(g-(x+1)*(x+y+1)%MOD*f%MOD+MOD)*ksm(y,MOD-2)%MOD;
		ll _g=(y*(x+y+2)%MOD*_f%MOD+(x+2)*g)%MOD;
		swap(f,_f);swap(g,_g);
		x+=2,y-=1;
	};
	auto plus_y=[&](){// (x,y) -> (x-1,y+2)
		ll _f=(g-(y+1)*(x+y+1)%MOD*f%MOD+MOD)*ksm(x,MOD-2)%MOD;
		ll _g=(x*(x+y+2)%MOD*_f%MOD+(y+2)*g)%MOD;
		swap(f,_f);swap(g,_g);
		x-=1,y+=2;
	};
	for(int i=n;i>=1;i--)if(!is[i]){
		while(x<c[i][1]||y<c[i][2]){
			if(x<c[i][1]&&y<c[i][2]) plus_x(),plus_y();
			if(x<c[i][1]-1) plus_x();
			if(y<c[i][2]-1) plus_y();
		}
		ans[i]=f*fac[x+y+c[i][0]]%MOD*inf[x+y]%MOD;
	}
	for(int i=1;i<=n;i++) cout<<(is[i]?0:ans[i])<<endl;
	return 0;
}
// f(x,y)=x*(x+y-1)*f(x-1,y-1)+(y-1)*f(x+1,y-2)
// f(x,y)=y*(x+y-1)*f(x-1,y-1)+(x-1)*f(x-2,y+1)
