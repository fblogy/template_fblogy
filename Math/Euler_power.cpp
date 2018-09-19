int phi(int n) {
	if (M.count(n)==1) return M[n];
	int r=n,nn=n;
	for(int i=2;i*i<=n;i++) if (n%i==0){
		r=r/i*(i-1);
		while (n%i==0) n/=i;
	}
	if (n>1) r=r/n*(n-1);
	M[nn]=r;
	return r;
}

ll Euler_qpow(ll a,ll b,ll mod) {
	ll res=1;bool ok=(b>0 && a>=mod);
	while (b>0) {
		if (b&1) {
			res=res*a;
			ok|=(res>=mod);
			res%=mod;			
		}
		a=a*a;
		ok|=(b>1 && a>=mod);
		a%=mod;
		b>>=1;
	}
	return res+mod*ok;
}

ll work(int l,int r,int mod) {
	if (mod==1) return 1;
	if (l==r) return a[l];
	return Euler_qpow(a[l],work(l+1,r,phi(mod)),mod);
}
