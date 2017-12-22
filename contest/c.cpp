#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

int a[20];
long long ans,anss;

struct node
{
	long long x,y,num;
}card[20];

vector <int> v[20];
int n,m;

int main()
{
	freopen("input","r",stdin);
	anss=0x7fffffffffffffff;
	srand(time(0)+529);
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld %lld %lld",&card[i].x,&card[i].y,&card[i].num);
	}
	if(m>=n)
		printf("0");
	else
	{
		for(int i=1;i<=n;i++)
			a[i]=i;
		for(int z=1;z<=10000000;z++)
		{
			ans=0;
			for(int i=1;i<=m;i++)
				v[i].clear();
			random_shuffle(a+1,a+1+n);
			for(int i=1;i<=m;i++)
				v[i].push_back(a[i]);
			for(int i=m+1;i<=n;i++)
			{
				int pos=rand()%m+1;
				v[pos].push_back(a[i]);
			}		
			for(int i=1;i<=m;i++)
			{
				long long res=0;
				long long cnt=0;
				long long xx=0;
				long long yy=0;
				for(int j=0;j<v[i].size();j++)
				{
					res+=card[v[i][j]].num*card[v[i][j]].x*card[v[i][j]].y;
					cnt+=card[v[i][j]].num;
					xx=max(xx,card[v[i][j]].x);
					yy=max(yy,card[v[i][j]].y);
				}
				ans+=xx*yy*cnt-res;
			}
			//cout<<ans<<endl;
			anss=min(ans,anss);
			// for(int i=1;i<=m;i++)
			// {
			// 	printf("%d:",i);
			// 	for(int j=0;j<v[i].size();j++)
			// 	printf("%d ",v[i][j]);
			// 	printf("\n");
			// }
			// printf("\n");
		}
		cout<<anss;
	}

	return 0;
}