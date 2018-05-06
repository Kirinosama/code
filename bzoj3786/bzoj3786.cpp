#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,fa[MAXN],in[MAXN],out[MAXN];
int a[MAXN],w[MAXN*2],ti;

struct edge{
    int x,y;
}E[MAXN];

int last[MAXN],ne[MAXN],edge_cnt;
int num,rt,ls[MAXN*2],rs[MAXN*2],val[MAXN*2],sum[MAXN*2],size[MAXN*2];
int f[MAXN*2];

void add_edge(int x,int y){
    E[++edge_cnt]=(edge){x,y};
    ne[edge_cnt]=last[x];
    last[x]=edge_cnt;
}

void dfs(int x){
    in[x]=++ti;w[ti]+=a[x];
    for(int i=last[x];i;i=ne[i])if(E[i].y!=fa[x])
        dfs(E[i].y);
    out[x]=ti;w[ti+1]-=a[x];
}

void maintain(int x){
    sum[x]=val[x]+sum[ls[x]]+sum[rs[x]];
    size[x]=size[ls[x]]+size[rs[x]]+1;
}

int build(int l,int r){
    int cur=++num;
    if(l!=r){
        int mid=(l+r)>>1;
        if(l<mid)ls[cur]=build(l,mid-1);
        if(r>mid)rs[cur]=build(mid+1,r);
        f[ls[cur]]=f[rs[cur]]=cur;
    }
    val[cur]=w[(l+r)>>1];
    maintain(cur);
    return cur;
}

int find(int x){
    int now=rt;
    while(now){
       int lcnt=size[ls[now]];
       if(x<=lcnt) now=ls[now];
       else if(x==lcnt+1) return now;
       else now=rs[now],x-=lcnt+1;
    }
    return now;
}

int wh(int x){
    return rs[f[x]]==x;
}

void rot(int x){
    int F=f[x],G=f[F];
    if(wh(x)){
        rs[F]=ls[x];f[rs[F]]=F;
        if(wh(F))rs[G]=x;
        else ls[G]=x;
        f[x]=G;ls[x]=F,f[F]=x;
    }else{
        ls[F]=rs[x];f[ls[F]]=F;
        if(wh(F)) rs[G]=x;
        else ls[G]=x;
        f[x]=G;rs[x]=F,f[F]=x;
    }
    if(F==rt) rt=x;
    maintain(F),maintain(x);
}

void splay(int x){
    for(;x!=rt;rot(x)){
        if(f[x]!=rt && f[f[x]]!=rt)
            rot(wh(x)==wh(f[x])?f[x]:x);
    }
}

void solve(){
    char opt[5];int x,y;
    scanf("%s",opt);
    if(opt[0]=='Q'){
        scanf("%d",&x);
        int p=find(in[x]+2),q=find(1);
        splay(p),splay(q);
        printf("%d\n",sum[ls[p]]);
    }else if(opt[0]=='F'){
        scanf("%d%d",&x,&y);
        int p=find(in[x]),q=find(out[x]+2);
        int u=find(in[y]),v=find(in[y]+3);
        splay(q);splay(p);
        int now=ls[q];ls[q]=0;
        maintain(q);maintain(p);
        splay(v);splay(u);
        ls[v]=now;maintain(v);maintain(u);
    }else{
        scanf("%d%d",&x,&y);
        int p=find(in[x]+1);splay(p);
        val[p]+=y,sum[p]+=y;
        p=find(out[x]+2);splay(p);
        val[p]-=y,sum[p]-=y;
    }
}

int main(){
    freopen("bzoj3786.in","r",stdin);
    cin>>n;
    for(int i=2;i<=n;i++){
        scanf("%d",&fa[i]);
        add_edge(fa[i],i);
    }
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    dfs(1);
    rt=build(0,ti+1);
    cin>>m;
    while(m--)
        solve();
    return 0;
}
