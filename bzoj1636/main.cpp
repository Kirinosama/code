#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;

int n,tot;
ll ans;
struct data{int t,d;}a[100001];
inline bool cmp(data a,data b){return a.t*b.d<a.d*b.t;}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&a[i].t,&a[i].d);
        tot+=a[i].d;
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++)
    {
        tot-=a[i].d;
        ans+=2*a[i].t*tot;
    }
    printf("%lld",ans);
    return 0;
}