#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n,m;

vector <int> f[70][70][70];

vector<int> operator + (const vector<int> &a,const vector<int> &b)
{
	int la=a.size()-1;
	int lb=b.size()-1;
	vector<int> c;
	int rem=0;
	for(int i=0;i<=max(la,lb);i++)
	{
		c.push_back(0);
		if(i<=lb)
		c[i]+=b[i];
		if(i<=la)
		c[i]+=a[i];
		c[i]+=rem;
		rem=c[i]/10;
		c[i]%=10;
	}
	if(rem>0)
	{
		c.push_back(rem);
	}
	return c;
}

int main()
{
	freopen("input","r",stdin);
	n=60;
	f[0][0][0].push_back(1);
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=i;j++)
		{
			for(int k=0;k<=j;k++)
			{
				f[i][j][k].push_back(0);
				if(i-1>=0 && i-1>=j)
				f[i][j][k]=f[i][j][k]+f[i-1][j][k];
				if(j-1>=0 && j-1>=k)
				f[i][j][k]=f[i][j][k]+f[i][j-1][k];
				if(k-1>=0)
				f[i][j][k]=f[i][j][k]+f[i][j][k-1];	
				// printf("f[%d][%d][%d]=",i,j,k);
				// for(int z=f[i][j][k].size()-1;z>=0;z--)
				// 	printf("%d",f[i][j][k][z]);
				// printf("\n");
			}
		}	
	}
	while(scanf("%d",&m)!=EOF)
	{
		for(int i=f[m][m][m].size()-1;i>=0;i--)
			printf("%d",f[m][m][m][i]);
		cout<<endl;cout<<endl;
	}
	return 0;	
}