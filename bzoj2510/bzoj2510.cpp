#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 110
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct matrix{
	int x,y;
	double num[MAXN][MAXN];
	void clear(){
		x=y=0;
		memset(num,0,sizeof(num));
	}
	matrix operator*(matrix a){
		matrix ans;ans.clear();
		ans.x=x,ans.y=a.y;
		for(int i=1;i<=x;i++)
			for(int j=1;j<=a.y;j++)
				for(int k=1;k<=y;k++)
					ans.num[i][j]+=num[i][k]*a.num[k][j];
		return ans;
	}
}res,mul,ans;

int n,k;
double m;

int main(){
    freopen("bzoj2510.in","r",stdin);
    scanf("%d %lf %d",&n,&m,&k);res.clear(),res.x=1,res.y=n;
    for(int i=1;i<=n;i++) scanf("%lf",&res.num[1][n]);
    mul.clear(),mul.x=1,mul.y=n;
	mul.num[1][1]=1.0-1.0/m;
	mul.num[1][2]=1.0/m;
	ans.clear(),ans.x=1,ans.y=1,ans.num[1][1]=1.0;
	while(k){
		if(k&1) ans=ans*mul;
		mul=mul*mul,k>>=1;
	}
	ans.x=n; 
	for(int i=2;i<=n;i++)
		for(int j=1;j<=n;j++)
			ans.num[i][j]=ans.num[i-1][j==1?n:j-1];
	res=res*ans;
	for(int i=1;i<=n;i++)
		printf("%.3f\n",res.num[1][i]);
    return 0;
}