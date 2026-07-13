// created time: 2026-07-13 10:08:39
#include<bits/stdc++.h>
#include<atcoder/all>

using namespace std;
using namespace atcoder;
using ll=long long;

const ll MXM=200005;

using mint = modint998244353;
vector<mint> fac(MXM),invfac(MXM);

void calc_fac(){
  fac[0]=mint(1);
  for(ll i=1;i<MXM;i++){
    fac[i]=fac[i-1]*mint(i);
  }
  invfac[MXM-1]=mint(1)/fac[MXM-1];
  for(ll i=MXM-2;i>=0;i--){
    invfac[i]=invfac[i+1]*mint(i+1);
  }
}

mint nCr(ll n,ll r){
  if(n<r){return 0;}
  return fac[n]*invfac[r]*invfac[n-r];
}

using tup=tuple<ll,ll,mint>;

int main(){
  ll al=(1ll<<60)-1;
  calc_fac();
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while(t--){
    ll n,k;
    cin >> n >> k;
    ll o=0;
    vector<ll> a(n);
    for(auto &nx : a){
      cin >> nx;
      o|=nx;
    }
    ll d1=0;
    for(ll i=n-k;i<n;i++){d1|=a[i];}
    ll d0=(al^d1);
    mint ini(0);
    for(ll i=0;i<=k;i++){ ini+=nCr(n,i); }
    vector<tup> sta={{0,k,ini}};
    mint res=0;
    for(ll i=n-1;i>=0;i--){
      {
        vector<tup> nsta;
        for(auto [f,rk,pat] : sta){
          ll e0=((al^f)&d0);
          ll e1=((al^f)&d1);
          int ban=0;
          if((e0&a[i])>0){ban|=2;}
          if((e1&(al^a[i]))>0){ban|=1;}
          if((ban&1)==0){
            // and
            mint npat=(pat+nCr(i,rk))/mint(2);
            nsta.push_back(tup{(f|(e0&(al^a[i]))),rk,npat});
          }
          if((ban&2)==0 && rk>0){
            // or
            mint npat=(pat-nCr(i,rk))/mint(2);
            nsta.push_back(tup{(f|(e1&a[i])),rk-1,npat});
          }
        }
        sta=nsta;
      }
      {
        vector<tup> nsta;
        for(auto [f,rk,pat] : sta){
          if((f&o)==o){
            res+=pat;
          }
          else{
            nsta.push_back(tup{f,rk,pat});
          }
        }
        sta=nsta;
      }
    }
    for(auto [f,rk,pat] : sta){
      if((f&d1)==d1){res+=pat;}
    }
    cout << res.val() << "\n";
  }
  return 0;
}
