// created time: 2026-06-08
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fi first
#define se second
#define mkp make_pair

inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
inline int lg2(int x){ return 31^__builtin_clz(x); }

const int N = 200005;
int n, q, a[N], ans[N], v[N], vn;
int inl[N], inr[N];
int sid0[N], sn0;
int qL0[N], qR0[N], qn0;
int aqL[N], aqR[N];

struct GlobalSeg {
	int mx[N*4], mn[N*4];
	void bld(int l, int r, int p, int *il, int *ir){
		if(l==r){ mx[p]=il[l]; mn[p]=ir[l]; return; }
		int m=(l+r)>>1;
		bld(l, m, p<<1, il, ir); bld(m+1, r, p<<1|1, il, ir);
		mx[p] = max(mx[p<<1], mx[p<<1|1]);
		mn[p] = min(mn[p<<1], mn[p<<1|1]);
	}
	int qmx(int l, int r, int ql, int qr, int p){
		if(r<ql || qr<l) return -2e9;
		if(ql<=l && r<=qr) return mx[p];
		int m=(l+r)>>1;
		return max(qmx(l, m, ql, qr, p<<1), qmx(m+1, r, ql, qr, p<<1|1));
	}
	int qmn(int l, int r, int ql, int qr, int p){
		if(r<ql || qr<l) return 2e9;
		if(ql<=l && r<=qr) return mn[p];
		int m=(l+r)>>1;
		return min(qmn(l, m, ql, qr, p<<1), qmn(m+1, r, ql, qr, p<<1|1));
	}
	void umx(int l, int r, int id, int val, int p){
		if(l==r){ mx[p]=val; return; }
		int m=(l+r)>>1;
		if(id<=m) umx(l, m, id, val, p<<1);
		else umx(m+1, r, id, val, p<<1|1);
		mx[p] = max(mx[p<<1], mx[p<<1|1]);
	}
	void umn(int l, int r, int id, int val, int p){
		if(l==r){ mn[p]=val; return; }
		int m=(l+r)>>1;
		if(id<=m) umn(l, m, id, val, p<<1);
		else umn(m+1, r, id, val, p<<1|1);
		mn[p] = min(mn[p<<1], mn[p<<1|1]);
	}
} GS;

struct DPSeg {
	int val[N*4], tag[N*4], id[N*4];
	void pushup(int p){
		if(val[p<<1] >= val[p<<1|1]){
			val[p] = val[p<<1]; id[p] = id[p<<1];
		} else {
			val[p] = val[p<<1|1]; id[p] = id[p<<1|1];
		}
	}
	void upd(int p, int v){
		tag[p] += v; val[p] += v;
	}
	void pushdown(int p){
		if(tag[p]){
			upd(p<<1, tag[p]); upd(p<<1|1, tag[p]);
			tag[p] = 0;
		}
	}
	void bld(int l, int r, int p){
		tag[p] = 0;
		if(l==r){ val[p]=-1e9; id[p]=l; return; }
		int m=(l+r)>>1;
		bld(l, m, p<<1); bld(m+1, r, p<<1|1);
		pushup(p);
	}
	void update(int l, int r, int ql, int qr, int v, int p){
		if(r<ql || qr<l) return;
		if(ql<=l && r<=qr){ upd(p, v); return; }
		int m=(l+r)>>1; pushdown(p);
		update(l, m, ql, qr, v, p<<1); update(m+1, r, ql, qr, v, p<<1|1);
		pushup(p);
	}
	void ptupd(int l, int r, int idx, int v, int p){
		if(l==r){ val[p]=v; return; }
		int m=(l+r)>>1; pushdown(p);
		if(idx<=m) ptupd(l, m, idx, v, p<<1);
		else ptupd(m+1, r, idx, v, p<<1|1);
		pushup(p);
	}
	pair<int,int> qry(int l, int r, int ql, int qr, int p){
		if(r<ql || qr<l) return mkp(-1e9, -1);
		if(ql<=l && r<=qr) return mkp(val[p], id[p]);
		int m=(l+r)>>1; pushdown(p);
		pair<int,int> L = qry(l, m, ql, qr, p<<1);
		pair<int,int> R = qry(m+1, r, ql, qr, p<<1|1);
		return (L.fi >= R.fi) ? L : R;
	}
} S0, S1;

int memS[N*25], topS;
int memQl[N*45], memQr[N*45], topQ;

int head0[N], nxt0[N*4], to0[N*4], tot0;
int head1[N], nxt1[N*4], to1[N*4], tot1;
int dp0[N], dp1[N], ch0[N], ch1[N], asg[N];

void solve(int L, int R, int *sid, int sn, int *ql, int *qr, int qn){
	if(sn == 0) return;
	if(L == R){
		for(int i=0; i<sn; ++i) ans[sid[i]] = v[L];
		return;
	}
	int mid = L + (R-L)/2, mv = v[mid];
	
	for(int i=0; i<=sn; ++i) head0[i] = head1[i] = 0;
	tot0 = tot1 = 0;
	
	for(int i=0; i<qn; ++i){
		int l = ql[i], r = qr[i];
		int lb = lower_bound(sid, sid+sn, l) - sid + 1;
		int rb = upper_bound(sid, sid+sn, r) - sid;
		if(lb <= rb){
			if(GS.qmx(1, n, l, r, 1) <= mv){
				to0[++tot0] = lb; nxt0[tot0] = head0[rb]; head0[rb] = tot0;
			}
			if(GS.qmn(1, n, l, r, 1) > mv){
				to1[++tot1] = lb; nxt1[tot1] = head1[rb]; head1[rb] = tot1;
			}
		}
	}
	
	S0.bld(0, sn, 1); S1.bld(0, sn, 1);
	S0.ptupd(0, sn, 0, 0, 1); S1.ptupd(0, sn, 0, 0, 1);
	
	for(int i=1; i<=sn; ++i){
		for(int e=head0[i]; e; e=nxt0[e]) S0.update(0, sn, 0, to0[e]-1, 1, 1);
		for(int e=head1[i]; e; e=nxt1[e]) S1.update(0, sn, 0, to1[e]-1, 1, 1);
		
		pair<int,int> q0 = S0.qry(0, sn, 0, i-1, 1);
		dp0[i] = q0.fi; ch0[i] = q0.se;
		pair<int,int> q1 = S1.qry(0, sn, 0, i-1, 1);
		dp1[i] = q1.fi; ch1[i] = q1.se;
		
		S0.ptupd(0, sn, i, dp1[i], 1); S1.ptupd(0, sn, i, dp0[i], 1);
	}
	
	int cur = sn, c = (dp0[sn] >= dp1[sn]) ? 0 : 1;
	while(cur > 0){
		int nx = (c == 0) ? ch0[cur] : ch1[cur];
		for(int j=nx+1; j<=cur; ++j) asg[j] = c;
		cur = nx; c = 1 - c;
	}
	
	int snL = 0, snR = 0;
	for(int i=1; i<=sn; ++i) if(asg[i] == 0) snL++; else snR++;
	
	int stS = topS;
	int *sidL = memS + topS; topS += snL;
	int *sidR = memS + topS; topS += snR;
	
	int pL = 0, pR = 0;
	for(int i=1; i<=sn; ++i){
		if(asg[i] == 0){
			sidL[pL++] = sid[i-1]; GS.umn(1, n, sid[i-1], mv, 1);
		} else {
			sidR[pR++] = sid[i-1]; GS.umx(1, n, sid[i-1], v[mid+1], 1);
		}
	}
	
	int stQ = topQ;
	int *qlL = memQl + topQ, *qrL = memQr + topQ; int qnL = 0;
	int *qlR = memQl + topQ + qn, *qrR = memQr + topQ + qn; int qnR = 0;
	
	for(int i=0; i<qn; ++i){
		int l = ql[i], r = qr[i];
		bool l0 = GS.qmx(1, n, l, r, 1) <= mv, l1 = GS.qmn(1, n, l, r, 1) > v[L];
		int p1 = lower_bound(sidL, sidL+snL, l) - sidL;
		if((l0 || l1) && p1 < snL && sidL[p1] <= r){ qlL[qnL] = l; qrL[qnL] = r; qnL++; }
		
		bool r0 = GS.qmx(1, n, l, r, 1) <= v[R], r1 = GS.qmn(1, n, l, r, 1) > mv;
		int p2 = lower_bound(sidR, sidR+snR, l) - sidR;
		if((r0 || r1) && p2 < snR && sidR[p2] <= r){ qlR[qnR] = l; qrR[qnR] = r; qnR++; }
	}
	
	int *nqlR = memQl + topQ + qnL, *nqrR = memQr + topQ + qnL;
	for(int i=0; i<qnR; ++i){ nqlR[i] = qlR[i]; nqrR[i] = qrR[i]; }
	topQ += qnL + qnR;
	
	solve(L, mid, sidL, snL, qlL, qrL, qnL);
	solve(mid+1, R, sidR, snR, nqlR, nqrR, qnR);
	
	topS = stS; topQ = stQ;
}

int rmqMx[20][N], rmqMn[20][N];

int main(){
	n = read(); q = read();
	if(n == 0) return 0;
	
	for(int i=1; i<=n; ++i){
		a[i] = read();
		if(a[i] > 0) v[vn++] = a[i];
		else sid0[sn0++] = i;
	}
	if(vn > 0){
		sort(v, v+vn); vn = unique(v, v+vn) - v;
	} else { v[0] = 1; vn = 1; }
	
	for(int i=1; i<=n; ++i){
		if(a[i] > 0) inl[i] = inr[i] = a[i];
		else { inl[i] = v[0]; inr[i] = v[vn-1]; }
	}
	GS.bld(1, n, 1, inl, inr);
	
	for(int i=0; i<q; ++i){
		int l = read(), r = read();
		aqL[i] = l; aqR[i] = r;
		int pos = lower_bound(sid0, sid0+sn0, l) - sid0;
		if(pos < sn0 && sid0[pos] <= r){
			qL0[qn0] = l; qR0[qn0] = r; qn0++;
		}
	}
	
	solve(0, vn-1, sid0, sn0, qL0, qR0, qn0);
	
	for(int i=1; i<=n; ++i) rmqMx[0][i] = rmqMn[0][i] = (a[i] > 0 ? a[i] : ans[i]);
	for(int j=1; j<=19; ++j){
		for(int i=1; i+(1<<j)-1<=n; ++i){
			rmqMx[j][i] = max(rmqMx[j-1][i], rmqMx[j-1][i+(1<<(j-1))]);
			rmqMn[j][i] = min(rmqMn[j-1][i], rmqMn[j-1][i+(1<<(j-1))]);
		}
	}
	
	ll tot = 0;
	for(int i=0; i<q; ++i){
		int l = aqL[i], r = aqR[i];
		int j = lg2(r-l+1);
		int mx = max(rmqMx[j][l], rmqMx[j][r-(1<<j)+1]);
		int mn = min(rmqMn[j][l], rmqMn[j][r-(1<<j)+1]);
		tot += (mx - mn);
	}
	printf("%lld\n", tot);
	return 0;
}