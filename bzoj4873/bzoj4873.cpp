#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=100010,s=100005,t=100006,oo=0x3f3f3f3f;
int fir[maxn],ne[maxn],to[maxn],w[maxn],que[maxn],dep[maxn],cur[maxn],
idr[110][110],ida[1010],idp[110],a[110],d[110][110],
n,m,tot,num;
void add(int u,int v,int x)
{
    num++;
    ne[num<<1]=fir[u];
    fir[u]=num<<1;
    to[num<<1]=v;
    w[num<<1]=x;
    ne[num<<1|1]=fir[v];
    fir[v]=num<<1|1;
    to[num<<1|1]=u;
    w[num<<1|1]=0;
}
int bfs()
{
    int hd=1,tl=1,u,v;
    for (int i=1;i<=tot;i++) dep[i]=0;
    dep[t]=0;
    dep[que[1]=s]=1;
    while (hd<=tl)
    {
        u=que[hd++];
        cur[u]=fir[u];
        for (int i=fir[u];i;i=ne[i])
            if (w[i]&&!dep[v=to[i]])
            {
                que[++tl]=v;
                dep[v]=dep[u]+1;
            }
    }
    return dep[t];
}
int dfs(int u,int lim)
{
    if (u==t) return lim;
    int ret=0,x,v;
    for (int &i=cur[u];i;i=ne[i])
        if (w[i]&&dep[v=to[i]]==dep[u]+1)
        {
            x=dfs(v,min(lim-ret,w[i]));
            ret+=x;
            w[i]-=x;
            w[i^1]+=x;
        }
    return ret;
}
int main()
{
    int ans=0;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) idp[i]=++tot;
    for (int i=1;i<=n;i++)
        for (int j=i;j<=n;j++)
            idr[i][j]=++tot;
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        if (!ida[a[i]]) ida[a[i]]=++tot;
    }
    for (int i=1;i<=n;i++)
        for (int j=i;j<=n;j++)
        {
            scanf("%d",&d[i][j]);
            if (d[i][j]>=0)
            {
                ans+=d[i][j];
                add(s,idr[i][j],d[i][j]);
            }
            else add(idr[i][j],t,-d[i][j]);
            if (i==j) add(idr[i][j],idp[i],oo);
            else
            {
                add(idr[i][j],idr[i+1][j],oo);
                add(idr[i][j],idr[i][j-1],oo);
            }
        }
    for (int i=1;i<=n;i++)
    {
        add(idp[i],t,a[i]);
        if (m) add(idp[i],ida[a[i]],oo);
    }
    if (m) for (int i=0;i<=1000;i++)
        if (ida[i]) add(ida[i],t,i*i);
    while (bfs()) ans-=dfs(s,oo);
    printf("%d\n",ans);
}