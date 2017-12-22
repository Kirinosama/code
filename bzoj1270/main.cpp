#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
using namespace std;

set <int> s;
int n,m,father[2010],ans;

int find(int x)
{
	if(father[x]!=x) father[x]=find(father[x]);
	return father[x];
}

void merge(int x,int y)
{
	int fx=find(x);
	int fy=find(y);
	if(fx!=fy) father[fx]=fy;
}

void read()
{
	char ch;
	int x,y;
	scanf("%c %d %d\n",&ch,&x,&y);
	if(ch=='F') merge(x,y);
	else merge(x+n,y),merge(x,y+n);
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d\n",&n,&m);
	for(int i=1;i<=2*n;i++) father[i]=i;
	for(int i=1;i<=m;i++) read();
	for(int i=1;i<=n;i++)
	{
		int fa=find(i);
		if(!s.count(fa)) ans++,s.insert(fa);
	}
	cout<<ans;
	return 0;
}