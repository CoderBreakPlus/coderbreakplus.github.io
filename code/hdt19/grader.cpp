#include<bits/stdc++.h>
#include"path.h"

namespace path_implementer {
using namespace std;
typedef unsigned long long ull;
const int mod=998244353;

unordered_set<int>S[500005];

int run(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n,q,lst=0;
	cin>>n>>q;
	::init(n,q);

	bool flg=1; int m=0;
	while(q--){
		int op;cin>>op;
		if(op==1){
			int x,y;cin>>x>>y;
			::add(x,y);
			S[x].emplace(y),S[y].emplace(x),m++;
		}else if(op==2){
			int x,y;cin>>x>>y;
			::del(x,y);
			S[x].erase(y),S[y].erase(x),m--;
		}else if(op==3){
			lst=::query();
			// cout<<"lst="<<lst<<endl;
		}else{
			vector<int>now=::query_path();

			// for(int x:now) cout<<x<<" "; cout<<endl;
			bool ok=(int)now.size()==m+1;
			if(ok){
				ok=(now[0]==now[m]);
				// cout<<"ok="<<ok<<endl;
				unordered_set<ull>vis;
				vis.reserve(m*2+1);
				for(int i=1;i<=m&&ok;i++){
					int x=now[i-1],y=now[i];
					if(x<1||x>n||y<1||y>n||!S[x].count(y)){
						// cout<<"fail find "<<x<<","<<y<<endl;
						ok=0;break;
					}
					ull key=((ull)min(x,y)<<32)|max(x,y);
					if(!vis.emplace(key).second){
						// cout<<"it counted"<<endl;
						ok=0;break;
					}
				}
				if(ok){
					int hsh=0;
					for(int i=m;i>=0;i--)
						hsh=(hsh*100ull+now[i])%mod;
					// cout<<hsh<<" and "<<lst<<endl;
					ok=(hsh==lst);
				}
			}
			flg&=ok;
		}
	}
	cout<<(flg?"AC":"WA")<<endl;
	return 0;
}
}

int main(){
	#ifdef LOCAL
		assert(freopen("path.in","r",stdin));
		assert(freopen("path.out","w",stdout));
	#endif
	return path_implementer::run();
}