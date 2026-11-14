// created time: 2026-11-14 14:35:00
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int mod=100003;
int n,k,a[100005],dp[100005];
inline int qpow(int a,int b){
    int ans=1,base=a;
    while(b){
        if(b&1)ans=(ull)ans*base%mod;
        base=(ull)base*base%mod;
        b>>=1;
    }
    return ans;
}
int K[100005],B[100005];
int main(){
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=n;i>=1;i--)
        for(int j=2*i;j<=n;j+=i)a[i]^=a[j];
    int cnt=0,ans;
    for(int i=1;i<=n;i++)cnt+=a[i];
    if(cnt<=k){
        ans=cnt;
    }else{
        K[n]=1,B[n]=1;
        for(int i=n-1;i>k;i--){
            int iv=qpow((n+(ull)(mod-n+i)*K[i+1])%mod, mod-2);
            K[i]=(ull)i*iv%mod;
            B[i]=(n+(ull)(n-i)*B[i+1]%mod)*iv%mod;
        }
        dp[k]=k;
        for(int i=k+1;i<=cnt;i++){
            dp[i]=((ull)dp[i-1]*K[i]+B[i])%mod;
        }
        ans=dp[cnt];
    }
    for(int i=1;i<=n;i++) ans=(ull)ans*i%mod;
    printf("%d\n",ans);
    return 0;
}