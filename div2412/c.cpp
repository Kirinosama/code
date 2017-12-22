#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
#include <cmath>
using namespace std;

#define MAXN 1010
const double eps=1e-8;

int n,book[MAXN],ans;

struct node
{
	double x[6];
	double len;

	void init()
	{
		len=0;
		for(int i=1;i<=5;i++) 
			len+=x[i]*x[i];
		len=sqrt(len);
	}
	void in()
	{
		for(int i=1;i<=5;i++) 
			scanf("%lf",&x[i]);
		init();
	}

	node operator - (node a)
	const{
		node b;
		for(int i=1;i<=5;i++)
			b.x[i]=x[i]-a.x[i]; 
		b.init();
		return b;
	}

	double operator * (node a)
	const{
		double cur=0;
		for(int i=1;i<=5;i++) cur+=x[i]*a.x[i];
		return cur;
	}
}p[MAXN];

bool judge(int k)
{
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		{
			if(i==k || j==k) continue;
			node s1=p[i]-p[k];
			node s2=p[j]-p[k];
			if(acos(s1*s2/(s1.len*s2.len))<M_PI/2)
				return false;
		}
	return true;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) p[i].in();
	for(int i=1;i<=n;i++) 
		if(judge(i))
			ans++,book[i]=1;
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)
		if(book[i])
			printf("%d ",i);
	return 0;
}