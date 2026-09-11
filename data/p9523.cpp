#include<bits/stdc++.h>
#define pb push_back
#define ll long long
#define ull unsigned long long

using namespace std;

const int N = 2511;
const ll inf = 1e17;

int n;
string S;
ll f[N][N];
ll A, B, C;
int pre[N][N]; 
ull p = 131;
ull H[N], ppow[N];
int tot = 0, tk;
unordered_map<ull, int> Ma;

void prework() {
	ppow[0] = 1;
	for(int i = 1; i <= N - 5; ++i) ppow[i] = ppow[i - 1] * p;
	for(int i = 1; i <= n; ++i) H[i] = (H[i - 1] * p + (S[i - 1] - 'a' + 1));
	return;
}

inline ull getHsh(int l, int r) {
	return (H[r] - H[l - 1] * ppow[r - l + 1]);
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> S;
	cin >> A >> B >> C;
	for(int i = 0; i <= n; ++i) {
		for(int j = 0; j <= n; ++j) f[i][j] = inf;
	}
	prework();
	for(int len = 1; len <= n; ++len) { 
        Ma.clear();
        for(int r = len; r <= n; ++r) {
            int l = r - len + 1;
            if(l - len >= 1) Ma[getHsh(l - len, l - 1)] = l - len;
            pre[l][r] = Ma[getHsh(l, r)];
        } 
    }
	for(int i = 1; i <= n; ++i) f[i][i] = A;
	for(int len = 1; len <= n - 1; ++len) {
		for(int r = len; r <= n; ++r) {
			int l = r - len + 1; 
			f[l - 1][r] = min(f[l - 1][r], f[l][r] + A);
			f[l][r + 1] = min(f[l][r + 1], f[l][r] + A);
			ll cc = 1; int t = pre[l][r];
			while(t) {
				cc++; 
				f[t][r] = min(f[t][r], f[l][r] + B + cc * C + (r - t + 1 - cc * len) * A); 
                t = pre[t][t + len - 1];
			}
		}
	}
	cout << f[1][n] << '\n';
	return 0;
}