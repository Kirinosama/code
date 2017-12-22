#include <cstdlib>
#include <cstdio>
#include <queue>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAXN 100010

int f[MAXN];
int n,s,l,book[MAXN];
pair<int,int> p1[MAXN],p2[MAXN];
priority_queue < pair<int,int> > Q1;
priority_queue < pair<int,int> > Q2;
//优先队列
int main()
{
	freopen("input","r",stdin);
	cin>>n>>s>>l;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&p2[i].first);
		p2[i].second=p1[i].second=i;
		p1[i].first=-p2[i].first;
		Q1.push(p1[i]);Q2.push(p2[i]);
	}
	memset(f,0x7f,sizeof(f));
	memset(book,1,sizeof(book));
	f[0]=0;
	for(int i=0;i<=n;i++)
	{
		if(f[i]==0x7f7f7f7f)
			continue;
		for(int j=i+l;j<=n;j++)
		{
			if(!book[p1[j].second])
			{
				Q1.push(p1[j]); 
				Q2.push(p2[j]);
				book[p1[j].second]=1;
			}
			while(Q1.top().second<i+1 || Q1.top().second>j)
			{
				book[Q1.top().second]=0;
				Q1.pop();
			}
			while(Q2.top().second<i+1 || Q2.top().second>j)
			{
				book[Q2.top().second]=0;
				Q2.pop();
			}
			int min1=-Q1.top().first;
			int max1=Q2.top().first;
			if(max1-min1>s)
				break;
			f[j]=min(f[j],f[i]+1);
		}
	}
	if(f[n]!=0x7f7f7f7f)
		printf("%d",f[n]);
	else
		printf("-1");
	return 0;
}