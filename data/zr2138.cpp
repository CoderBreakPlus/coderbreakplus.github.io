// created time: 2026-07-10 10:33:52
// #pragma GCC optimize(3,"inline")
// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx,avx2")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll

int n,p,z,g,s0[20],s1[20];
inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
inline int lg2(int x){ return 31^__builtin_clz(x); }
inline ll lg2(ll x){ return 63^__builtin_clzll(x); }

int sb[20][20];
int pw[20],a[5005],ff[5005],val[5005],b[5005][20],id[20],iv[20],sq[20];
int f[5005],ans[20005],tot;
vector<int> E[5005];

int seq[5005],tt;
void dfs(int x,int fa){
	seq[++tt]=x,ff[x]=fa;
	for(auto y:E[x]){
		if(y==fa)continue;
		dfs(y,x);
	}
}

// ==========================================
// 核心优化：利用 template 将运行期变量 p 转化为编译期常数 P
// ==========================================
template<int P>
struct FastMod {
    static inline void addmod_fast(int &x){ if(x >= P) x -= P; }
    
    static inline int qpow_fast(int a,int b){
        int res=1, base=a;
        while(b){
            if(b&1) res=res*base%P;
            base=base*base%P; b>>=1;
        }
        return res;
    }
    
    static inline int INV_fast(int x){ return qpow_fast(x, P-2); }
    
    static void fwt(int *arr){
        for(int m=1;m<pw[z];m*=P)
            for(int j=0;j<m;j++)
                for(int k=0;k<pw[z];k+=m*P){
                    int tmp[20];
                    for(int i=1;i<P;i++)tmp[i]=arr[j+k+m*i];
                    for(int i=1;i<P;i++){
                        int &f_val=arr[j+k+m*i];
                        f_val=0;
                        for(int jj=1;jj<P;jj++) f_val+=qpow_fast(i,jj)*tmp[jj];
                        f_val%=P;
                    }
                    for(int i=1;i<P;i++) addmod_fast(arr[j+k]+=arr[j+k+m*i]);
                }
    }
    
    static void ifwt(int *arr){
        int inv[20];
        for(int i=1;i<P;i++) inv[i] = INV_fast(i);
        for(int m=1;m<pw[z];m*=P)
            for(int j=0;j<m;j++)
                for(int k=0;k<pw[z];k+=m*P){
                    int tmp[20];
                    for(int i=0;i<P;i++) tmp[i]=arr[j+k+m*i];
                    for(int x=1;x<P;x++){
                        int sum=0;
                        for(int i=1;i<P;i++)
                            sum+=sb[inv[i]][x]*tmp[i];
                        addmod_fast(arr[j+k+m*x]=P-sum%P);
                    }
                    int sumA=0;
                    for(int x=1;x<P;x++) sumA+=arr[j+k+m*x];
                    addmod_fast(arr[j+k]=tmp[0]+P-sumA%P);
                }
    }

    static void procedure(){
        pw[0]=1;

        for(int i=0;i<=P;i++)
            for(int j=0;j<=P;j++)sb[i][j]=qpow_fast(i,j);

        for(int i=1;i<=z;i++)pw[i]=pw[i-1]*P;
        
        g=2;
        if(P==2) g=1;
        else if(P==7||P==17) g=3;

        for(int i=1,x=g;i<P;i++,x=x*g%P)
            id[x]=i,iv[i]=x;

        for(int i=1;i<=n;i++) E[i].clear();

        for(int i=1;i<=n;i++){
            a[i]=read();
            for(int j=0;j<z;j++){
                b[i][j] = id[a[i]%P];
                a[i]/=P;
            }
        }
        for(int i=1;i<n;i++){
            int u=read(),v=read();
            E[u].pb(v),E[v].pb(u);
        }
        tt=0;
        dfs(1,0);

        for(int s=0;s<pw[z];s++){
            tot=0;
            int ss=s;
            for(int i=0;i<z;i++)sq[i]=ss%P,ss/=P;

            for(int x=1;x<=n;x++){
                val[x]=1;
                for(int i=0;i<z;i++) {
                    if(sq[i]) {
                        if(!b[x][i]){
                            val[x] = 0;
                            break;
                        }else val[x]=val[x]*sb[sq[i]][b[x][i]]; 
                    }
                }
                val[x]%=P;
            }
            for(int i=1;i<=n;i++)f[i]=val[i];
            for(int i=tt;i>=2;i--){
                int x=seq[i];
                addmod_fast(tot+=f[x]);
                (f[ff[x]]*=(1+f[x]))%=P;
            }
            addmod_fast(tot+=f[1]);
            ans[s]=tot;
        }
        
        ifwt(ans);
        
        for(int s=0;s<pw[z];s++){
            int w=0,ss=s;
            for(int i=0;i<z;i++){
                w+=pw[i]*id[ss%P],ss/=P;
            }
            printf("%d ",ans[w]);
        }
        printf("\n");
    }
};

void procedure(){
    n=read(),p=read(),z=read();
    
    // 任务分发站：让编译器针对特定的素数进入极其暴力的乘法/移位替代除法的神仙境界
    switch(p) {
        case 2: FastMod<2>::procedure(); break;
        case 3: FastMod<3>::procedure(); break;
        case 5: FastMod<5>::procedure(); break;
        case 7: FastMod<7>::procedure(); break;
        case 11: FastMod<11>::procedure(); break;
        case 13: FastMod<13>::procedure(); break;
        case 17: FastMod<17>::procedure(); break;
        case 19: FastMod<19>::procedure(); break;
        default: break;
    }
}

int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	while(T--) procedure();
	return 0;
}