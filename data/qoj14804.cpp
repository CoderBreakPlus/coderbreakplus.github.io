#include<bits/stdc++.h>
using namespace std;
using ld=long double;

struct Event{
    ld grade,fail;
    int id;
    bool operator<(const Event &other)const{
        return grade<other.grade;
    }
};

struct Tree{
    int n,s;
    vector<vector<int>> edge;
    vector<int> parent,order;
    vector<bool> active;
    vector<ld> alpha,beta,a,b,grade;

    void read(){
        cin>>n>>s;
        edge.resize(n+1);
        for(int i=1,u,v;i<n;i++){
            cin>>u>>v;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        parent.resize(n+1);
        order.push_back(1);
        for(int i=0;i<n;i++){
            int u=order[i];
            for(int v:edge[u])if(v!=parent[u]){
                parent[v]=u;
                order.push_back(v);
            }
        }
        active.assign(n+1,false);
        alpha.resize(n+1);beta.resize(n+1);
        a.resize(n+1);b.resize(n+1);grade.resize(n+1);
    }

    // active 始终是一棵包含根的连通子树。
    // 根收益为 r，走出 active 就退出，求 V[u]=a[u]*r-b[u]。
    // a[u] 同时也是从 u 出发，在退出前进洞的概率。
    void solve(){
        // 自底向上消元：
        // V[u]=alpha[u]*V[parent[u]]-beta[u]。
        for(int i=n-1;i>0;i--){
            int u=order[i];
            if(!active[u])continue;
            ld denominator=edge[u].size();
            ld cost=edge[u].size();
            for(int v:edge[u])if(parent[v]==u&&active[v]){
                denominator-=alpha[v];
                cost+=beta[v];
            }
            alpha[u]=1/denominator;
            beta[u]=cost/denominator;
        }

        // 自顶向下代回，根的收益 V[1]=r。
        a[1]=1;b[1]=0;
        for(int u:order)if(u!=1&&active[u]){
            int p=parent[u];
            a[u]=alpha[u]*a[p];
            b[u]=alpha[u]*b[p]+beta[u];
        }
    }

    void get_events(int id,vector<Event> &events){
        vector<int> sequence;
        active[1]=true;
        ld last=0;

        // 第一部分：逐渐增大奖励，求每个节点的 grade。
        for(int step=1;step<n;step++){
            solve();
            int next=0;
            ld best=numeric_limits<ld>::infinity();

            for(int u=2;u<=n;u++)
                if(!active[u]&&active[parent[u]]){
                    int p=parent[u];

                    // u 刚好值得继续时，它的收益为 0。
                    // 此时其他儿子尚未加入，故：
                    // V[parent[u]]=degree(u)。
                    ld value=((ld)edge[u].size()+b[p])/a[p];
                    if(value<best)best=value,next=u;
                }

            grade[next]=last=max(last,best);
            active[next]=true;
            sequence.push_back(next);
        }

        // 第二部分：按 grade 顺序加入节点。
        // success=P(路径最大 grade <= 当前阈值)。
        fill(active.begin(),active.end(),false);
        active[1]=true;

        for(int u:sequence){
            active[u]=true;
            solve();

            ld success=active[s]?a[s]:0;
            ld fail=clamp(1-success,(ld)0,(ld)1);

            // 全树加入后一定能进洞，直接设为 0，避免误差。
            if(u==sequence.back())fail=0;
            events.push_back({grade[u],fail,id});
        }
    }
};

// 维护所有球的 P(路径最大 grade > 当前阈值) 的乘积。
// 使用线段树，避免除以 0，也避免不断相除积累误差。
struct ProductTree{
    int size=1;
    vector<ld> product;

    ProductTree(int k){
        while(size<k)size*=2;
        product.assign(size*2,1);
    }

    void update(int id,ld value){
        int p=size+id;
        product[p]=value;
        for(p/=2;p;p/=2)
            product[p]=product[p*2]*product[p*2+1];
    }

    ld query()const{
        return product[1];
    }
};

int main(){
    #ifdef LOCAL
        assert(freopen("test.in","r",stdin));
        assert(freopen("test.out","w",stdout));
    #endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin>>k;
    vector<Event> events;

    for(int id=0;id<k;id++){
        Tree tree;
        tree.read();
        tree.get_events(id,events);
    }

    // 相同 grade 时保留同一棵树内部的加入顺序。
    stable_sort(events.begin(),events.end());

    ProductTree product(k);
    ld answer=0,last=0;
    for(const auto &event:events){
        // 两个相邻阈值之间，所有球的失败概率保持不变。
        // 对 P(min M_i > x) 积分。
        answer+=(event.grade-last)*product.query();
        product.update(event.id,event.fail);
        last=event.grade;
    }

    cout<<fixed<<setprecision(12)<<answer<<'\n';
    return 0;
}