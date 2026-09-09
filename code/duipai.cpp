#include<bits/stdc++.h>
using namespace std;

int main(){
	int T = 100;
	while(T--){
		system("./gen");
		system("./agc040d");
		system("./std");
		if(system("diff -Zq test.out test.ans")){
			cout<<"WA\n";exit(0);
		}else
			cout<<"AC\n";
	}
}