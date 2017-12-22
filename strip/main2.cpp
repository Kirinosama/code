#include <cstdlib>
#include <cstdio>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

#define MAXN 100010

multiset<int> S;
priority_queue <pair<int,int> > Q;
int n,s,l,leftend[MAXN];
int now,a[MAXN],f[MAXN];

int main()
{
	freopen("input","r",stdin);
	cin>>n>>s>>l;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	now=0;
	for(int i=1;i<=n;i++)
	{
		S.insert(a[i]);
		while(*(--S.end())-*S.begin()>s)
		{
			S.erase(S.lower_bound(a[now+1]));
			now++;
		}
		leftend[i]=now;
	}
	memset(f,0x7f,sizeof(f));
	f[0]=0;
	Q.push(pair<int,int>(0,0));⁄
	for(int i=1;i<=n;i++)
	{
		
		if(i-l>0)
			Q.push(pair<int,int>(-f[i-l],i-l));
		if(leftend[i]>i-l)
		{
			f[i]=0x7f7f7f7f;
			continue;
		}
		while(Q.top().second<leftend[i])
			Q.pop();
		if(Q.top().first!=-0x7f7f7f7f)
			f[i]=-Q.top().first+1;
		else
			f[i]=0x7f7f7f7f;
	}
	if(f[n]!=0x7f7f7f7f)
		printf("%d",f[n]);
	else
		printf("-1");
	return 0;
}