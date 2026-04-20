// created time: 2026-04-20 11:13:58
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
const ull base = 131;
ull pw[1000005];

struct Node{
	string s;
	vector<ull>vec;
	int id;

	void init(){
		vec.pb(0);
		ull hsh=0;
		for(auto ch: s){
			hsh=base*hsh+ch;
			vec.pb(hsh);
		}
	}
	int size(){ return s.size(); }
	ull gethash(int l,int r){
		return vec[r]-vec[l-1]*pw[r-l+1];
	}
}a[50005],b[50005];

int n,m;

int check(Node &a,int x,Node &b,int y){
	int len=min(a.size()-x+1, b.size()-y+1);
	// cout<<"len="<<len<<endl;
	int L=1, R=len, ans=0;
	while(L<=R){
		int mid=(L+R)>>1;
		if(a.gethash(x,x+mid-1)==b.gethash(y,y+mid-1)){
			ans=mid;
			L=mid+1;
		}else R=mid-1;
	}
	if(ans==len) return -1;
	// cout<<"here ans="<<ans<<endl;
	return a.s[x+ans-1] <= b.s[y+ans-1];
}

int checkf(Node &a,int x,Node &b,int y){
	int len=min(a.size()-x+1, b.size()-y+1);
	// cout<<"len="<<len<<endl;
	int L=1, R=len, ans=0;
	while(L<=R){
		int mid=(L+R)>>1;
		if(a.gethash(x,x+mid-1)==b.gethash(y,y+mid-1)){
			ans=mid;
			L=mid+1;
		}else R=mid-1;
	}
	if(ans==len) return -1;
	return a.s[x+ans-1] <= b.s[y+ans-1];
}

int chk(int u,int v,int s,int t){
	// return check(b[v],1,b[t],1);
	// check u+v <= s+t
	// cout<<"checking "<<u<<" "<<v<<" "<<s<<" "<<t<<endl;
	int x = check(a[u],1,a[s],1);
	// cout<<"x="<<x<<endl;
	if(~x) return x;

	if(a[u].size()==a[s].size()){
		// cout<<"fucking"<<endl;
		return check(b[v],1,b[t],1);
	}
	else if(a[u].size()<a[s].size()){
		int x = check(b[v],1,a[s],1+a[u].size()); if(~x) return x;
		return check(b[v],1+a[s].size()-a[u].size(),b[t],1);
	}else{
		int x = check(a[u],1+a[s].size(),b[t],1); if(~x) return x;
		return check(b[v],1,b[t],1+a[u].size()-a[s].size());
	}
}
int comp(int u,int v,int s,int t){
	// return check(b[v],1,b[t],1);
	// check u+v <= s+t
	// cout<<"checking "<<u<<" "<<v<<" "<<s<<" "<<t<<endl;
	int x = chk(u,v,s,t);
	if(x==-1) return a[u].size()+b[v].size()<=a[s].size()+b[t].size();
	else return x;
}
// bool check(int u,int v,int s,int t){
// 	int res = check2(u,v,s,t);
// 	if(res != (b[v].s<=b[t].s)){
// 		cout<<u<<" "<<v<<" "<<s<<" "<<t<<endl;
// 		cout<<res<<" but "<<(b[v].s<=b[t].s)<<endl;
// 		exit(0);
// 	}
// 	return res;
// }
vector<int>bel[50005],tag[1000005];
int son[1000005][26],fa[1000005],sb[50005],cnt=1;

void insert(int x){
	int rt=1;
	for(auto ch: a[x].s){
		if(!son[rt][ch-'a']) fa[son[rt][ch-'a']=++cnt]=rt;
		rt=son[rt][ch-'a'];
	}
	if(!tag[rt].size()){
		int cur=rt;
		while(cur){
			tag[cur].pb(x);
			cur=fa[cur];
		}
		bel[x].pb(x);
	}else{
		sb[x]=0;
		for(auto y:tag[rt]){
			bel[y].pb(x);
			// cout<<x<<"->"<<y<<endl;
		}
	}
}


void procedure(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i].s,a[i].id=i,sb[i]=1;
	for(int i=1;i<=m;i++) cin>>b[i].s,b[i].id=i;

	stable_sort(a+1,a+n+1,[](const Node &A,const Node &B){
		return A.s<B.s;
	});
	stable_sort(b+1,b+m+1,[](const Node &A,const Node &B){
		return A.s<B.s;
	});

	for(int i=n;i>=1;i--) insert(i);

	for(int i=1;i<=n;i++) a[i].init();
	for(int i=1;i<=m;i++) b[i].init();

	int q;cin>>q;
	while(q--){
		ll k; cin>>k;
		int pos=0;
		for(int i=1;i<=n;i++){
			if(sb[i]){
				if(k>(ll)bel[i].size()*m)k-=(ll)bel[i].size()*m;
				else {pos=i;break;}
			}
		}
		int i=0,j=0; ll val=1e18;
		for(auto x: bel[pos]){
			int lft=1, rht=m, ans=m+1; ll ok=0;
			while(lft<=rht){
				int mid=(lft+rht)>>1;

				ll sum=0;
				for(auto y: bel[pos]){
					int l=1,r=m,cur=0;
					while(l<=r){
						int mid2=(l+r)>>1;
						if(comp(y,mid2,x,mid))
							cur=mid2,l=mid2+1;
						else r=mid2-1;
					}
					sum+=cur;
				}
				if(sum>=k){
					ans=mid, ok=sum;
					rht=mid-1;
				}else lft=mid+1;
			}
			if(ans!=m+1 && ok<val){
				val=ok;
				i=x, j=ans;
			} 
		}
		printf("%d %d\n", a[i].id, b[j].id);
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	pw[0]=1;
	for(int i=1;i<=m;i++) pw[i]=base*pw[i-1];
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}