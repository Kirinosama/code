#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const double INF=1e20	;
const double eps=1e-8;
#define MAXN 210

struct node
{
	double x,y;
}p[MAXN];

int n,cnt,ans;
double l[MAXN*MAXN];

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lf %lf",&p[i].x,&p[i].y);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		{
			if(p[j].x==p[i].x) l[++cnt]=INF;
			else l[++cnt]=(p[j].y-p[i].y)/(p[j].x-p[i].x);
		}
	sort(l+1,l+1+cnt);
	for(int i=1;i<=cnt;i++)
		if(fabs(l[i]-l[i-1])>eps) ans++;
	cout<<ans;
	return 0;
}