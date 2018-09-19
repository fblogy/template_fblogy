const int N=1e5+7;
int n;
ll a[N], mod[N], M , R;

void exgcd(ll a,ll b,ll &x,ll &y){
    if(b == 0){
        x = 1; y = 0;
        return;
    }
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}

ll Inv(ll a, ll mod){
    ll x = 0, y = 0;
    exgcd(a, mod, x, y);
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

ll CRT(int n, ll *a, ll *mod){
    M = mod[1], R = a[1];
    rep(i, 2, n+1) {
        ll g=__gcd(M, mod[i]);
        ll inv = Inv(M / g, mod[i] / g);
        if ((a[i] - R) % g) return -1; // 无解 
        R += inv * ((a[i] - R) / g) % (mod[i] / g) * M;  
        M = M / g * mod[i];
        R = (R % M + M) % M; // 可能为 0 看是否需要是正整数 
    }
    return R;
}

