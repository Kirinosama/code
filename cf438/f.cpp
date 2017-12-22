#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
	freopen("input","r",stdin);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=k;j++)
		{
			for(int st=0;st<=i;st++)
			{
				if(st==i)
					for(int st1=0;st1<i;st1++)
						f[i][j][st]=min(f[i-1][j-1][st1]);
				else
					for(int st1=0;st1<i;st1++)
						f[i][j][st]=min(f[i-1][j][st1]+cal(st1,i-1,i));
			}
		}
	return 0;
}