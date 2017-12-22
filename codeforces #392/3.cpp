#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 200

long long  n,m,x,y;
long long k;
long long max1,min1;
long long start[3][MAXN][MAXN];
long long cnt[MAXN][MAXN];

const long long INF=1000000000000000000ULL;

int main()
{
	freopen("input","r",stdin);
	min1=INF;
	cin>>n>>m>>k>>x>>y;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			start[1][i][j]=(i-1)*m+j;
			start[2][i][j]=(n+n-i-i)*m+start[1][i][j];
			long long turns=(n+n-2)*m;
			if(n==1)
				turns=m;
			if(k>=start[1][i][j])
			{
				cnt[i][j]++;
				if(k-start[1][i][j]>0)
					cnt[i][j]+=(long long)((k-start[1][i][j])/turns);
			}
			if(k>=start[2][i][j] && i!=1 && i!=n)
			{
				cnt[i][j]++;
				if(k-start[2][i][j]>0)
					cnt[i][j]+=(long long)((k-start[2][i][j])/turns);
			}
			max1=max(max1,cnt[i][j]);
			min1=min(min1,cnt[i][j]);
		}
		cout <<max1<<' '<<min1<<' '<<cnt[x][y];
	return 0;
}