#include <iostream>
#include <cassert>
#include "cheapai.h"

using namespace std;

int main() {
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	int K;
    string S;

    std::cin >> K >> S;

	std::cout << solve(K, S) << '\n';

	return 0;
}