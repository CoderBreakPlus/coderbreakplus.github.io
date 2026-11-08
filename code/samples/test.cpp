#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    freopen("migrate.in","r",stdin);
    freopen("migrate.out","w",stdout);

    long long c,t;
    if(fscanf(fi,"%lld %lld",&c,&t)!=2){ fclose(fi); fclose(fo); return 0; }
    while(t--){
        long long n,d;
        if(fscanf(fi,"%lld %lld",&n,&d)!=2) break;
        vector<long long> x(n);
        for(long long i=0;i<n;i++) if(fscanf(fi,"%lld",&x[i])!=1) return 0;
        vector<int> r(n);
        { int j=0; for(int i=0;i<n;i++){ if(j<i)j=i; while(j+1<n && x[j+1]-x[i]<=d) j++; r[i]=j; } }
        long long ans=0;
        vector<int> ways(n,0), suf(n+1,0);
        for(int u=0;u<n;u++){
            ways[u]=1;
            int prevL=u, prevR=u;
            int nextR=r[u];
            if(nextR<=prevR){ continue; }
            for(int v=prevR+1; v<=nextR; v++) ways[v]=1;
            prevL=prevR; prevR=nextR;
            while(prevR<n-1){
                int nn=r[prevR];
                if(nn<=prevR) break;
                int s=0;
                for(int y=prevR; y>prevL; y--){ s+=ways[y]; if(s>3)s=3; suf[y]=s; }
                int a=prevL+1;
                for(int v=prevR+1; v<=nn; v++){
                    while(a<=prevR && r[a]<v) a++;
                    int val = (a<=prevR)? suf[a] : 0;
                    if(val>3) val=3;
                    ways[v]=val;
                    if(val==2) ans++;
                }
                prevL=prevR; prevR=nn;
            }
        }
        fprintf(fo,"%lld\n",ans);
    }
    fclose(fi); fclose(fo);
    return 0;
}