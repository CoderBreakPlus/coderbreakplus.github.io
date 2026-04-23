// created time: 2026-04-22
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 400005
#define INF (int)2e18

int n,a[MAXN],pnt[129];

inline void solve(){
	scanf("%lld",&n);
	for( int i = 1 ; i <= n ; i ++ ) scanf("%lld",&a[i]);
	int N = INF;
	vector<int> A; A.emplace_back( -1 );
	for( int i = n ; i >= 1 ; i -- ) if( a[i] < N ) A.emplace_back( a[i] ),N = a[i];
	int siz = (int)A.size();
	pnt[0] = 0; for( int i = 1 ; i <= 128 ; i ++ ) pnt[i] = -INF;
	for( int i = 1 ; i < siz ; i ++ ){
		for( int v = 128 ; v >= 0 ; v -- ){
			if( pnt[v] > -INF ){
				int newc = v + ( A[pnt[v] + 1] - 1 ) / A[i] + 1;
				if( newc <= 128 ) pnt[newc] = max( pnt[newc] , i );
			}
		}
	}
	int res = INF;
	for( int i = 128 ; i > 0 ; i -- ) if( pnt[i] == siz - 1 ) res = i;
	printf("%lld\n",res);
}

signed main(){
	int testcase; scanf("%lld",&testcase);
	while( testcase -- ) solve();
	return 0;
}
