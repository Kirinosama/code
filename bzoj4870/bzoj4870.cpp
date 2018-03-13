#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,k,r;
ll p;

struct matrix{
	ll num[60][60];
	int n,m;
	matrix(){n=m=0;memset(num,0,sizeof(num));}
	matrix(int x,int y){n=x,m=y;memset(num,0,sizeof(num));}
	matrix operator * (const matrix &a)const{
		matrix c(n,a.m);
		for(int i=0;i<n;i++)
			for(int j=0;j<a.m;j++)
				for(int k=0;k<m;k++)
					c.num[i][j]=(c.num[i][j]+num[i][k]*a.num[k][j])%p;
		return c;
	}
};

matrix pow(matrix x,ll t){
	matrix res(k,k);
	for(int i=0;i<k;i++)res.num[i][i]=1;
	while(t){
		if(t&1) res=res*x;
		x=x*x;t>>=1;
	}
	return res;
}

int main(){
    freopen("bzoj4870.in","r",stdin);
    cin>>n>>p>>k>>r;
    matrix A(1,k),B(k,k);
    A.num[0][0]=1;
    for(int i=0;i<k;i++)B.num[i][i]++,B.num[i][(i+1)%k]++;
    matrix ans=A*pow(B,n*(ll)k);
	printf("%lld",ans.num[0][r]);
    return 0;
}