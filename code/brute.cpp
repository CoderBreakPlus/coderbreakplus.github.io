#include <set>

#include <cstdio>

const int N = 200005 ;

#define _be begin
#define _en rbegin

#define era erase
#define ins insert

using namespace std ;

set <int> col[N] ;

int seg[N * 3] ;
int mnv[N * 3] ;
int mxt[N * 3] ;
int tag[N * 3] ;
int lcon[N * 3] ;
int rcon[N * 3] ;

#define lc (rt << 1)
#define rc (rt << 1 | 1)

inline void _down(int rt){
    if (tag[rt]){
        mnv[lc] += tag[rt] ;
        mnv[rc] += tag[rt] ;
        tag[lc] += tag[rt] ;
        tag[rc] += tag[rt] ;
        tag[rt] = 0 ;
    }
}
inline void _up(int rt){
    int ls = rt << 1 ;
    int rs = rt << 1 | 1 ;
    mxt[rt] = max(mxt[ls], mxt[rs]) ;
    mnv[rt] = min(mnv[ls], mnv[rs]) ;
    if (mnv[ls] < mnv[rs]){
        seg[rt] = seg[ls] ;
        lcon[rt] = lcon[ls] ;
        rcon[rt] = max(mxt[rs], rcon[ls]) ;
        //此处由于最后要覆盖，所以 max_Time(rc) 本质上就是包含右端点的值。
    }
    else if (mnv[ls] > mnv[rs]){
        seg[rt] = seg[rs] ;
        rcon[rt] = rcon[rs] ;
        lcon[rt] = max(mxt[ls], lcon[rs]) ;
    }
    else {
        lcon[rt] = lcon[ls] ; rcon[rt] = rcon[rs] ;
        seg[rt] = seg[ls] + seg[rs] + max(lcon[rs], rcon[ls]) ;
    }
}
void upd(int rt, int l, int r, int ul, int ur, int v){
    if (ul > ur) return ;
    if (ul <= l && r <= ur)
        return mnv[rt] += v, void(tag[rt] += v) ;
    int mid = (l + r) >> 1 ; _down(rt) ;
    if (ul <= mid) upd(lc, l, mid, ul, ur, v) ;
    if (ur > mid)  upd(rc, mid + 1, r, ul, ur, v) ;
    _up(rt) ;
}
void cov(int rt, int l, int r, int p, int v){
    if (l == r)
        return void(mxt[rt] = lcon[rt] = v) ;
    int mid = (l + r) >> 1 ; _down(rt) ;
    if (p <= mid) cov(lc, l, mid, p, v) ;
    else cov(rc, mid + 1, r, p, v) ; _up(rt) ;
}
int n, q ;
int base[N] ;
void mdf(int c, int mk){
    int w ;
    if (!(w = col[c].size())) return ;
//	printf("%d %d %d %d %d\n", c, mk, *col[c]._be(), *-- col[c]._en(), (int)col[c].size()) ;
    cov(1, 1, n, *col[c]._be(), mk > 0 ? w : 0) ;
    upd(1, 1, n, *col[c]._be(), *col[c]._en() - 1, mk) ;
}
int val_it(){ return n - seg[1] - lcon[1] - rcon[1] ; }

int main(){
	#ifdef LOCAL
		freopen("test.in","r",stdin);
		freopen("test.ans","w",stdout);
	#endif
    int x, y, z ;
    scanf("%d%d", &n, &q) ;
    for (int i = 1 ; i <= n ; ++ i)
        scanf("%d", &base[i]), col[base[i]].ins(i) ;
    for (int i = 1 ; i < N ; ++ i)
        mdf(i, 1) ; printf("%d\n", val_it()) ;
    while (q --){
        scanf("%d%d", &x, &y) ; z = base[x] ;
        mdf(z, -1) ; col[z].era(x) ; mdf(z, 1) ;
        mdf(y, -1) ; col[y].ins(x) ; mdf(y, 1) ;
        printf("%d\n", val_it()) ; base[x] = y ;
    }
    return 0 ;
}
