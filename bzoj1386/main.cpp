#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 10010
int n,t,a[MAXN];

int gcd(int x,int y)
{
	if(x>y) swap(x,y);
	if(!x) return y;
	else return gcd(y%x,x); 
}

void solve()
{
	int cnt=0,x;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		if(i!=2) scanf("%d",&a[++cnt]);
		else scanf("%d",&x);
	}
	for(int i=1;i<=cnt && x>1;i++)
		x/=gcd(x,a[i]);
	if(x==1) printf("YES\n");
	else printf("NO\n");
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&t);
	while(t--) solve();
	return 0;
}