// created time: 2026-08-24
#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a), i##ABRACADABRA = (b); i <= i##ABRACADABRA; i++)
#define drep(i, a, b) for (int i = (a), i##ABRACADABRA = (b); i >= i##ABRACADABRA; i--)
using namespace std;
using ll = long long;

int n;
ll L,R,a[5010],b[5010],sum[5010];

ll gs(int L,int R,int o){
  o&=1;
  if ((L^o)&1)++L;
  if ((R^o)&1)--R;
  if (L>R)return 0;
  if (L<=1)return sum[R];
  return sum[R]-sum[L-2];
}

bool chk(){
  sum[1]=b[1];
  rep(i,2,n-1)sum[i]=sum[i-2]+b[i];
  rep(i,1,n-1){
    ll A=gs(1,i-1,1)+gs(i+1,n-1,0);
    ll B=gs(1,i-1,0)+gs(i+1,n-1,1);
    // cout<<i<<' '<<A<<' '<<B<<'\n';
    if (L<=A&&B<=R)return 1;
  }
  return 0;
}

int main() {
  scanf("%d%lld%lld",&n,&L,&R);
  rep(i,1,n)scanf("%lld",&a[i]);
  sort(a+1,a+n+1);
  rep(p,1,n){
    // A chose p
    L-=a[p],R-=a[p];
    int tot=0;
    rep(i,1,n)if (i^p)b[++tot]=a[i];
    if (chk()){
      // cout<<p<<'\n';
      puts("Alice");
      return 0;
    }
    // return 0;
    L+=a[p],R+=a[p];
  }
  puts("Bob");
  return 0;
}
