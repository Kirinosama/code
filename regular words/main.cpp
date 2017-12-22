#include <cstdlib>
#include <cstdio>

int n;
int f[200][200][200];

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	f[1][1][0]=1;
	for(int i=2;i<=3*n;i++)
	{
		for(int j=0;j<=n;j++)
			for(int k=0;k<=n;k++)
			{
				if((i+2*j+k)/3>n)
					continue;
				if((i+k-j)/3<0 || (i+k-j)/3>n)
					continue;
				if((i-j-2*k)/3<0 || (i-j-2*k)/3>n)
					continue;
				if(j-1>=0 && k>=0)
					f[i][j][k]+=f[i-1][j-1][k];
				if(j+1>=0 && k-1>=0)
					f[i][j][k]+=f[i-1][j+1][k-1];
				if(j>=0 && k+1>=0)
					f[i][j][k]+=f[i-1][j][k+1];
			}
	}
	if(n>0)
		printf("%d",f[3*n][0][0]);
	else
		printf("1");
	return 0;
}