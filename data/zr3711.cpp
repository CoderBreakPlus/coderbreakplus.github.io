// created time: 2026-11-12 07:12:00
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb emplace_back
#define fi first
#define se second
inline ll read(){
	ll x;scanf("%lld",&x);return x;
}
template<typename T>void chkmax(T &A,const T &B){ A=max(A,B); }

int n,k,c;
vector<int>fac;
int check(int M){
	int ret=0;
	for(int i=0;i<(1<<fac.size());i++){
		int now=1;
		for(int j=0;j<fac.size();j++)if((i>>j)&1)
			now=now*fac[j];
		if(__builtin_parity(i))ret-=M/now;
		else ret+=M/now;
	}
	return ret;
}
void procedure(){
	n=read()+2,k=read();
	fac.clear();
	int tmp=n;
	for(int i=2;i*i<=tmp;i++){
		if(tmp%i==0){
			fac.pb(i);
			while(tmp%i==0)tmp/=i;
		}
	}
	if(tmp>1)fac.pb(tmp);
	int L=1,R=n-1,ans=-1;
	while(L<=R){
		int M=(L+R)>>1;
		if(check(M)>=k)ans=M,R=M-1;
		else L=M+1;
	}
	if(~ans){
		vector<int>vec;
		int a=ans,b=n-ans,op=(a<b?0:1);
		while(a>1||b>1){
			if(a<b){
				int k=(b-1)/a;
				vec.pb(k);
				b-=k*a;
			}else{
				int k=(a-1)/b;
				vec.pb(k);
				a-=k*b;
			}
		}
		printf("%d %d\n",(int)vec.size(),op);
		for(int x: vec) printf("%d ",x);
		puts("");
	}else puts("-1");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	int T=read();
	while(T--)procedure();
}