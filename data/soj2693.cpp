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

int n,q,w[1000005];
char s[1000005],t[1000005];
void procedure(){
	n=read(),q=read();
	scanf("%s",s+1); scanf("%s",t+1);
	int sum=0;
	for(int i=1;i<=n;i++){
		if(i&1)
			(sum+=s[i]-t[i]+26)%=26;
		else
			(sum+=t[i]-s[i]+26)%=26;
	}
	puts(sum?"ne":"da");
	while(q--){
		int x=read(); char w[5];
		scanf("%s",w);
		if(x&1)
			(sum+=w[0]-s[x]+26)%=26;
		else
			(sum+=s[x]-w[0]+26)%=26;
		s[x]=w[0];
		puts(sum?"ne":"da");
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("string.in","r",stdin));
		assert(freopen("string.out","w",stdout));
	#endif
	procedure();
}
