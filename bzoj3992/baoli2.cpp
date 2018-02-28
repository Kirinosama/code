#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define Mod 1004535809
#define MAXM 8010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,x,s;
int cnt[MAXM];

struct matrix{
	int n,m;
	ll num[300][300];
	matrix(){n=m=0;memset(num,0,sizeof(num));}
	matrix(int x,int y){n=x,m=y,memset(num,0,sizeof(num));}
	matrix operator *(const matrix &a)const{
		matrix c(n,a.m);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=a.m;j++)
				for(int k=1;k<=m;k++)
					c.num[i][j]+=num[i][k]*a.num[k][j],c.num[i][j]%=Mod;
		return c;
	}
};


matrix pow(matrix x,int k){
	matrix res(m-1,m-1);
	for(int i=1;i<=m-1;i++) res.num[i][i]=1;
	while(k){
		if(k&1) res=res*x;
		x=x*x,k>>=1;
	}
	return res;
}

int main(){
    freopen("bzoj3994.in","r",stdin);
    cin>>n>>m>>x>>s;
    for(int i=1;i<=s;i++){
    	static int t;
    	scanf("%d",&t),cnt[t]=1;
    }
    matrix b(m-1,m-1);
    for(int i=1;i<=m-1;i++)
    	for(int j=1;j<m;j++)
    		if(cnt[j]) b.num[i][(i*j)%m]=1;
    matrix a(1,m-1);
    for(int i=1;i<m;i++)
    	if(cnt[i]) a.num[1][i]=1;
    a=a*pow(b,n-1);
    printf("%lld",a.num[1][x]);
    return 0;
}