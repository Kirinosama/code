#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
#define N 1000005

typedef long long ll;

int n;
ll sum,ave,ans,a[N];

ll Abs(ll x)
{
	return (x>0)?x:-x;
}

int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;++i) scanf("%d",&a[i]),sum+=a[i];
    ave=sum/n;
    for (int i=1;i<=n;++i) a[i]=a[i-1]+a[i]-ave;
    sort(a+1,a+n+1);
    for (int i=1;i<=n;++i) ans+=Abs(a[i]-a[(n>>1)+1]);
    printf("%lld\n",ans);
}