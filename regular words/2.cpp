#include <cstdlib>
#include <cstdio>

void dfs(int x,int a,int b,int c)
{
	if(a+1<=n)
		dfs(x+1,a+1,b,c);
	if(b+1<=n && b+1<=a)
		dfs(x+1,a,b+1,c);w
	if(c+1<=n && c+1<=b)
		dfs(x+1,a,b,c+1);
}

int main()
{
	scanf("%d",&n);
	dfs(1,0,0,0);
	return 0;
}