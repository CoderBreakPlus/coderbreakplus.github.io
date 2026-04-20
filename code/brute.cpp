// created time: 2026-04-20 16:25:52
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }
const ll mod = (ll)1e18 + 3, base = rng(1e8,1e9);
ll pw[200005];

const int M = 1e5 + 30;
const int MOD = 1e9 + 7;

struct Tree{
	int tag,sz,lst[2],lc,rc;
	ll hsh[2];
	Tree(){ tag=sz=lst[0]=lst[1]=lc=rc=hsh[0]=hsh[1]=0; }
}t[8000005];

struct Node{
	ll sz,lst;
	Node(){ sz=lst=0; }
	Node(const Tree &w,int o){ sz=w.sz, lst=w.lst[o]; }
	Node(ll a,ll b){ sz=a, lst=b; }
};

inline Node operator+ (const Node &A, const Node &B){
	return Node(A.sz+B.sz, A.lst+(A.lst==A.sz)*B.lst);
}

#define lc(x) t[x].lc
#define rc(x) t[x].rc
#define sz(x) t[x].sz

int n,m,cnt;
int stk[10000005],tp;

int newnode(){
	if(tp) return stk[tp--];
	else return ++cnt;
}
void remove(int x){
	stk[++tp]=x;
	t[x]=Tree();
}
void pushup(int x){
	int v=t[x].tag;
	if(t[x].sz==1){
		for(int o:{0,1}){
			t[x].hsh[o]=(o^v)+1;
			t[x].lst[o]=(o^v);
		}
	}else{
		for(int o:{0,1}){
			t[x].hsh[o]=((__int128)t[lc(x)].hsh[o^v]*pw[sz(rc(x))]+t[rc(x)].hsh[o^v])%mod;
			t[x].lst[o]=t[lc(x)].lst[o^v]+(t[lc(x)].lst[o^v]==sz(lc(x)))*t[rc(x)].lst[o^v];
		}
	}
}
void build(int l,int r,int &p){
	p=newnode();
	t[p].sz=r-l+1;
	if(l<r){
		int mid=(l+r)>>1;
		build(l,mid,lc(p));
		build(mid+1,r,rc(p));
	}
	pushup(p);
}

vector<int> rub[100005];

vector<int> &tmp = rub[0];

void modify(int l,int r,int ql,int qr,int pp,int &p){
	// cout<<l<<" "<<r<<" "<<ql<<" "<<qr<<endl;
	if(r<ql || qr<l){
		p = pp;
		return;
	}
	t[p=newnode()] = t[pp];
	tmp.pb(p);
	if(ql<=l && r<=qr){
		t[p].tag^=1;
		pushup(p);
		return;
	}
	int mid=(l+r)>>1;
	modify(l,mid,ql,qr,lc(pp),lc(p));
	modify(mid+1,r,ql,qr,rc(pp),rc(p));
	pushup(p);
}

int check(int x,int y,int vx=0,int vy=0,int no=0){
	if(!no){
		if(t[x].hsh[0] == t[y].hsh[0])
			return -1;
	}
	// cout<<"checking "<<x<<" "<<y<<endl;
	if(t[x].sz == 1) return (t[x].tag^vx) < (t[y].tag^vy);
	else{
		if(t[rc(x)].hsh[vx] == t[rc(y)].hsh[vy])
			return check(lc(x), lc(y), vx^t[x].tag, vy^t[y].tag, 1);
		else
			return check(rc(x), rc(y), vx^t[x].tag, vy^t[y].tag, 1);
	} 
}
Node line;
void query(int l,int r,int ql,int qr,int p,int v=0){
	// cout<<"query "<<l<<" "<<r<<" "<<ql<<" "<<qr<<endl;
	if(r<ql||qr<l)return;
	if(ql<=l&&r<=qr){line=line+Node(t[p],v);return;}
	int mid=(l+r)>>1;
	query(l,mid,ql,qr,lc(p),v^t[p].tag);
	query(mid+1,r,ql,qr,rc(p),v^t[p].tag);
}
int qry(int rt,int x){
	line=Node();
	query(0,M,x,M,rt);
	return line.lst;
}
int vis[100005], pre[100005], rt[100005], pw2[200005], prv[100005];
vector<pair<int,int>>E[100005];

struct cmp{
	bool operator()(int x,int y) const{
		// if(!rt[x] || !rt[y]){
		// 	cout<<"compare "<<x<<","<<y<<endl;
		// 	exit(0);
		// }
		int p = check(rt[x],rt[y]);
		if(~p) return p;
		else return x<y;
	}
};

int getans(int l,int r,int p,int v=0){
	if(l==r) return t[p].tag^v;
	int mid=(l+r)>>1;
	return (getans(l,mid,lc(p),t[p].tag^v)+(ull)getans(mid+1,r,rc(p),t[p].tag^v)*pw2[sz(lc(p))])%MOD;
}
void print(int l,int r,int p,int v=0){
	if(l==r) {
		if(l<=10) putchar('0'+(t[p].tag^v));
		return;
	}
	int mid=(l+r)>>1;
	print(l,mid,lc(p),v^t[p].tag);
	print(mid+1,r,rc(p),v^t[p].tag);
}
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		E[u].pb(v,w),E[v].pb(u,w);
	}
	int t=read(),s=read();
	build(0,M,rt[s]);
	set<int,cmp>q;

	q.emplace(s);

	while(!q.empty()){
		// cout<<"getting x"<<endl;

		// cout<<"now sta ";for(auto x:q)cout<<x<<" ";cout<<endl;
		int x=*q.begin(); q.erase(x);
		if(vis[x]) continue;
		vis[x]=1;

		// cout<<"x="<<x<<endl;
		// print(0,M,rt[x]);
		// cout<<endl;
		for(auto [y,w]: E[x]){
			// cout<<"y="<<y<<" w="<<w<<endl;
			if(vis[y]) continue;

			if(rt[y] && q.count(y)) q.erase(y);
			int cur; vector<int>now; tmp = now;

			int exp=qry(rt[x],w);
			// cout<<x<<"->"<<y<<" w="<<w<<" exp="<<exp<<endl;
			modify(0,M,w,w+exp,rt[x],cur);

			// cout<<"new cost "<<cur<<endl;
			if(!rt[y] || check(cur,rt[y])){
				swap(now, rub[y]);
				rt[y] = cur;
				prv[y] = x;
				// cout<<"upd for "<<y<<endl;
				// print(0,M,rt[y]);
				// cout<<endl;
			}
			// cout<<"rt = "<<rt[y]<<" push in "<<y<<endl;
			// cout<<"done"<<endl;
			for(auto x: now) remove(x);

			// for(auto x:q) cout<<x<<",";cout<<endl;
			q.emplace(y);
			// cout<<"put in "<<y<<endl;
			// cout<<"done"<<endl;
		}
		// cout<<"end"<<endl;
	}
	// checkf(rt[4],rt[2]);
	if(!vis[t]){
		puts("-1");
		return;
	}
	printf("%d\n", getans(0,M,rt[t]));
	// vector<int>path = {t};

	// while(t!=s){ t=prv[t]; path.pb(t); }
	// printf("%d\n", (int)path.size());
	// reverse(path.begin(),path.end());
	// for(auto x: path) printf("%d ",x);puts("");
}
int main(){
	pw[0]=pw2[0]=1;
	for(int i=1;i<=200000;i++)pw[i]=(__int128)pw[i-1]*base%mod;
	for(int i=1;i<=200000;i++)pw2[i]=pw2[i-1]*2%MOD;
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.ans","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}