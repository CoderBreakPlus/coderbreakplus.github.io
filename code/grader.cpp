#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

extern vector<long long> tower_events(vector<int> H, vector<vector<int>> E);

int main() {
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int N, Q;
	cin >> N >> Q;
	vector<int> H(N);
	vector<vector<int>> E(Q);
	for (auto &h : H) {
		cin >> h;
	}
	for (auto &e : E) {
		int t;
		cin >> t;
		e.resize(t);
		for (auto &v : e) {
			cin >> v;
		}
	}
	vector<long long> X = tower_events(H, E);
	for (long long &x : X)
		cout << x << "\n";
	return 0;
}
