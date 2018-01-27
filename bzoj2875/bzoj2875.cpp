#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ll MOD,a,c,g,x0,n;

ll cheng(ll x,ll y){
	ll res=0;
	while(y>0){
		if(y&1) res=(res+x)%MOD;
		x=(x+x)%MOD,y>>=1;
	}
	return res;
}

struct matrix{
	int n,m;
	ll num[3][3];
	matrix(){		
		n=m=0;
		memset(num,0,sizeof(num));
	}
	matrix(int x,int y){
		n=x,m=y;
		memset(num,0,sizeof(num));
	}
	matrix operator * (const matrix &a)const{
		matrix c(n,a.m);
		for(int i=1;i<=c.n;i++)
			for(int j=1;j<=c.m;j++)
				for(int k=1;k<=m;k++)
					c.num[i][j]=(c.num[i][j]+cheng(num[i][k],a.num[k][j]))%MOD;
		return c;
	}
}p,q;

matrix pow(matrix x,ll k){
	matrix res(2,2);
	res.num[1][1]=res.num[2][2]=1;
	while(k){
		if(k&1) res=res*x;
		k>>=1,x=x*x;
	}
	return res;
}

int main(){
    freopen("bzoj2875.in","r",stdin);
    scanf("%lld %lld %lld %lld %lld %lld",&MOD,&a,&c,&x0,&n,&g);
    p=matrix(1,2); p.num[1][1]=x0%MOD,p.num[1][2]=1;
    q=matrix(2,2); q.num[1][1]=a%MOD,q.num[2][1]=c%MOD,q.num[2][2]=1;
    matrix ans=p*pow(q,n);
    printf("%lld",ans.num[1][1]%g);
    return 0;
}