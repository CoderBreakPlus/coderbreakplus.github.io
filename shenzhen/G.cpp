// created time: 2026-04-18 08:20:58
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
inline void addmod(int &x){ if(x >= mod) x -= mod; }
inline void addmod(ll &x){ if(x >= mod) x -= mod; }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }

int n,m,x,y;
#define L 0
#define R 1
#define U 2
#define D 3

char s[4]={'L','R','U','D'};
int dx[4]={0,0,-1,1};
int dy[4]={-1,1,0,0};

int vis[55][55];
void procedure(){
	memset(vis,0,sizeof(vis));

	mt19937_64 rnd(1233);


	cin>>n>>m>>x>>y;
	deque<pair<int,int>>q;
	q.push_back({x,y}); vis[x][y]=1;

	vector<pair<int,int>>vec, vec2;

	if(n&m&1){
		int _x=1,_y=1;
		vec.pb(_x,_y);
		for(int i=1;i<=n-1;i++){
			_x++;
			vec.pb(_x,_y);
		}
		for(int i=1;i<=m-2;i++){
			_y++;
			vec.pb(_x,_y);
		}
		_x--, vec.pb(_x,_y);
		_y++, vec.pb(_x,_y);
		_x--, vec.pb(_x,_y);
		_y--, vec.pb(_x,_y);

		for(int i=1;i<=m-3;i++){
			_y--, vec.pb(_x,_y);
			if(i&1) _x++; else _x--;
			vec.pb(_x,_y);
		}
		for(int i=1;i<=n-3;i++){
			_x--, vec.pb(_x,_y);
			if(i&1){
				for(int j=1;j<=m-2;j++) _y++, vec.pb(_x,_y);
			}else{
				for(int j=1;j<=m-2;j++) _y--, vec.pb(_x,_y);
			}
		}

		
		_x=1,_y=1;
		vec2.pb(_x,_y);
		for(int i=1;i<=n-1;i++){
			_x++;
			vec2.pb(_x,_y);
		}
		for(int i=1;i<=m-2;i++){
			_y++;
			vec2.pb(_x,_y);
		}
		_y++, vec2.pb(_x,_y);
		_x--, vec2.pb(_x,_y);
		_x--, vec2.pb(_x,_y);
		_y--, vec2.pb(_x,_y);

		for(int i=1;i<=m-3;i++){
			_y--, vec2.pb(_x,_y);
			if(i&1) _x++; else _x--;
			vec2.pb(_x,_y);
		}
		for(int i=1;i<=n-3;i++){
			_x--, vec2.pb(_x,_y);
			if(i&1){
				for(int j=1;j<=m-2;j++) _y++, vec2.pb(_x,_y);
			}else{
				for(int j=1;j<=m-2;j++) _y--, vec2.pb(_x,_y);
			}
		}
	}else if(!(m&1)){
		int _x=1,_y=1;
		vec.pb(_x,_y);
		for(int i=1;i<n;i++){
			_x++;
			vec.pb(_x,_y);
		}
		for(int i=1;i<=m-1;i++){
			_y++; vec.pb(_x,_y);
			if(i&1){
				for(int k=1;k<=n-2;k++) _x--,vec.pb(_x,_y);
			}else{
				for(int k=1;k<=n-2;k++) _x++,vec.pb(_x,_y);
			}
		}
		_x--,vec.pb(_x,_y);
		for(int i=1;i<m-1;i++) _y--,vec.pb(_x,_y);
	}else{
		int _x=1,_y=1;
		vec.pb(_x,_y);
		for(int i=1;i<m;i++){
			_y++;
			vec.pb(_x,_y);
		}
		for(int i=1;i<=n-1;i++){
			_x++; vec.pb(_x,_y);
			if(i&1){
				for(int k=1;k<=m-2;k++) _y--,vec.pb(_x,_y);
			}else{
				for(int k=1;k<=m-2;k++) _y++,vec.pb(_x,_y);
			}
		}
		_y--,vec.pb(_x,_y);
		for(int i=1;i<n-1;i++) _x--,vec.pb(_x,_y);
	}
	// for(auto [x,y]: vec) cout<<x<<","<<y<<endl;
	// cout<<"-----"<<endl;
	// for(auto [x,y]: vec2) cout<<x<<","<<y<<endl;
	// memset(nxt,-1,sizeof(nxt));
	// for(int i=0;i<vec.size();i++)nxt[vec[i].fi][vec[i].se]=i;

	// for(int i=1;i<=n;i++){
	// 	for(int j=1;j<=m;j++){
	// 		cout<<nxt[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }
	// cout<<endl;
	int pt = 0;

	int yuan = 1;
	if((n&m&1) && x==n && y==m){
		yuan = 2;
		for(int i=0;i<vec2.size();i++){
			if(vec2[i].fi==x && vec2[i].se==y){
				pt=i;
				break;
			}
		}
	}else{
		yuan = 1;
		for(int i=0;i<vec.size();i++){
			if(vec[i].fi==x && vec[i].se==y){
				pt=i;
				break;
			}
		}
	}
	// cout<<"yuan = "<<yuan<<" pt = "<<pt<<endl;
	int cnt = 0;
	auto move_to = [&](int xx,int yy){
		auto move = [&](int t){
			x += dx[t], y += dy[t];
			cout<<s[t];
			// cerr<<"on "<<x<<","<<y<<endl;
			cnt ++;
			assert(cnt <= n*m);

			if(x==xx && y==yy){
				q.push_back({x,y});
				assert(!vis[x][y]);
				vis[x][y]=1;

				cout<<endl;
				cnt = 0;

				return 1;
			}
			else {
				auto [u,v]=q.front();q.pop_front();
				vis[u][v]=0;

				q.push_back({x,y});
				assert(!vis[x][y]);
				vis[x][y]=1;

				return 0;
			}
		};
		while(1){
			int dx,dy;
			if(yuan==2) dx = -vec2[pt].fi, dy = -vec2[pt].se;
			else dx = -vec[pt].fi, dy = -vec[pt].se;
			// cerr<<"from "<<-dx<<" "<<-dy<<endl;

			if((n&m&1) && xx==n && yy==m){
				yuan = 2;
				pt = (pt + 1) % vec.size();
				dx += vec2[pt].fi, dy += vec2[pt].se;
				// cout<<"to "<<vec2[pt].fi<<" "<<vec2[pt].se<<endl;

				int ret;
				if(dx==-1) ret=move(U);
				if(dx==1) ret=move(D);
				if(dy==-1) ret=move(L);
				if(dy==1) ret=move(R);
				if(ret) return;
			}else{
				yuan = 1;
				pt = (pt + 1) % vec.size();
				dx += vec[pt].fi, dy += vec[pt].se;
				// cout<<"to "<<vec[pt].fi<<" "<<vec[pt].se<<endl;

				int ret;
				if(dx==-1) ret=move(U);
				if(dx==1) ret=move(D);
				if(dy==-1) ret=move(L);
				if(dy==1) ret=move(R);
				if(ret) return;
			}
		}
	};
	for(int i=1;i<n*m;i++){
		int xx,yy;
		#ifndef LOCAL
			if(!(cin>>xx>>yy)) exit(0);
		#endif
		#ifdef LOCAL
			vector<pair<int,int>>ok;
			for(int p=1;p<=n;p++)for(int q=1;q<=m;q++)
				if(!vis[p][q])ok.pb(p,q);

			auto [a,b]=ok[rnd()%ok.size()];
			xx=a,yy=b;
			cout<<"> "<<xx<<" "<<yy<<endl;
		#endif
		move_to(xx,yy);
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1; cin>>T;
	// math_init();
	for(int i=1;i<=T;i++){
		procedure();
		// cerr<<"finished "<<i<<endl;
	}
	return 0;
}