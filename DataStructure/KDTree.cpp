const ll INF = pw(62);
const int N = 100005;

int T, n, Q, D;
ll now;

struct node{
	int d[2], l, r, mi[2], ma[2];//sum, val, minp, p, id;
	bool operator <(const node &b)const{
		return d[Q] < b.d[Q];
	}
};

node a[N], ans, v, b[N];

struct KDTree{
	static const int N = 1e5 + 7;
	int root;
	node tr[N];

	inline void up(node &a, const node &b){
		rep(i, 0, D) {
			a.mi[i] = min(a.mi[i], b.mi[i]);
			a.ma[i] = max(a.ma[i], b.ma[i]);
		}
	}
	inline void insert(int now){
		int k = 0, p = root;
		if (!p) {root = now;return;}
		while (1) {
			up(tr[p], tr[now]);
    		if(tr[now].d[k] >= tr[p].d[k]){
        		if (!tr[p].r) {tr[p].r = now;return;}
				else p = tr[p].r;
    		}else{
        		if (!tr[p].l) {tr[p].l = now;return;}
        		else p = tr[p].l;
    		}
       		k = (k + 1) % D;
		}
	}

	int build(int l,int r,int k) {
		if (l > r) return 0;
		int mid = l+r>>1; Q = k;
		nth_element(a+l, a+mid, a+r+1);
		tr[mid] = a[mid];
		rep(i, 0, D) tr[mid].ma[i] = tr[mid].mi[i] = tr[mid].d[i];
		tr[mid].l = build(l, mid-1, k^1);
		tr[mid].r = build(mid+1, r, k^1);
		if (tr[mid].l) up(tr[mid], tr[tr[mid].l]);
		if (tr[mid].r) up(tr[mid], tr[tr[mid].r]);
		return mid;
	}

	inline ll sqr(ll x) {return x * x;}

	inline ll get(const node &v, int x) { // dis function need update 
		if (!x) return INF+1;
		ll res = 0;
		rep(i, 0, D) {
			if (v.d[i] < tr[x].mi[i]) res += sqr(tr[x].mi[i] - v.d[i]);
			if (v.d[i] > tr[x].ma[i]) res += sqr(v.d[i] - tr[x].ma[i]);
 		}
		return res;
	}
 
	inline void check(const node &v, const node &p) {  
		ll dis = 0;
		rep(i, 0, D) dis += sqr(p.d[i] - v.d[i]);
		if (dis) now = min(now, dis);
		return;
	}
 
	void ask(const node &v, int x) {
		if (!x) return;
		check(v, tr[x]);
		ll lm = get(v, tr[x].l), rm = get(v, tr[x].r);
		if (lm < rm) {
			if (lm <= now) ask(v, tr[x].l);
			if (rm <= now) ask(v, tr[x].r);
		}else {
			if (rm <= now) ask(v, tr[x].r);
			if (lm <= now) ask(v, tr[x].l);
		}
	}
} kdt;
