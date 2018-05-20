#include"bits/stdc++.h"
#define F(i,j,n) for(register int i=j;i<=n;i++)
#define D(i,j,n) for(register int i=j;i>=n;i--)
#define ll long long
#define N 510
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
int n,x[N],d,a,b,f[N],ans,as;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("point.in","r",stdin);
	freopen("point.out","w",stdout);
	#endif
	gi(n);gi(d);gi(a);gi(b);d*=2;
	F(i,1,n)gi(x[i]),f[x[i]]=1;
	if(a<=b){
		n=0;F(i,1,N-1)n+=f[i];
		F(i,1,N-d)if(f[i])
			if(f[i+d])f[i+d]=0,n--;
		printf("%d\n",n*a);
		return 0;
	}
	sort(x+1,x+n+1);
	n=unique(x+1,x+n+1)-x-1;
	if(n<=20){
		ans=n*a;
		F(j,0,(1<<n)-2){
			F(i,1,n)f[i]=x[i]+d*((j>>i-1)&1);
			as=n*a;
			sort(f+1,f+n+1);
			F(i,2,n)as-=max(0,a-(f[i]-f[i-1])*b);
//			F(i,1,n)printf("%d ",f[i]);printf(" :%d\n",as);
			ans=min(ans,as);
		}
		printf("%d\n",ans);
	}
	return 0;
}

