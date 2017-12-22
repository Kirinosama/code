#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

double ch[30][30];
double f[30],p;
int n;

double pow2(double x,int k)
{
	if(k==0)
		return 1.000000;
	if(k==1)
		return x;
	if(k%2==1)
		return x*pow2(x,k-1);
	else
		return pow2(x*x,k/2);
}

double dp(int x)
{
	if(x==1)
		return f[x]=1.000000;
	if(f[x])
		return f[x];
	double minus=0.000000;
	for(int i=1;i<=x-1;i++)
		minus+=ch[x-1][i-1]*dp(i)*pow2(1-p,i*(x-i));
	return f[x]=1.000000-minus;
}

int main()
{
	freopen("input","r",stdin);
	for(int i=0;i<=20;i++)
		ch[i][0]=1.000000;
	for(int i=1;i<=20;i++)
		for(int j=1;j<=i;j++)
			ch[i][j]=ch[i-1][j]+ch[i-1][j-1];
	while(scanf("%d %lf",&n,&p)!=EOF)
	{	
		memset(f,0,sizeof(f));
		cout<<dp(n)<<endl;
	}
	return 0;
}