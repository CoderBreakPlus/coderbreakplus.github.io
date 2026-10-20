#include <iostream>
#include <string>

std::string Alice(int n, int k, std::string s);
std::string Bob(int n, int k, std::string t);

int main() {
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int tests;
	std::cin >> tests;
	while (tests--) {
		int n, k;
		std::string s;
		std::cin >> n >> k >> s;
		std::string t = Alice(n, k, s);
		std::cout << t << '\n';
		std::cout << Bob(n, k, t) << '\n';
	}
	return 0;
}
