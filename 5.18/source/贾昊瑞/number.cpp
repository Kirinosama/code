#include"bits/stdc++.h"
#define F(i,j,n) for(register int i=j;i<=n;i++)
#define D(i,j,n) for(register int i=j;i>=n;i--)
#define ll long long
#define N 110
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
int m,s,t,c[40],d[40];ll n,a,x,b[40],p[40],oo=1ll<<60;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	#endif
	gi(t);
	p[0]=1;F(i,1,20)p[i]=p[i-1]*10;
	while(t--){
		gi(n);m=0;a=n;
		memset(c,0,sizeof(c));
		while(n)c[++m]=n%10,n/=10;
		reverse(c+1,c+m+1);
//		F(i,1,m)printf("  %d",c[i]);puts("");
		F(i,2,m)if(c[i]!=0){
			n=0;F(j,i,m)n=n*10+c[j];
			x=0;F(j,1,i-1)x|=(c[j]!=9);
			if(x){F(j,1,i-1)n=n*10+c[j];n++;}
			else F(j,1,i-1)n=n*10;
			a=min(a,n);
		}
		F(i,1,m-1)F(j,1,min(i,m-i+1)){
			if(c[j]==0)continue;
			n=0;F(k,j,j+i-1)n=n*10+c[k];
//			printf("%d %d %lld\n",i,j,n);
			x=0;F(k,1,j-1)x=x*10+c[k];
			n--;
//			printf("		%lld %lld %lld\n",n,n%p[j-1],x);
			if(x!=n%p[j-1])continue;
			for(int l=j;l<=m;l+=i){
				n++;
				x=0;F(k,l,l+i-1)x=x*10+c[k];
//				printf("	%d %d %d %lld %lld %lld\n",l,l+i-1,m,p[l+i-1-m],n,x);
				if(l+i-1<=m)if(x!=n){n=oo;break;}
				if(l+i-1>m)if(x/p[l+i-1-m]!=n/p[l+i-1-m])n=oo;
			}
//			printf("%lld\n",n);
			a=min(a,n);
		}
		F(j,1,m)if(c[j]==1){
			int i=1;
			for(;i<m&&c[j+i]==0;i++){
				n=p[i];
//				printf("%d %lld\n",i,p[i]);
				for(int l=j-i;l+i>1;l-=i){
					n--;
					x=0;F(k,max(1,l),l+i-1)x=x*10+c[k];
//					printf("%d %lld %lld %lld %d\n",l,x,n,n%p[min(i,l+i-1)],min(i,l+i-1));
					if(n%p[min(i,l+i-1)]!=x){n=oo;break;}
				}
				if(n==oo)continue;
				n=p[i];
				for(int l=j+i+1;l<=m;l+=i+1){
					n++;
					x=0;F(k,l,l+i)x=x*10+c[k];
					if(l+i<=m)if(x!=n){n=oo;break;}
					if(l+i>m)if(x/p[l+i-m]!=n/p[l+i-m])n=oo;
				}
//				printf("%lld\n",n);
				a=min(a,n);
			}
		}
		printf("%lld\n",a);
	}
	return 0;
}

