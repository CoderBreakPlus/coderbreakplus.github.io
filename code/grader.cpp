#include "cycle.h"
#include <cassert>
#include <iostream>
#include <vector>
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int op, t;
	if(!(std::cin >> op >> t)) return 1;

	std::vector<std::string> s(t), c(t);
	for(int i = 0; i < t; ++i){
		if(!(std::cin >> s[i])) return 1;
		if(op == 2){if(!(std::cin >> c[i])) return 1; if(c[i] == "-") c[i].clear();}
	}

	init(op, t);
	for(int i = 0; i < t; ++i){
		if(op == 1){
			auto ans = construct(s[i]);
			std::cout << ans.first << ' ' << ans.second.size() << '\n';
			std::cout << (ans.second.empty() ? "-" : ans.second) << '\n';
		}else std::cout << (check(s[i], c[i]) ? "Yes" : "No") << '\n';
	}
	return 0;
}
