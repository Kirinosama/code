#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 100500
#define inf 99999999
using namespace std;
int delta=0,n,minn,tree[maxn][3],w[maxn],fath[maxn],size[maxn],value[maxn];
int x,ans=0,tot=0,re,root=0;
char type[5];
void pushup(int now)
{
    int ls=tree[now][1],rs=tree[now][2];
    size[now]=size[ls]+size[rs]+w[now];
}
int insert(int x,int now,int father)
{
    int regis;
    int ls=tree[now][1],rs=tree[now][2];
    if (now==0)
    {
        now=++tot;
        fath[now]=father;
        size[now]=1;w[now]=1;
        if (x<value[father]) tree[father][1]=now;
        else tree[father][2]=now;
        value[now]=x;
        return now;    
    }
    if (x<value[now]) regis=insert(x,ls,now);
    else if (x>value[now]) regis=insert(x,rs,now);
    else {size[now]++;w[now]++;regis=now;}
    pushup(now);
    return regis;
}
void rotate(int x,int &k)
{
    int y=fath[x],z=fath[y],l,r;
    if (tree[y][1]==x) l=1;else l=2;
    r=3-l;
    if (y==k) k=x;
    else
    {
        if (tree[z][1]==y) tree[z][1]=x;
        else tree[z][2]=x;
    }
    fath[x]=z;fath[y]=x;fath[tree[x][r]]=y;
    tree[y][l]=tree[x][r];tree[x][r]=y;
    pushup(y);pushup(x);
}
void splay(int x,int &k)
{
    while (x!=k)
    {
        int y=fath[x],z=fath[y];
        if (y!=k)
        {
            if ((tree[y][1]==x)^(tree[z][1]==y)) rotate(x,k);
            else rotate(y,k);
        }
        rotate(x,k);
    }
}
void pre(int x,int now)
{
    if (now==0) return;
    int ls=tree[now][1],rs=tree[now][2];
    if (value[now]<x)
    {
        re=now;
        pre(x,rs);
    }
    else pre(x,ls);
}
int ra(int x,int now)
{
    if (now==0) return 0;
    int ls=tree[now][1],rs=tree[now][2];
    if (x<=size[rs]) return ra(x,rs);
    else if (x>size[rs]+w[now]) return ra(x-size[rs]-w[now],ls);
    else return value[now];
}
void work1()
{
    int regis;
    scanf("%d",&x);
    if ((tot==0) || (root==0)) {tot++;root=tot;value[root]=x-delta;size[root]=1;w[root]=1;}
    else if (x>=minn) {regis=insert(x-delta,root,root);splay(regis,root);}
}
void work2()
{
    scanf("%d",&x);
    delta=delta+x; 
}
void work3()
{
    scanf("%d",&x);
    delta=delta-x;
    pre(minn-delta,root);
    if (re!=0)
    { 
        splay(re,root);
        ans=ans+size[tree[root][1]]+w[root];
        root=tree[root][2];
    }
    re=0;
}
void work4()
{
    int regis;
    scanf("%d",&x);
    regis=ra(x,root);
    if (regis==0) printf("-1\n");
    else printf("%d\n",regis+delta);
}
int main()
{
    scanf("%d%d",&n,&minn);
    for (int i=1;i<=n;i++)
    {
        scanf("%s",type);
        if (type[0]=='I') work1();
        else if (type[0]=='A') work2();
        else if (type[0]=='S') work3();
        else work4();
    }
    printf("%d\n",ans);
    return 0;
}