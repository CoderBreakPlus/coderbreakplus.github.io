// created time: 2026-08-12 19:27
// 迭代

#include<bits/stdc++.h>
using namespace std;
using ll=long long;
inline ll read(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-') f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=5+5;
int n,m,a[maxn][maxn],x[maxn],y[maxn];
const int inf=2e9;
bool check(int k){
	for(int i=1;i<=n;i++) x[i]=1;
	for(int i=1;i<=m;i++) y[i]=inf;
	y[m+1]=inf+1;
	auto chk=[k](){
		for(int i=1;i<=n;i++) if(x[i]<=0) return 0;
		for(int i=1;i<=m;i++) if(y[i]<=0) return 0;
		for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
			if(abs(1ll*x[i]*y[j]-a[i][j])>k) return 0;
		return 1;
	};
	while(1){
		for(int i=1;i<=n;i++){
			x[i]=max(x[i],x[i-1]+1);
			for(int j=1;j<=m;j++)
				x[i]=max(x[i],(a[i][j]-k-1)/y[j]+1);
		}
		for(int i=m;i>0;i--){
			y[i]=min(y[i],y[i+1]-1);
			for(int j=1;j<=n;j++)
				y[i]=min(y[i],(a[j][i]+k)/x[j]);
		}
		if(y[1]<=0||x[n]>y[m]||chk()) break;
	}
	if(chk()) return 1;
	for(int i=1;i<=n;i++) x[i]=inf;
	for(int i=1;i<=m;i++) y[i]=1;
	x[n+1]=inf+1;
	while(1){
		for(int i=1;i<=m;i++){
			y[i]=max(y[i],y[i-1]+1);
			for(int j=1;j<=n;j++)
				y[i]=max(y[i],(a[j][i]-k-1)/x[j]+1);
		}
		for(int i=n;i>0;i--){
			x[i]=min(x[i],x[i+1]-1);
			for(int j=1;j<=m;j++)
				x[i]=min(x[i],(a[i][j]+k)/y[j]);
		}
		if(x[1]<=0||x[n]<y[m]||chk()) break;
	}
	return chk();
}
int main(){
#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	n=read();
	m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) a[i][j]=read();
	int l=0,r=1e9;
	while(l<r){
		int mid=l+(r-l)/2;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	check(r);
	printf("%d\n",r);
	for(int i=1;i<=n;i++) printf("%d ",x[i]);
	printf("\n");
	for(int i=1;i<=m;i++) printf("%d ",y[i]);
#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
#endif
	return 0;
}
