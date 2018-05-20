#include"bits/stdc++.h"
#define F(i,j,n) for(register int i=j;i<=n;i++)
#define D(i,j,n) for(register int i=j;i>=n;i--)
#define ll long long
#define N 1000
#define M 1010
using namespace std;
namespace io{
	const int L=(1<<19)+1;
	char ibuf[L],*iS,*iT,c;int f;
	char gc(){
		if(iS==iT){
			iT=(iS=ibuf)+fread(ibuf,1,L,stdin);
			return iS==iT?EOF:*iS++;
		}
		return*iS++;
	}
	template<class I>void gi(I&x){
		for(f=1,c=gc();c<'0'||c>'9';c=gc())if(c=='-')f=-1;
		for(x=0;c<='9'&&c>='0';c=gc())x=x*10+(c&15);x*=f;
	}
};
using io::gi;
using io::gc;
int a[M],f[M][M],h[M],x[M],m,t,n,p;
void dfs(int n,int m,ll s){
	if(s>=N||m>=N)return;
//	printf("%d %d %lld\n",n,m,s);
//	printf("	%d %d %lld\n",n+1,m+1,s+m);
//	printf("	%d %d %lld\n",n,n+m,s+(ll)(n-1)*(n+m)-n*(n-1)/2);
	if(m<a[s]){a[s]=m;h[s]=n;F(i,1,n)f[s][i]=x[i];}
	x[n+1]=1;dfs(n+1,m+1,s+m);
	F(i,1,n)x[i]++;
	dfs(n,n+m,s+(ll)(n-1)*(n+m)-n*(n-1)/2);
	F(i,1,n)x[i]--;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	#endif
	F(i,1,N)a[i]=i+1,h[i]=2,f[i][1]=1,f[i][2]=i;
	x[1]=1;dfs(1,1,0);
	gi(t);
	while(t--){
		gi(n);
		if(n<=1000){
			F(i,1,h[n])F(j,1,f[n][i])printf("%d",i&1);
			puts("");continue;
		}
		n*=2;
		for(m=1;m*(m-1)<n;m++);
//		printf("%d %d %d\n",m,n,m*m);
		n=m*m-n;
		p=1;
		D(i,m,1)while(n>=i*i){
			n-=i*i;
			F(j,1,i)printf("%d",p);p^=1;
		}
		puts("");
	}
	return 0;
}

