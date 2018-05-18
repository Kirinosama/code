#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int maxn=60;
struct stu
{
    int to,next;
}road[maxn*maxn]; int first[maxn],cnt;
int n,m,ans;
int sum[maxn],a[maxn],du[maxn],val[maxn],book[maxn];

void addedge(int x,int y)
{
    road[++cnt].to=y;
    road[cnt].next=first[x];
    first[x]=cnt;
}

void dfs(int x)
{
    if(x==n+1)
    {
        sum[0]=0;
        for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
        for(int i=1;i<=n;i++)
            for(int j=i;j<=n;j++){
                ans=max(ans,sum[j]-sum[i-1]);
			}
        return;
    }
    for(int now=1;now<=n;now++)
    {
        if(du[now]||book[now]) continue;
        book[now]=1;
        a[x]=val[now];
        for(int i=first[now];i;i=road[i].next)
        {
            int to=road[i].to;
            du[to]--;
        }
        dfs(x+1);
        book[now]=0;
        for(int i=first[now];i;i=road[i].next)
        {
            int to=road[i].to;
            du[to]++;
        }
    }
}

int main()
{
	freopen("san.in","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&val[i]);
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        addedge(x,y);du[y]++;
    }
    dfs(1);
    printf("%d",ans);
    return 0;
}
