// created time: 2026-10-09
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
int L[7][7];
vector<pair<ull,int>> prof[128];
void init(){
 for(int i=0;i<7;i++)for(int j=0;j<7;j++)L[i][j]=lcm(i+1,j+1);
 for(int mask=1;mask<128;mask++){
  vector<int> p;
  for(int i=0;i<7;i++)if(mask>>i&1)p.push_back(i);
  int k=p.size(),lim=1;
  if(k==1){prof[mask].push_back({0,0});continue;}
  for(int i=0;i<k-2;i++)lim*=k;
  unordered_map<ull,int> mp;
  for(int s=0;s<lim;s++){
   int deg[7]={},seq[7],u[6],v[6],x=s;
   for(int i=0;i<k;i++)deg[i]=1;
   for(int i=0;i<k-2;i++)seq[i]=x%k,x/=k,deg[seq[i]]++;
   for(int i=0;i<k-2;i++){
    int j=0;
    while(deg[j]!=1)j++;
    u[i]=j;v[i]=seq[i];deg[j]--;deg[seq[i]]--;
   }
   int a=0,b=0;
   while(deg[a]!=1)a++;
   b=a+1;
   while(deg[b]!=1)b++;
   if(k>1)u[k-2]=a,v[k-2]=b;
   int w=0;
   for(int i=0;i<k-1;i++)w+=L[p[u[i]]][p[v[i]]];
   for(int d=0;d<(1<<(k-1));d++){
    int o[7]={},in[7]={};
    for(int j=0;j<k-1;j++){
     int a=p[u[j]],b=p[v[j]];
     if(d>>j&1)swap(a,b);
     o[a]++;in[b]++;
    }
    ull key=0,rev=0;
    for(int i=0;i<7;i++){
     key|=(ull)(o[i]+8*in[i])<<(6*i);
     rev|=(ull)(in[i]+8*o[i])<<(6*i);
    }
    key=min(key,rev);
    mp[key]=max(mp[key],w);
   }
  }
  for(auto [key,w]:mp)prof[mask].push_back({key,w});
 }
}
struct Flow{
 struct Edge{int to,nxt,cap,cost;};
 Edge e[140];int head[16],cnt;
 void add(int u,int v,int c,int w){
  e[cnt]={v,head[u],c,w};head[u]=cnt++;
  e[cnt]={u,head[v],0,-w};head[v]=cnt++;
 }
 ll solve(int n,int c[7],ull key,int k){
  memset(head,-1,sizeof(head));cnt=0;
  int a[7],b[7];
  for(int i=0;i<7;i++){
   a[i]=c[i]-((key>>(6*i))&7);
   b[i]=c[i]-((key>>(6*i+3))&7);
   if(a[i]<0||b[i]<0)return -1;
   if(a[i])add(14,i,a[i],0);
   if(b[i])add(i+7,15,b[i],0);
  }
  for(int i=0;i<7;i++)if(a[i])
   for(int j=0;j<7;j++)if(b[j])add(i,j+7,n,-L[i][j]);
  int need=n-k;ll ans=0;
  while(need){
   int dis[16],pre[16];bool in[16]={};
   fill(dis,dis+16,1e9);dis[14]=0;
   queue<int> q;q.push(14);in[14]=1;
   while(!q.empty()){
    int u=q.front();q.pop();in[u]=0;
    for(int i=head[u];i!=-1;i=e[i].nxt)if(e[i].cap&&dis[e[i].to]>dis[u]+e[i].cost){
     int v=e[i].to;dis[v]=dis[u]+e[i].cost;pre[v]=i;
     if(!in[v])in[v]=1,q.push(v);
    }
   }
   if(dis[15]==1e9)return -1;
   int f=need;
   for(int v=15;v!=14;v=e[pre[v]^1].to)f=min(f,e[pre[v]].cap);
   for(int v=15;v!=14;v=e[pre[v]^1].to)e[pre[v]].cap-=f,e[pre[v]^1].cap+=f;
   need-=f;ans-=(ll)f*dis[15];
  }
  return ans;
 }
 bool connected(int mask){
  int f[7];iota(f,f+7,0);
  auto find=[&](int x){while(x!=f[x])x=f[x];return x;};
  for(int i=0;i<7;i++)for(int j=head[i];j!=-1;j=e[j].nxt){
   int v=e[j].to-7;
   if(v>=0&&v<7&&e[j^1].cap)f[find(i)]=find(v);
  }
  int rt=-1;
  for(int i=0;i<7;i++)if(mask>>i&1){
   if(rt==-1)rt=find(i);
   else if(find(i)!=rt)return false;
  }
  return true;
 }
};
int main(){
 ios::sync_with_stdio(false);cin.tie(nullptr);
 init();
 int T;cin>>T;
 while(T--){
  int n,c[7]={},mask=0;cin>>n;
  ll ans=0;int last=0;
  for(int i=0,x;i<n;i++){
   cin>>x;c[x-1]++;mask|=1<<(x-1);
   if(i)ans+=L[last-1][x-1];
   last=x;
  }
  if(n==1){cout<<0<<'\n';continue;}
  int k=__builtin_popcount((unsigned)mask);
  Flow mf;
  ll R=mf.solve(n,c,0,1);
  if(mf.connected(mask))ans=R;
  else for(auto [key,w]:prof[mask]){
   ll v=mf.solve(n,c,key,k);
   if(v>=0)ans=max(ans,v+w);
  }
  cout<<ans<<'\n';
 }
}
