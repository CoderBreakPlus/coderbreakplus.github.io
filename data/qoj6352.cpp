// created time: 2026-06-15 10:08:44
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}

template<typename T>inline void chkmax(T &a,T b){ a=max(a,b); }
template<typename T>inline void chkmin(T &a,T b){ a=min(a,b); }

int n;
int a[1000005], pos[1000005];
int c1_arr[1000005];
int c2_arr[1000005];

inline ll solve(ll B, ll C) {
    if (C >= 0) return 0;
    ll D = B * B - 8LL * C;
    ll K = sqrt(D);
    while (K * K < D) K++;
    while (K * K > D) K--;
    ll ceilsq = K;
    if (ceilsq * ceilsq < D) ceilsq++;
    ll num = ceilsq - B;
    if (num <= 0) return 0;
    return (num + 3) / 4;
}

int calc_fast(int mx0, int mx1, int sum, int k0) {
	if(mx0+(~mx0&1) <= n/2) return mx0 + (~mx0&1);
	if(mx1+(mx1&1) <= n/2) return mx1 + (mx1&1);

	int m = n/2+1;
	if(n%4==0){
		int x1 = solve(3, k0 + m - n);
		int x2 = solve(5, 3 + k0 - sum);
		return min(m + 2*x1, m + 2*x2 + 1);
	}else if(n%4==1){
		int x1 = solve(2, k0 + m - n);
		int x2 = solve(4, 2 + k0 - sum);
		return min(m + 2*x1, m + 2*x2 + 1);
	}else if(n%4==2){
		int x1 = solve(3, 1 + k0 - sum);
		int x2 = solve(5, 2 + k0 + m - n);
		return min(m + 2*x1, m + 2*x2 + 1);
	}else{
		int x1 = solve(2, k0 - sum);
		int x2 = solve(4, 1 + k0 + m - n);
		return min(m + 2*x1, m + 2*x2 + 1);
	}
}

void procedure(){
	n = read();
	int ans1 = 0, ans2 = 0;
	for(int i=1;i<=n+1;i++) {
        c1_arr[i] = 0;
        c2_arr[i] = 1;
    }
	bool flg = 1;
	for(int i=1;i<=n;i++){
		a[i]=read(),pos[a[i]]=i;
		flg &= (a[i]==i);
	}
	if(flg){
		puts(".");
		return;
	}

	int eval = 0;
    int m = n / 2 + 1;
    int m_start = (n % 4 == 1) ? m + 1 : m;

    int mx0_1 = n;
    int mx1_1 = 0;
    int sum_1 = 0;
    int k_1 = 0;

    int mx0_2 = 0;
    int mx1_2 = n;
    int sum_2 = n;
    int k_2 = n - m_start + 1;
    int first_1_idx_2 = 1;

	for(int i=n;i>=1;i--){
        int x = pos[i];
        
		if(x>1 && c1_arr[x-1]) eval--;
		c1_arr[x] = 1;
		if(x<n && !c1_arr[x+1]) eval++;
        
        while(mx0_1 > 0 && c1_arr[mx0_1] == 1) mx0_1--; // mx0 单调递减
        chkmax(mx1_1, n - x + 1);
        sum_1++;
        if (x >= m_start) k_1++;

        int y = n - x + 1;
        c2_arr[y] = 0;
        chkmax(mx0_2, y);
        while(first_1_idx_2 <= n && c2_arr[first_1_idx_2] == 0) first_1_idx_2++; // mx1 取决于第一个1的位置，单调递增
        if (first_1_idx_2 <= n) mx1_2 = n - first_1_idx_2 + 1;
        else mx1_2 = 0;
        sum_2--;
        if (y >= m_start) k_2--;

		if(eval){
			chkmax(ans1, calc_fast(mx0_1, mx1_1, sum_1, k_1));
			chkmax(ans2, calc_fast(mx0_2, mx1_2, sum_2, k_2));
		}
	}

	if(ans1 <= ans2)
		for(int i=1;i<=ans1;i++) putchar("SP"[i&1]);
	else
		for(int i=1;i<=ans2;i++) putchar("PS"[i&1]);

	puts(".");
}

int main(){
	ll T=1;
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
		T=read();
	#endif
	while(T--) procedure();
	return 0;
}