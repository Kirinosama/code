#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN=100010;

int n,m,root,MOD,edge_cnt,cnt;
int son[MAXN],top[MAXN],id[MAXN],w[MAXN];
int fa[MAXN],last[MAXN],ne[MAXN*2],tail[MAXN];
int dep[MAXN],size[MAXN],val[MAXN],pre_val[MAXN];

struct edge
{
    int u,v;
}E[MAXN*2];

struct node
{
    int l,r;
    int sum,lazy;
    node *ls;
    node *rs;
    void maintain()
    {
        sum=((long long)ls->sum+rs->sum)%MOD;
    }
    void pushdown()
    {
        sum=(sum+(long long)(r-l+1)*lazy)%MOD;
        if(ls) ls->lazy=((long long)ls->lazy+lazy)%MOD;
        if(rs) rs->lazy=((long long)rs->lazy+lazy)%MOD;
        lazy=0;
    }
};

node * Root;

void insert_edge(int x,int y)
{
    E[++edge_cnt].u=x;
    E[edge_cnt].v=y;
    ne[edge_cnt]=last[x];
    last[x]=edge_cnt;
}

void add_edge()
{
    int x,y;
    scanf("%d %d",&x,&y);
    insert_edge(x,y);
    insert_edge(y,x);
}

void dfs1(int x,int f)
{
    int to;
    fa[x]=f;
    son[x]=0;
    size[x]=1;
    for(int i=last[x];i;i=ne[i])
    {
        to=E[i].v;
        if(to==f)continue;
        dep[to]=dep[x]+1;
        dfs1(to,x);
        size[x]+=size[to];
        if(size[to]>size[son[x]])
            son[x]=to;
    }
}

void dfs2(int x,int tp)
{
    int to;
    top[x]=tp;
    id[x]=++cnt;
    if(son[x])
        dfs2(son[x],tp);
    for(int i=last[x];i;i=ne[i])
    {
        to=E[i].v;
        if(to==son[x] || to==fa[x])
            continue;
        dfs2(to,to);
    }
    tail[x]=cnt;
}

void build(node *&p,int l,int r)
{
    if(!p)
    {
        p=new node;
        p->l=l;p->r=r;
        p->ls=p->rs=NULL;
        p->sum=0;
        p->lazy=0;
    }

    if(l==r)
        p->sum=val[l];

    if(l!=r)
    {
        int mid=(l+r)/2;
        build(p->ls,l,mid);
        build(p->rs,mid+1,r);
        p->maintain();
    }
}

void add(node *&p,int l,int r,int k)
{
    if(p->l>r || p->r<l)	return;
    if(p->l>=l && p->r<=r)	
    {
        p->lazy+=k;
        return;
    }
    if(p->l!=p->r)
    {
        p->sum=(p->sum+((long long)(min(p->r,r)-max(p->l,l)+1)*k)%MOD)%MOD;
        add(p->ls,l,r,k);
        add(p->rs,l,r,k);
    }
}

int query(node *p,int l,int r)
{
    if(p->l>r || p->r<l)
        return 0;
    if(p->lazy)p->pushdown();
    if(p->l>=l && p->r<=r)
        return p->sum;
    else if(p->l!=p->r)
        return ((long long)query(p->ls,l,r)+query(p->rs,l,r))%MOD;
    return 0;
}

int query1(int x,int y)
{
    int res=0;
    while(top[x]!=top[y])
    {
        if(dep[top[x]]>dep[top[y]])
        {
            res=(res+query(Root,id[top[x]],id[x]))%MOD;
            x=top[x];
            x=fa[x];
        }
        else
        {
            res=(res+query(Root,id[top[y]],id[y]))%MOD;
            y=top[y];
            y=fa[y];
        }
    }
    if(id[x]>id[y]) swap(x,y);
    res=(res+query(Root,id[x],id[y]))%MOD;
    return res;
}

void premake()
{
    dep[root]=0;
    dfs1(root,0);
    dfs2(root,root);	
    for(int i=1;i<=n;i++)
        val[id[i]]=w[i];
    build(Root,1,n);
}

void make(int x,int y,int z)
{
    while(top[x]!=top[y])
    {
        if(dep[top[x]]>dep[top[y]])
        {
            add(Root,id[top[x]],id[x],z);
            x=top[x];
            x=fa[x];
        }
        else
        {
            add(Root,id[top[y]],id[y],z);
            y=top[y];
            y=fa[y];
        }
    }
    if(id[x]>id[y]) swap(x,y);
    add(Root,id[x],id[y],z);
}

void solve()
{
    int k,x,y,z;
    scanf("%d %d",&k,&x);
    if(k==1)
    {
        scanf("%d %d",&y,&z);
        make(x,y,z);
    }
    if(k==2)
    {
        scanf("%d",&y);
        printf("%d\n",query1(x,y));
    }
    if(k==3)
    {
        scanf("%d",&z);
        add(Root,id[x],tail[x],z);
    }
    if(k==4)
    {
        printf("%d\n",query(Root,id[x],tail[x]));
    }
}

int main()
{
//	freopen("input","r",stdin);
    scanf("%d %d %d %d",&n,&m,&root,&MOD);
    for(int i=1;i<=n;i++)
        scanf("%d",&w[i]);
    for(int i=1;i<=n-1;i++)
        add_edge();
    premake();
    while(m--)
        solve();
    return 0;
}