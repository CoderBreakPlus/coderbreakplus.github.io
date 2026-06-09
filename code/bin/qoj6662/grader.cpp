#include <cstdio>
#include <cstdlib>
#include <vector>

extern int maintenance_costs_sum (std::vector<int> U, std::vector<int> V, std::vector<int> W);

void my_assert (bool x) {
	if (!x) {
		puts("Wrong input");
		exit(0);
	}
}

int main() {
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	int N;
	my_assert(scanf("%d", &N) == 1);

	std::vector<int> U(N - 1), V(N - 1), W(N - 1);
	for (int i = 0; i < N - 1; i++) {
		my_assert(scanf("%d%d%d", &U[i], &V[i], &W[i]) == 3);
	}

	int answer = maintenance_costs_sum(U, V, W);
	printf("%d\n", answer);

	return 0;
}
