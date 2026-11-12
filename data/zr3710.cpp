#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read(){
	ll x;scanf("%lld",&x);return x;
}
template<typename T>void chkmax(T &A,const T &B){ A=max(A,B); }
int n,x[3][500005],ord[3][500005];
bool vis[500005];

bool check(int k){
	for(int i=1;i<=n;i++)vis[i]=0;
	int c=0,pt[3]={1,1,1};

	while(c<n){
		for(int o:{0,1,2})
			while(vis[ord[o][pt[o]]])pt[o]++;

		bool find=0;
		for(int o:{0,1,2}){
			int i=ord[o][pt[o]];
			bool ok=1;
			for(int w:{0,1,2})ok&=(x[w][i]-x[w][ord[w][pt[w]]]<=2*k);
			if(ok){
				vis[i]=find=1,c++;
				break;
			}
		}
		if(!find)break;
	}
	return c==n;
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++){
		for(int o:{0,1,2})x[o][i]=read(),ord[o][i]=i;
	}
	for(int o:{0,1,2})
		sort(ord[o]+1,ord[o]+n+1,[&](int i,int j){
			return x[o][i]<x[o][j];
		});
	int L=0,R=1e9,ans;
	while(L<=R){
		int M=(L+R)>>1;
		if(check(M))ans=M,R=M-1;
		else L=M+1;
	}
	printf("%d\n",ans);
}
int main(){
	assert(freopen("maifu.in","r",stdin));
	assert(freopen("maifu.out","w",stdout));
	procedure();
}