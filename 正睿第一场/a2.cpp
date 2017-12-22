#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 1010

int n;
double s[MAXN],ans;

void solve(int mask)
{
	int cnt=0;
	double sum1=0;
	double sum2=0;
	for(int i=1;i<=2*n;i++)
	{
		int ch=mask&1;
		mask>>=1;
		if(ch==1) cnt++;
		if(ch==1 && i<=n) sum1+=s[i];
		if(ch==1 && i>n) sum2+=s[i];
	}
	ans=max(ans,min(sum1,sum2)-cnt);
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=2*n;i++) scanf("%lf",&s[i]);
	for(int i=0;i<(1<<(2*n));i++)
		solve(i);
	printf("%.4f",ans);
	return 0;
}
