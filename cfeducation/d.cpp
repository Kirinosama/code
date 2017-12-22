#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 200010
#define MAXM 200
#define MAXQ 200010

int a[MAXN],b[MAXM],n,m,q;

struct que
{
	int type,l,r;
	void in()
	{
		scanf("%d %d %d",&type,&l,&r);
	}
}query[MAXQ];

void solve(int cur)
{
	int type=query[cur].type;
	int l=query[cur].l;
	int r=query[cur].r;
	for(int i=1;i<=m;i++)
	{
		int pos=b[i];
		if(pos>r || pos<l) continue;
		if(type==1)
		{
			if(pos==l) pos=r;
			else pos--;
		}
		else
			pos=l+r-pos;
		b[i]=pos;
	}
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d %d",&n,&q,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=q;i++) query[i].in();
	for(int i=1;i<=m;i++) scanf("%d",&b[i]);
	for(int i=q;i>=1;i--) solve(i);
	for(int i=1;i<=m;i++) printf("%d ",a[b[i]]);
	return 0; 
}