#pragma GCC optimize("O3")
#include<bits/stdc++.h>
#include"ygg.h"
#ifdef LOCAL
#include"_b.cpp"
#endif
using namespace std;
typedef long long ll;

const int N=5000005;
const ll ninf=-(1LL<<60);

static int st[N],ch[N];
static uint64_t sd=88172645463325252ull;

inline uint32_t rng(){
	sd^=sd<<7;
	sd^=sd>>9;
	return sd;
}
inline ll ceil_div(ll x,int y){
	return x>=0?(x+y-1)/y:x/y;
}

inline ll small_calc(int *q,int d,int au,int *A,ll *B,ll &mx){
	int v[8];
	for(int i=0;i<d;i++){
		int id=q[i];
		if(B[id]>mx)mx=B[id];
		int x=A[id],j=i;
		while(j&&v[j-1]<x){
			v[j]=v[j-1];
			--j;
		}
		v[j]=x;
	}
	ll s=(ll)v[0]+v[1];
	ll t=s-au;
	for(int k=3;k<=d;k++){
		s+=v[k-1];
		ll w=ceil_div(s-au,k-1);
		if(w>t)t=w;
	}
	return t;
}

inline ll quick_calc(int *l,int *r,int au,int *A,ll *B,ll &mx){
	ll sum_hi=0;
	int cnt_hi=0;
	bool first=1;

	while(l<r){
		int d=r-l;
		int q=A[l[(uint64_t)rng()*d>>32]];

		int *x=l,*y=l,*z=r;
		ll sum_gt=0;
		int cnt_gt=0,cnt_eq=0;

		while(y<z){
			int id=*y;
			int v=A[id];

			if(first&&B[id]>mx)mx=B[id];

			if(v>q){
				swap(*x,*y);
				sum_gt+=v;
				++cnt_gt;
				++x;
				++y;
			}else if(v<q){
				--z;
				swap(*y,*z);
			}else{
				++cnt_eq;
				++y;
			}
		}
		first=0;

		ll f=(ll)au-sum_hi-sum_gt+(ll)(cnt_hi+cnt_gt-1)*q;

		if(f<0){
			r=x;
			continue;
		}

		if(f==0&&cnt_hi+cnt_gt+cnt_eq>1)
			return q;

		sum_hi+=sum_gt+(ll)cnt_eq*q;
		cnt_hi+=cnt_gt+cnt_eq;
		l=z;
	}

	return ceil_div(sum_hi-au,cnt_hi-1);
}

void ygg(int sb,int n,vector<int>p,vector<int>a){
	int *P=p.data(),*A=a.data();

	for(int i=1;i<n;i++){
		int fa=P[i];
		if(A[i]>A[fa]){
			answer(0);
			return;
		}
		++st[fa];
	}

	for(int i=1;i<n;i++)
		st[i]+=st[i-1];

	for(int i=n-1;i;i--)
		ch[--st[P[i]]]=i;
	st[n]=n-1;

	vector<ll>b(n);
	ll *B=b.data();

	for(int i=n-1;i>=0;i--){
		int l=st[i],r=st[i+1],d=r-l;

		if(!d){
			B[i]=ninf;
			continue;
		}
		if(d==1){
			B[i]=B[ch[l]];
			continue;
		}

		ll mx=ninf,t;
		if(d<=8)
			t=small_calc(ch+l,d,A[i],A,B,mx);
		else
			t=quick_calc(ch+l,ch+r,A[i],A,B,mx);

		B[i]=mx>t?mx:t;
	}

	if(B[0]>0){
		answer(0);
		return;
	}

	vector<ll>c(n);
	ll *C=c.data();

	int old=A[0];
	int v=old<0?old:0;
	A[0]=v;
	B[0]=-(ll)v;
	C[0]=(ll)old-v;

	for(int i=1;i<n;i++){
		int fa=P[i];
		old=A[i];
		int pv=A[fa];
		v=old<pv?old:pv;

		ll z=(ll)old-v;

		A[i]=v;
		B[i]=(ll)pv-v;

		C[i]=z;
		C[fa]-=z;
	}

	answer(1);
	operation(move(b),move(c));
}