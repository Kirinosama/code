#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
#define N 1000005
#define inf 2000000000

int n,root,cmpd,x,y,Max,Min,ans;
struct data{int l,r,d[2],mx[2],mn[2];}tr[N];

void update(int x)
{
    int l=tr[x].l,r=tr[x].r;
    if (l)
    {
        tr[x].mx[0]=max(tr[x].mx[0],tr[l].mx[0]);
        tr[x].mn[0]=min(tr[x].mn[0],tr[l].mn[0]);
        tr[x].mx[1]=max(tr[x].mx[1],tr[l].mx[1]);
        tr[x].mn[1]=min(tr[x].mn[1],tr[l].mn[1]);
    }
    if (r)
    {
        tr[x].mx[0]=max(tr[x].mx[0],tr[r].mx[0]);
        tr[x].mn[0]=min(tr[x].mn[0],tr[r].mn[0]);
        tr[x].mx[1]=max(tr[x].mx[1],tr[r].mx[1]);
        tr[x].mn[1]=min(tr[x].mn[1],tr[r].mn[1]);
    }
}
int cmp(data a,data b)
{
    return a.d[cmpd]<b.d[cmpd]||a.d[cmpd]==b.d[cmpd]&&a.d[cmpd^1]<b.d[cmpd^1];
}
int build(int l,int r,int d)
{
    int mid=(l+r)>>1;
    cmpd=d;
    nth_element(tr+l,tr+mid,tr+r+1,cmp);
    tr[mid].mx[0]=tr[mid].mn[0]=tr[mid].d[0];
    tr[mid].mx[1]=tr[mid].mn[1]=tr[mid].d[1];
    if (l<mid) tr[mid].l=build(l,mid-1,d^1);
    if (r>mid) tr[mid].r=build(mid+1,r,d^1);
    update(mid);
    return mid;
}
int disMin(int now,int x,int y)
{
    int dis=0;
    if (x>tr[now].mx[0]) dis+=x-tr[now].mx[0];
    if (x<tr[now].mn[0]) dis+=tr[now].mn[0]-x;
    if (y>tr[now].mx[1]) dis+=y-tr[now].mx[1];
    if (y<tr[now].mn[1]) dis+=tr[now].mn[1]-y;
    return dis;
}
void queryMin(int now)
{
    int dl,dr;
    int d0=abs(tr[now].d[0]-x)+abs(tr[now].d[1]-y);
    if (d0) Min=min(Min,d0);
    if (tr[now].l) dl=disMin(tr[now].l,x,y);
    else dl=inf;
    if (tr[now].r) dr=disMin(tr[now].r,x,y);
    else dr=inf;
    if (dl<dr)
    {
        if (dl<Min) queryMin(tr[now].l);
        if (dr<Min) queryMin(tr[now].r);
    }
    else
    {
        if (dr<Min) queryMin(tr[now].r);
        if (dl<Min) queryMin(tr[now].l);
    }
}
int disMax(int now,int x,int y)
{
    int dis=0;
    dis+=max(abs(tr[now].mx[0]-x),abs(tr[now].mn[0]-x));
    dis+=max(abs(tr[now].mx[1]-y),abs(tr[now].mn[1]-y));
    return dis;
}
void queryMax(int now)
{
    int dl,dr;
    int d0=abs(tr[now].d[0]-x)+abs(tr[now].d[1]-y);
    Max=max(Max,d0);
    if (tr[now].l) dl=disMax(tr[now].l,x,y);
    else dl=0;
    if (tr[now].r) dr=disMax(tr[now].r,x,y);
    else dr=0;
    if (dl>dr)
    {
        if (dl>Max) queryMax(tr[now].l);
        if (dr>Max) queryMax(tr[now].r);
    }
    else
    {
        if (dr>Max) queryMax(tr[now].r);
        if (dl>Max) queryMax(tr[now].l);
    }
}
int main()
{
    freopen("bzoj1941.in","r",stdin);
    freopen("out2","w",stdout);
    scanf("%d",&n);
    for (int i=1;i<=n;++i) scanf("%d%d",&tr[i].d[0],&tr[i].d[1]);
    root=build(1,n,0);
    ans=inf;
    for (int i=1;i<=n;++i)
    {
        x=tr[i].d[0];y=tr[i].d[1];
        Min=inf;Max=0;
        queryMin(root);
        queryMax(root);
        ans=min(ans,Max-Min);
    }
    printf("%d",ans);
}