#ifndef PATH_H
#define PATH_H

#include <vector>
void init(int n,int q);
void add(int u,int v);
void del(int u,int v);
int query();
std::vector<int> query_path();

#endif // PATH_H