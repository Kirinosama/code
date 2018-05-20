#include<bits/stdc++.h>
using namespace std;
int N,a[33],s;
bool f=0;
const int INF(0x7f7f7f7f);
void dfs(int i)
{
	if(f) return;
	if(i>N)
	{
		int cnt=0;
		for(int i=1;i<=N;i++)
			for(int j=i+1;j<=N;j++)
				for(int k=i;k<=j;k++)
					if(a[k]!=a[i])
					{
						++cnt;
						break;
					}
		if(cnt==s) f=1;
		return;
	}
	a[i]=0;
	dfs(i+1);
	if(f) return;
	a[i]=1;
	dfs(i+1);
	if(f) return;
}
int main()
{
	int T;
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&s);
		for(N=1;N*(N-1)<s*2;++N);
		f=0,dfs(1);
		for(int i=1;i<=N;i++)
			putchar(a[i]^'0');
		puts("");
	}
	return 0;
}
