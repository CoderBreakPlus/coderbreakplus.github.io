// created time: 2026-09-03 19:57:53
#include<bits/stdc++.h>
using namespace std;

bool query(int);
void modify(int,bool);

bool WereYouLast(int n,int m){
	if(n==1024){
		int x=0;
		for(int i=1;i<=10;i++){
			x+=query(i)<<i-1;
		}
		if(x==1023)return 1;
		x++;
		for(int i=1;i<=10;i++)
			modify(i, (x>>i-1)&1);
		return 0;
	}
	int x=0;
	for(int i=0;i<=4;i++)x|=(query(m-i)<<i);
	if(x==31)return 1;
	if((1<<x)==n>>1) x=31;
	else if(query(x+1)) modify(x+1,0),x++;
	else modify(x+1,1),x=0;
	for(int i=0;i<=4;i++)modify(m-i,(x>>i)&1);
	return 0;
}