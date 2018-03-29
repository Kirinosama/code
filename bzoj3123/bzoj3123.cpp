#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

#define ls p->ch[0]
#define rs p->ch[1]
#define SIZE(x) (x?x->cnt:0)
#define MAXN 200010
#define MAXM 1000010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

map <int,int> mp1,mp2;
int n,m,T,val[MAXN],sor[MAXN];
int fa[MAXN],size[MAXN];
int last[MAXN],ne[MAXM],edge_cnt;
int cnt,anc[MAXN][25],dep[MAXN];
int lastans;

struct edge{
    int x,y;
}E[MAXM];

struct node{
    node* ch[2];
    int cnt;
    node(){ch[0]=ch[1]=NULL;cnt=0;}
}*root[MAXN];

void add_edge(int x,int y){
    E[++edge_cnt]=(edge){x,y};
    ne[edge_cnt]=last[x];
    last[x]=edge_cnt;
}

void discrete(){
    for(int i=1;i<=n;i++)sor[i]=i;
    sort(sor+1,sor+n+1);
    for(int i=1;i<=n;i++)if(sor[i]!=sor[i+1]){
        mp1[sor[i]]=++cnt;
        mp2[cnt]=sor[i];
    }
    for(int i=1;i<=n;i++)val[i]=mp1[val[i]];
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void merge(int x,int y){
    int fx=find(x),fy=find(y);
    if(fx!=fy) size[fy]+=size[fx],fa[fx]=fy;
}

void build(node *&p,int l,int r,int pos){
    p=new node;p->cnt=1;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(pos<=mid)build(ls,l,mid,pos);
    else build(rs,mid+1,r,pos);
}

void make(node *&p,node *q,int l,int r,int pos){
    if(!p) p=new node;
    p->cnt=q?q->cnt+1:1;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(pos<=mid) make(ls,q?q->ch[0]:NULL,l,mid,pos);
    else make(rs,q?q->ch[1]:NULL,mid+1,r,pos);
    p->ch[pos<=mid]=q?q->ch[pos<=mid]:NULL;
}

void dfs(int x,int f){
    if(root[x] && x==f) return;
    anc[x][0]=f;dep[x]=dep[f]+1;
    if(!root[x] && f==x) build(root[x],1,cnt,val[x]);
    if(!root[x] && f!=x) make(root[x],root[f],1,cnt,val[x]);
    for(int i=1;i<=20;i++)anc[x][i]=anc[anc[x][i-1]][i-1];
    for(int i=last[x];i;i=ne[i])if(E[i].y!=f)
        dfs(E[i].y,x);
}

int getlca(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=20;i>=0;i--)if(dep[x]-(1<<i)>=dep[y])
        x=anc[x][i];
    if(x==y) return x;
    for(int i=20;i>=0;i--)if(anc[x][i]!=anc[y][i])
        x=anc[x][i],y=anc[y][i];
    return anc[x][0];
}

int query(node **v,int l,int r,int k){
    if(l==r) return l;
    int mid=(l+r)>>1,lcnt=0;
    for(int i=0;i<=1;i++)lcnt+=v[i]?SIZE(v[i]->ch[0]):0;
    for(int i=2;i<=3;i++)lcnt-=v[i]?SIZE(v[i]->ch[0]):0;
    if(k<=lcnt){
        for(int i=0;i<4;i++)if(v[i])
            v[i]=v[i]->ch[0];
        return query(v,l,mid,k);
    }else{
        for(int i=0;i<4;i++)if(v[i])
            v[i]=v[i]->ch[1];
        return query(v,mid+1,r,k-lcnt);
    }
}

void dfs1(int x,int f){
    dep[x]=dep[f]+1;anc[x][0]=f;
    for(int i=1;i<=20;i++)anc[x][i]=anc[anc[x][i-1]][i-1];
    make(root[x],root[f],1,cnt,val[x]);
    for(int i=last[x];i;i=ne[i])if(E[i].y!=f)
        dfs1(E[i].y,x);
}

void solve(){
    char opt;node *v[4];int x,y,z;
    scanf("%c %d %d",&opt,&x,&y);
    if(opt=='Q'){
        scanf("%d\n",&z);
        x^=lastans,y^=lastans,z^=lastans;
        v[0]=root[x],v[1]=root[y];
        int lca=getlca(x,y);
        v[2]=root[lca],v[3]=anc[lca][0]==lca?NULL:root[anc[lca][0]];
        lastans=mp2[query(v,1,cnt,z)];
        printf("%d\n",lastans);
    }else{
        scanf("\n");
        x^=lastans,y^=lastans;
        int fx=find(x),fy=find(y);
        if(size[fx]>size[fy])swap(x,y);
        dfs1(x,y);add_edge(x,y);add_edge(y,x);
        size[fy]+=size[fx];fa[fx]=fy;
    }
}

int main(){
    freopen("bzoj3123.in","r",stdin);
    scanf("%d",&T);scanf("%d%d%d",&n,&m,&T);
    for(int i=1;i<=n;i++){
        size[i]=1,fa[i]=i;
        scanf("%d",&val[i]);
    }
    discrete();
    for(int i=1;i<=m;i++){
        int x,y;scanf("%d%d",&x,&y);
        add_edge(x,y);add_edge(y,x);
        merge(x,y);
    }
    for(int i=1;i<=n;i++)dfs(i,i);
    scanf("\n");
    while(T--)solve();
    return 0;
}
