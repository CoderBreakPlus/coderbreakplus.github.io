#include "tree.h"
#include <iostream>
#include <vector>
#include <tuple>
#include <cassert>
#include <iomanip>
#include <cmath>
double tree_hash(double a, double b) {
    return 1.0531415 
         + 0.3214567 * a 
         + 0.3261234 * b 
         + 0.0061827 * a * b;
}
int main() {
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	std::ios::sync_with_stdio(false), std::cin.tie(nullptr);

	int n, q; 
	std::cin >> n >> q;

	std::vector<int>p(n);
	for(auto &i : p) std::cin >> i;

	std::vector<double> ret;

	std::vector<std::tuple<int,int,int,int>>que;
	while(q--){
		int x,y,l,r;
		std::cin >> x >> y >> l >> r;
		que.emplace_back(x,y,l,r);
	}
	init(p);
	for(auto [x,y,l,r]: que){
		ret.push_back(solve(x,y,l,r));
	}

	for(auto x: ret) std::cout << std::fixed << std::setprecision(10) << x << "\n";
	std::cout << std::flush;
	return 0;
}

