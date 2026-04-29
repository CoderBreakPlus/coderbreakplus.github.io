#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

extern vector<int> array_operation(vector<int> A, vector<int> B, vector<int> L, vector<int> R);

int main() {
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, Q;
	cin >> N >> Q;

	vector<int> A(N), B(N);
	for (int i = 0; i < N; i++) {
		cin >> A[i] >> B[i];
	}

	vector<int> L(Q), R(Q);
	for (int i = 0; i < Q; i++) {
		cin >> L[i] >> R[i];
	}

	vector<int> S = array_operation(A, B, L, R);

	for (int i = 0; i < (int)S.size(); i++) {
		cout << S[i] << (((i + 1) < (int)S.size()) ? ' ' : '\n');
	}

	return 0;
}
