#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 50010

int n,m,a[MAXN],b[MAXN],sqr;
int dfn[MAXN],anc[MAXN][25],dep[MAXN],ti;
int querycnt,changecnt;
int last[MAXN],ne[MAXN*2],edge_cnt;
int size[MAXN],sizecnt[MAXN],tot[MAXN];
int lastnum,col[MAXN],st[MAXN],ed[MAXN],ans[MAXN];

struct edge{
    int x,y;
}E[MAXN*2];

struct task{
    int num,x,y,ID;
}query[MAXN],change[MAXN];

void add_edge(int x,int y){
    E[++edge_cnt]=(edge){x,y};
    ne[edge_cnt]=last[x];
    last[x]=edge_cnt;
}

bool cmp(const task &a,const task &b){
    if(dfn[a.x]/sqr==dfn[b.x]/sqr) return dfn[a.y]<dfn[b.y];
    else return dfn[a.x]/sqr<dfn[b.x]/sqr;
}

void dfs(int x,int f){
    anc[x][0]=f;dep[x]=dep[f]+1;dfn[x]=++ti;
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

void update(int x,int k){
    if(x>n) return;
    size[x]+=k;
    if(!size[x] && k==-1) sizecnt[x/sqr]--;
    if(size[x]==1 && k==1) sizecnt[x/sqr]++;
}

void rev(int x){
    if(col[x]) col[x]=0,update(a[x],-1);
    else col[x]=1,update(a[x],1);
}

void make(int x,int y){
    if(x<y){
        for(int i=x+1;i<=y;i++)if(col[change[i].num])
            update(change[i].x,-1),update(change[i].y,1);
    }else{
        for(int i=x;i>y;i--)if(col[change[i].num])
            update(change[i].y,-1),update(change[i].x,1);
    }
}

int getans(){
    for(int i=0;i<=n/sqr;i++)if(sizecnt[i]!=tot[i]){
        for(int j=st[i];j<=ed[i];j++)if(!size[j])
            return j;
    }
}

int main(){
    freopen("bzoj4129.in","r",stdin);
    cin>>n>>m;sqr=(int)sqrt(n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]),b[i]=a[i];
    for(int i=1;i<n;i++){
        int x,y;scanf("%d%d",&x,&y);
        add_edge(x,y);add_edge(y,x);
    }
    for(int i=1;i<=m;i++){
        int opt,x,y;
        scanf("%d%d%d",&opt,&x,&y);
        if(opt==0) change[++changecnt]=(task){x,b[x],y},b[x]=y;
        else query[++querycnt]=(task){changecnt,x,y,querycnt};
    }
    dfs(1,1);
    memset(st,-1,sizeof(st));
    for(int i=0;i<=n;i++){
        tot[i/sqr]++;
        ed[i/sqr]=i;
        if(st[i/sqr]==-1) st[i/sqr]=i;
    }
    sort(query+1,query+1+querycnt,cmp);
    int l=1,r=1;rev(1);
    for(int i=1;i<=querycnt;i++){
        make(lastnum,query[i].num);
        int x=query[i].x,y=query[i].y;
        int lca1=getlca(l,x),lca2=getlca(r,y);
        for(int j=l;j!=lca1;j=anc[j][0]) rev(j);
        for(int j=x;j!=lca1;j=anc[j][0]) rev(j);
        for(int j=r;j!=lca2;j=anc[j][0]) rev(j);
        for(int j=y;j!=lca2;j=anc[j][0]) rev(j);
        rev(getlca(l,r));rev(getlca(x,y));
        ans[query[i].ID]=getans();
        lastnum=query[i].num;l=x,r=y;
    }
    for(int i=1;i<=querycnt;i++)printf("%d\n",ans[i]);
    return 0;
}
