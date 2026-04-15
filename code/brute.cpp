#include <bits/stdc++.h>
#define int long long
#define rep(i, l, r) for (int i = l; i <= r; ++ i)
#define rrp(i, l, r) for (int i = r; i >= l; -- i)
#define eb emplace_back
#define inf 1000000000
#define linf 100000000000000
#define pii pair <int, short>
using namespace std;
constexpr int N = 2e5 + 5, P = 998244353;
inline int rd ()
{
	int x = 0, f = 1;
	char ch = getchar ();
	while (! isdigit (ch)) { if (ch == '-') f = -1; ch = getchar (); }
	while (isdigit (ch)) { x = (x << 1) + (x << 3) + ch - 48; ch = getchar (); }
	return x * f;
}
int n, m;
vector <pii> v1, v2, v3;
signed main ()
{
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.ans","w",stdout));
	#endif
//	freopen ("1.in", "r", stdin);
//	freopen ("1.out", "w", stdout);
	n = rd ();
	rep (t, 1, n)
	{
		int l = rd (), r = rd ();
		if (l == r)
		{
			v1.eb (pii (l, 0));
			continue;
		}
		int x = 0, d;
		rrp (j, 0, 60)
		{
			int bl = l >> j & 1, br = r >> j & 1;
			if (bl == br) d = j;
			else break;
			x |= bl; x <<= 1;
		}
		int y = x;
		y |= 1; y <<= 1;
		rrp (j, 0, d - 2)
		{
			int b = r >> j & 1;
			if (b) v1.eb (pii (y, j));
			y |= b; y <<= 1;
		}
		v1.eb (pii (y >> 1, 0));
		y = x; y <<= 1;
		rrp (j, 0, d - 2)
		{
			int a = l >> j & 1;
			if (! a) v1.eb (pii (y | 1, j));
			y |= a; y <<= 1;
		}
		v1.eb (pii (y >> 1, 0));
	}
	m = rd ();
	rep (t, 1, m)
	{
		int l = rd (), r = rd ();
		if (l == r)
		{
			v2.eb (pii (l, 0));
			continue;
		}
		int x = 0, d;
		rrp (j, 0, 60)
		{
			int bl = l >> j & 1, br = r >> j & 1;
			if (bl == br) d = j;
			else break;
			x |= bl; x <<= 1;
		}
		int y = x;
		y |= 1; y <<= 1;
		rrp (j, 0, d - 2)
		{
			int b = r >> j & 1;
			if (b) v2.eb (pii (y, j));
			y |= b; y <<= 1;
		}
		v2.eb (pii (y >> 1, 0));
		y = x; y <<= 1;
		rrp (j, 0, d - 2)
		{
			int a = l >> j & 1;
			if (! a) v2.eb (pii (y | 1, j));
			y |= a; y <<= 1;
		}
		v2.eb (pii (y >> 1, 0));
	}
	for (auto u : v1)
	{
		for (auto v : v2)
		{
			int x = u.first, y = u.second, xx = v.first, yy = v.second;
			if (y > yy) swap (y, yy), swap (x, xx); 
			if (! y || yy == y)
			{
				int g = ((x << y) ^ (xx << yy)) >> yy << yy;
				v3.eb (pii (g, - yy));
			}
		}
	}
	sort (v3.begin (), v3.end ());
	int ans = 0, cnt = 0;
	int w = -1;
	for (int i = 0; i < v3.size (); ++ i)
	{
		int p = v3[i].first, q = - v3[i].second;
		
		if (w >= p) continue;
		cout<<p<<" -> "<<p+(1ll<<q)<<endl;
		w = p + (1ll << q) - 1; ++ cnt;
		int x = 1ll << q;
		(ans += x % P * (p % P) % P + ((x >> 1) % P) * ((x - 1) % P) % P) %= P;
	}
	printf ("%lld\n", ans); 	
}

/*

*/
