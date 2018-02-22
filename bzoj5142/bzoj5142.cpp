#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

#define ll long long
#define N 100001
inline int read()
{
    char ch=getchar();
    int x=0;
    while ('0'>ch || ch>'9') ch=getchar();
    while ('0'<=ch && ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return x;
}
struct node
{
    int x,y,id;
}a[N];
bool cmp(node x,node y)
{
    return x.y<y.y;
}
ll m,s[N];
int f[N],n,flag[N];
inline int find(int x)
{
    if (f[x]==x) return x;
    f[x]=find(f[x]);
    return f[x];
}
inline void merge(int x,int y)
{
    x=find(x);y=find(y);
    s[x]+=s[y];
    f[y]=x;
}
int main()
{
    n=read();scanf("%lld",&m);
    for (int i=1;i<=n;++i) a[i]={read(),read()},a[i].id=f[i]=i,s[i]=a[i].x;
    sort(a+1,a+1+n,cmp);
    for (int i=1;i<=n;++i)
    {
        int id=a[i].id;
        flag[id]=1;
        if (flag[id-1]) merge(id,id-1);
        if (s[find(id)]>=m) {printf("%d\n",a[i].y);return 0;}
    }
}