// created time: 2026-07-31 18:18:46
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll

inline int lg2(int x){ return 31^__builtin_clz(x); }

int n,q,a[250005],b[250005];
struct Seq{
	ll f[21][250005],g[21][250005];

	ll qmax(int l,int r){
		if(l>r) return -1e18;
		int p=lg2(r-l+1); return max(f[p][l],f[p][r-(1<<p)+1]);
	}
	ll qmin(int l,int r){
		if(l>r) return 1e18;
		int p=lg2(r-l+1); return min(g[p][l],g[p][r-(1<<p)+1]);
	}

	void init(){
		for(int i=1;i<=lg2(n+1);i++)
		for(int j=0;j<=n;j++)
			f[i][j]=max(f[i-1][j],f[i-1][j+(1<<i-1)]),
			g[i][j]=min(g[i-1][j],g[i-1][j+(1<<i-1)]);
	}
}sA, sB;
bool fL[250005], fR[250005];
int gL[250005], gR[250005];

int oL[250005], tL, oR[250005], tR;

int X[250005], Y[250005], W[250005], Z[2500005];

int tag[1000005], cnt[1000005];
ll ans[1000005], out[1000005];
void pushup(int pos){
	ans[pos]=ans[pos<<1]+ans[pos<<1|1];
	cnt[pos]=cnt[pos<<1]+cnt[pos<<1|1];
}
void upd(int pos,int v){
	ans[pos]+=1ll*cnt[pos]*v;
	tag[pos]+=v;
}
void pushdown(int pos){
	if(tag[pos]){
		upd(pos<<1,tag[pos]);
		upd(pos<<1|1,tag[pos]); 
		tag[pos]=0;
	}
}
void cover(int l,int r,int ql,int qr,int pos){
	if(ql>qr) return;
	if(ql<=l && r<=qr){
		upd(pos,1);
		return;
	}
	int mid=(l+r)>>1; pushdown(pos);
	if(ql<=mid) cover(l,mid,ql,qr,pos<<1);
	if(mid<qr) cover(mid+1,r,ql,qr,pos<<1|1);
	pushup(pos);
}
void modify(int l,int r,int x,int v,int pos){
	if(l==r){
		cnt[pos]+=v;
		return;
	}
	int mid=(l+r)>>1; pushdown(pos);
	if(x<=mid) modify(l,mid,x,v,pos<<1);
	else modify(mid+1,r,x,v,pos<<1|1);
	pushup(pos);
}
ll query(int l,int r,int ql,int qr,int pos){
	if(ql>qr) return 0;
	if(ql<=l && r<=qr){
		return ans[pos];
	}
	int mid=(l+r)>>1; ll ret=0; pushdown(pos);
	if(ql<=mid) ret+=query(l,mid,ql,qr,pos<<1);
	if(mid<qr) ret+=query(mid+1,r,ql,qr,pos<<1|1);
	return ret;
}
vector<pair<int,int>>sb[250005],sc[250005];


vector<ll> maxsum(vector<int>A,vector<int>B,vector<int>L1,vector<int> R1,vector<int> L2,vector<int>R2)
{
	n=A.size();
	for(int i=0;i<n;i++) a[i+1]=A[i],b[i+1]=B[i];

	for(int i=1;i<=n;i++) sA.f[0][i]=sA.g[0][i]=a[i]+sA.f[0][i-1];
	for(int i=1;i<=n;i++) sB.f[0][i]=sB.g[0][i]=b[i]+sB.f[0][i-1];

	sA.init(); sB.init();

	ll glo = -1e18;
	for(int i=1;i<=n;i++){
		fL[i]=(sA.qmin(0,i-1)>=sA.g[0][i-1]);
		fR[i]=(sA.qmax(i+1,n)<=sA.f[0][i]);
		glo=max(glo, sA.g[0][i]-sA.qmin(0,i-1));

		if(fL[i]) oL[++tL]=i;
		if(fR[i]) oR[++tR]=i;
	}

	for(int l=1;l<=n;l++){
		int lft=l,rht=n; gL[l]=l;
		while(lft<=rht){
			int mid=(lft+rht)>>1;
			if(sB.qmin(l,mid) < sB.g[0][l-1]) rht=mid-1;
			else gL[l]=mid,lft=mid+1;
		}
	}

	for(int r=1;r<=n;r++){
		int lft=0,rht=r; gR[r]=r;
		while(lft<=rht){
			int mid=(lft+rht)>>1;
			if(sB.qmax(mid,r) > sB.f[0][r]) lft=mid+1;
			else gR[r]=mid,rht=mid-1;
		}
	}

	for(int i=1;i<=tL;i++){
		int l=oL[i];

		int lft=l, rht=n; X[i]=n+1;
		while(lft<=rht){
			int mid=(lft+rht)>>1;
			if(sB.qmax(l,mid)-sB.g[0][l-1]>=glo){
				X[i]=mid;
				rht=mid-1;
			}else lft=mid+1;
		}
		Y[i]=gL[l];

		X[i]=lower_bound(oR+1, oR+tR+1, X[i])-oR;
		Y[i]=upper_bound(oR+1, oR+tR+1, Y[i])-(oR+1);
	}

	for(int i=1;i<=tR;i++){
		int r=oR[i];
		W[i]=gR[r], Z[i]=r;
		W[i]=lower_bound(oL+1, oL+tL+1, W[i])-oL;
		Z[i]=upper_bound(oL+1, oL+tL+1, Z[i])-(oL+1);
		
		if(W[i]<=Z[i]) sb[W[i]].pb(i,1), sb[Z[i]+1].pb(i,1);
	}
	
	q=L1.size();

	for(int i=0;i<q;i++){
		L1[i]++, R1[i]++, L2[i]++, R2[i]++;
	}
	for(int i=0;i<q;i++){
		L1[i]=lower_bound(oL+1,oL+tL+1,L1[i])-oL;
		R1[i]=upper_bound(oL+1,oL+tL+1,R1[i])-(oL+1);

		L2[i]=lower_bound(oR+1,oR+tR+1,L2[i])-oR;
		R2[i]=upper_bound(oR+1,oR+tR+1,R2[i])-(oR+1);
		
		sc[R1[i]].pb(i+1,R2[i]);
		sc[R1[i]].pb(-(i+1),L2[i]-1);
		sc[L1[i]-1].pb(-(i+1),R2[i]);
		sc[L1[i]-1].pb(i+1,L2[i]-1);
	}

	for(int i=1;i<=tL;i++){
		for(auto [x,y]: sb[i]){
			modify(1,tR,x,y,1);
		}
		cover(1,tR,X[i],Y[i],1);
		for(auto [x,y]: sc[i]){
			ll z;
			if(x>0){
				out[x-1]+=(z=query(1,tR,1,y,1));
			}else{
				out[-x-1]-=(z=query(1,tR,1,y,1));
			}
		}
	}

	return vector<ll>(out,out+q);
}