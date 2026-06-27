#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 4000000, "q");
    inf.readEoln();
    
    for(int i = 1; i <= n; ++i) {
        inf.readInt(1, 1000000001, "a_i");
        if (i < n) inf.readSpace();
        else inf.readEoln();
    }
    
    for(int i = 1; i <= q; ++i) {
        int op = inf.readInt(1, 3, "op");
        inf.readSpace();
        if (op == 1) {
            inf.readInt(1, n, "x");
            inf.readSpace();
            inf.readInt(1, 1000000001, "y");
        } else if (op == 2) {
            int l = inf.readInt(1, n, "l");
            inf.readSpace();
            inf.readInt(l, n, "r");
        } else {
            inf.readInt(1, n, "l");
            inf.readSpace();
            inf.readInt(1, 1000000001, "x");
        }
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}