#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
struct DSU {
    vector<int> p, sz;
    vector<pair<int,int>> history;
    int components;
    DSU(int n):p(n+1),sz(n+1,1),components(n) { iota(p.begin(),p.end(),0); }
    int root(int x) { while(p[x]!=x)x=p[x]; return x; }
    void join(int x,int y) {
        x=root(x); y=root(y); if(x==y)return;
        if(sz[x]<sz[y])swap(x,y);
        history.emplace_back(y,sz[x]); p[y]=x; sz[x]+=sz[y]; --components;
    }
    void undo(size_t checkpoint) {
        while(history.size()>checkpoint) {
            auto [y,s]=history.back(); history.pop_back();
            sz[p[y]]=s; p[y]=y; ++components;
        }
    }
};
int main(int argc,char**argv) {
    string dir=argc>1?argv[1]:"data";
    long long all_ops=0,all_queries=0,all_paths=0;
    for(int id=1;id<=80;++id) {
        ifstream f(dir+"/test"+to_string(id)+".in");
        auto require=[&](bool ok,string why) {
            if(!ok) { cerr<<"FAIL test"<<id<<": "<<why<<'\n'; exit(1); }
        };
        int n=0,q=0; f>>n>>q;
        int limit=id<=20?10:id<=40?1000:id<=60?50000:200000;
        require(1<=n&&n<=limit&&1<=q&&q<=limit,"n/q limits");
        vector<vector<pair<int,int>>> seg(4*q);
        auto add_interval=[&](auto&&self,int x,int l,int r,int a,int b,pair<int,int>e)->void {
            if(a>r||b<l)return;
            if(a<=l&&r<=b) { seg[x].push_back(e); return; }
            int mid=(l+r)/2;
            self(self,x*2,l,mid,a,b,e); self(self,x*2+1,mid+1,r,a,b,e);
        };
        unordered_map<ull,int> active;
        active.reserve(q*2);
        vector<int> degree(n+1);
        vector<char> query(q);
        int odd=0,zero=n,last=0,paths=0,queries=0;
        long long edge_work=0;
        for(int t=0;t<q;++t) {
            int op=0; f>>op; require(bool(f),"missing operation");
            require(1<=op&&op<=4,"unknown operation");
            if(op==1||op==2) {
                int u=0,v=0; f>>u>>v;
                require(bool(f)&&1<=u&&u<=n&&1<=v&&v<=n&&u!=v,"bad endpoints");
                if(u>v)swap(u,v);
                ull key=(ull(u)<<32)|unsigned(v);
                auto it=active.find(key);
                if(op==1) {
                    require(it==active.end(),"adding existing edge at "+to_string(t+1));
                    active.emplace(key,t);
                } else {
                    require(it!=active.end(),"deleting missing edge at "+to_string(t+1));
                    add_interval(add_interval,1,0,q-1,it->second,t-1,{u,v});
                    active.erase(it);
                }
                for(int x:{u,v}) {
                    int before=degree[x],after=before+(op==1?1:-1);
                    odd+=(after&1)-(before&1); zero+=(after==0)-(before==0);
                    degree[x]=after;
                }
            } else if(op==3) {
                require(odd==0&&zero==0,"non-Euler degrees at query "+to_string(t+1));
                query[t]=1; ++queries; edge_work+=active.size();
            } else {
                require(last==3,"query_path not immediately after query");
                require(++paths<=10,"too many query_path calls");
            }
            last=op;
        }
        string extra; require(!(f>>extra),"trailing data");
        for(auto [key,start]:active)
            add_interval(add_interval,1,0,q-1,start,q-1,{int(key>>32),int(key&0xffffffff)});
        DSU dsu(n);
        auto dfs=[&](auto&&self,int x,int l,int r)->void {
            auto checkpoint=dsu.history.size();
            for(auto [u,v]:seg[x])dsu.join(u,v);
            if(l==r) {
                if(query[l])require(dsu.components==1,"disconnected query at "+to_string(l+1));
            } else {
                int mid=(l+r)/2; self(self,x*2,l,mid); self(self,x*2+1,mid+1,r);
            }
            dsu.undo(checkpoint);
        };
        dfs(dfs,1,0,q-1);
        ifstream answer(dir+"/test"+to_string(id)+".ans");
        string ans; answer>>ans; require(ans=="AC"&&!(answer>>extra),"answer is not AC");
        all_ops+=q;all_queries+=queries;all_paths+=paths;
        cout<<id<<' '<<n<<' '<<q<<' '<<queries<<' '<<paths<<' '<<edge_work<<'\n';
    }
    cerr<<"VALID: files=80 operations="<<all_ops<<" queries="<<all_queries<<" paths="<<all_paths<<'\n';
}
