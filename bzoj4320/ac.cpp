#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define maxn 400500
#define inf 1000000007
using namespace std;
int n,x;char s[5];
int mn[maxn],father[maxn],a[maxn],tot=0,mx[maxn];
struct query
{
    int type,x,ans;
    query (int type,int x,int ans):type(type),x(x),ans(ans) {}
    query () {}
}q[maxn];
int getfather(int x)
{
    if (x!=father[x]) father[x]=getfather(father[x]);
    return father[x];
}
void unionn(int x,int y)
{
    if (y>300000) return;
    int f1=getfather(x),f2=getfather(y);
    if (f1!=f2) father[f1]=f2;
}
int main()
{
    freopen("bzoj4320.in","r",stdin);
    scanf("%d",&n);
    int top=(int)sqrt(300000)+1;
    for (int i=1;i<=top;i++) mn[i]=inf;
    for (int i=1;i<=n;i++)
    {
        mx[i]=mx[i-1];
        scanf("%s",s);scanf("%d",&x);
        if (s[0]=='A') q[i]=query(1,x,0);
        else q[i]=query(2,x,0);
        if (s[0]=='A')
        {
            for (int j=1;j<=top;j++)
                mn[j]=min(mn[j],x%j);
            a[++tot]=x;mx[i]=max(mx[i],x);
        }
        else if (x<=top) q[i]=query(2,x,mn[x]);
    }
    sort(a+1,a+tot+1);for (int i=1;i<=300000;i++) father[i]=i;
    int p=1;
    for (int i=1;i<=300000;i++)
    {
        if (a[p]<i) p++;
        father[i]=a[p];
    }
    for (int i=n;i>=1;i--)
    {
        if (q[i].type==1) unionn(q[i].x,q[i].x+1);
        else if (q[i].x>top)
        {
            int ret=inf,kr=q[i].x;
            for (int j=q[i].x;j<=mx[i];j+=q[i].x)
            {
                int f=getfather(j);
                ret=min(ret,f%q[i].x);
            }
            ret=min(ret,getfather(1)%q[i].x);
            q[i]=query(2,kr,ret);
        }
    }
    for (int i=1;i<=n;i++)
        if (q[i].type==2) printf("%d\n",q[i].ans);
    return 0;
}
