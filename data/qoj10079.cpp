// created time: 2026-05-12 18:48:58
// https://qoj.ac/contest/1906/problem/10079
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 998244353;
inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
inline int lg2(int x){ return 31^__builtin_clz(x); }
inline ll lg2(ll x){ return 63^__builtin_clzll(x); }
template<typename T>inline void addmod(T &x){ if(x >= mod) x -= mod; }
template<typename T>inline void chkmax(T &a,T b){ a=max(a,b); }
template<typename T>inline void chkmin(T &a,T b){ a=min(a,b); }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }

class GeneralGraphMVC {
private:
    int n;
    std::vector<uint32_t> adj;      // 原图的邻接矩阵（状态压缩）
    std::vector<uint32_t> comp_adj; // 补图的邻接矩阵（状态压缩）
    uint32_t best_mis;              // 最优的最大独立集 (Max Independent Set)
    int max_mis_size;               // 最大独立集的大小

    // 基础版 Bron-Kerbosch 算法寻找最大团（无 Tomita 枢轴优化）
    void bron_kerbosch(uint32_t R, uint32_t P, uint32_t X) {
        // 如果候选集和排除集都为空，说明找到一个极小/极大结果
        if (P == 0 && X == 0) {
            int r_size = __builtin_popcount(R);
            if (r_size > max_mis_size) {
                max_mis_size = r_size;
                best_mis = R;
            }
            return;
        }

        // 基础剪枝：如果当前团大小 + 候选集中所有的点 <= 目前最优解，直接回溯
        if (__builtin_popcount(R) + __builtin_popcount(P) <= max_mis_size) {
            return;
        }

        // 基础 BK 算法：不选 Pivot，直接遍历 P 中的每一个节点
        uint32_t current_P = P; // 拷贝一份 P 用于遍历
        while (current_P) {
            int v = __builtin_ctz(current_P); // 提取最低位的 1 的位置（即节点编号）
            
            // 递归进入下一层
            // R 加入 v，P 和 X 分别与 v 的邻居 (comp_adj[v]) 取交集
            bron_kerbosch(R | (1U << v), P & comp_adj[v], X & comp_adj[v]);
            
            // 搜索完毕后，将节点 v 从候选集 P 移入排除集 X
            P &= ~(1U << v);
            X |= (1U << v);
            
            // 在遍历集合中清除节点 v，继续处理下一个候选节点
            current_P &= current_P - 1; // 这是一个位运算魔法：直接抹去最低位的 1
        }
    }

public:
    // 构造函数，n 为节点总数 (0 到 n-1，最多支持 32 个节点)
    GeneralGraphMVC(int n) : n(n), adj(n, 0), comp_adj(n, 0), best_mis(0), max_mis_size(0) {
    }

    // 添加无向边 u - v (0 <= u, v < n)
    void add_edge(int u, int v) {
        if (u == v) return; // 忽略自环
        adj[u] |= (1U << v);
        adj[v] |= (1U << u);
    }

    // 执行求解算法，返回最小点覆盖的节点集合
    std::vector<int> solve() {
        if (n == 0) return {};
        
        // 全集掩码
        uint32_t all_mask = (n == 32) ? ~0U : (1U << n) - 1;
        
        // 构建补图
        for (int i = 0; i < n; ++i) {
            comp_adj[i] = all_mask & ~(adj[i] | (1U << i));
        }

        best_mis = 0;
        max_mis_size = 0;
        
        // 执行基础 Bron-Kerbosch 查找补图的最大团
        bron_kerbosch(0, all_mask, 0);

        // 最小点覆盖 = 全集 ^ 最大独立集
        uint32_t mvc_mask = all_mask & ~best_mis;
        std::vector<int> mvc;
        for (int i = 0; i < n; ++i) {
            if ((mvc_mask >> i) & 1) {
                mvc.push_back(i);
            }
        }
        
        return mvc;
    }
};

int n,f[1<<12],g[27][27][1<<10];
char s[4000005];
bool vis[26];

void procedure(){
	n=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1); int w=strlen(s+1);
		int s1=26,s2=26,sta=0;
		for(int i=1;i<=w;i++){
			if(isdigit(s[i])){
				sta|=(1<<s[i]-'0');
			}else if(s1!=26 && s1!=s[i]-'A') s2=s[i]-'A';
			else s1=s[i]-'A';
		}
		g[s1][s2][sta]++;
	}
	for(int i=0;i<=26;i++)for(int j=0;j<=26;j++)
		for(int k=0;k<10;k++)for(int s=0;s<(1<<10);s++)
			if((s>>k)&1)g[i][j][s]+=g[i][j][s^(1<<k)];


	int ans=1e9;
	for(int s=0;s<(1<<10);s++){
		memset(vis,0,sizeof(vis));
		int flg=1,cnt=__builtin_popcount(s);
		vector<pair<int,int>>edge;

		for(int i=0;i<=26;i++)for(int j=0;j<=26;j++){
			if(!g[i][j][1023-s]) continue;
			if(i==26&&j==26){
				flg=0;
				break;
			}else if(j==26){
				vis[i]=1, cnt++;
				continue;
			}else edge.pb(i,j);
		}
		if(!flg)continue;

		GeneralGraphMVC sb(27);

		for(auto [x,y]:edge){
			if(!vis[x]&&!vis[y]){
				sb.add_edge(x+1,y+1);
			}
		}
		ans=min(ans, cnt+(int)sb.solve().size());
	}
	printf("%d\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}