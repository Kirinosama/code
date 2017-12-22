#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXN 50010

struct sq
{
	int x,y;
	void in(){scanf("%d %d",&x,&y);}
}t[MAXN];

typedef long long ll;
sq p[MAXN];
int maxy,cnt,n;
ll f[MAXN];

bool cmp(sq &a,sq &b)
{
	if(a.x==b.x) return a.y<b.y;
	return a.x<b.x;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		t[i].in();
	sort(t+1,t+1+n,cmp);
	for(int i=n;i>=1;i--)
	{
		if(maxy<t[i].y) p[++cnt]=t[i];
		maxy=max(maxy,t[i].y);
	}
	n=cnt;
	for(int i=1;i<=cnt;i++) t[i]=p[cnt-i+1];
	memset(f,0x7fff,sizeof(f));
	f[0]=0;
	l=0;r=0;
	for(int i=1;i<=n;i++)
	{
		while(l+1<r && cal(l,l+1)<t[])
	cout<<f[n];
	return 0;
}