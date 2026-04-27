// created time: 2026-04-24 10:12:43
// http://10.49.18.71/problem/2506
#include<bits/stdc++.h>
using namespace std;
int X(int x){
	if(x==2) return 1;
	return 2;
}
int Y(int x){
	if(x==2) return 0;
	return 2;
}
int main(){
	int n;cin>>n;
	for(int i=0;i<3;i++) cout<<X(i)<<" ";
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++) cout<<(i==2?Y(j):X(j))<<" ";
	}
	for(int _=3;_<n;_++){
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				for(int k=0;k<3;k++) cout<<((j==2&&i!=2)?Y(k):X(k))<<" ";
			}
		}
	}
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			for(int k=0;k<3;k++) cout<<(j==2?X(k):Y(k))<<" ";
		}
	}
	return 0;
}