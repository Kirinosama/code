#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010 
#define MAXM 200010
typedef long long ll;

struct edge{
    int x,y;
}E[MAXM];

int n,m,rt;
int last[MAXN],ne[MAXM],edge_cnt;
int size[MAXN],dep[MAXN],fa[MAXN],son[MAXN],top[MAXN];
int ti,ID[MAXN],nodecnt,dfn[MAXN],tail[MAXN];
ll a[MAXN],add[MAXN*4],sum[MAXN*4];
int ls[MAXN*4],rs[MAXN*4];

void add_edge(int x,int y){
    E[++edge_cnt]=(edge){x,y};
    ne[edge_cnt]=last[x];
    last[x]=edge_cnt;
}

void dfs1(int x,int f){
    size[x]=1;son[x]=0;
    dep[x]=dep[f]+1;fa[x]=f;
    for(int i=last[x];i;i=ne[i])if(E[i].y!=f){
        dfs1(E[i].y,x);size[x]+=size[E[i].y];
        if(size[E[i].y]>size[son[x]])son[x]=E[i].y;
    }
}

void dfs2(int x,int tp){
    dfn[x]=++ti;ID[ti]=x;top[x]=tp;
    if(son[x]) dfs2(son[x],tp);
    for(int i=last[x];i;i=ne[i])if(E[i].y!=fa[x] && E[i].y!=son[x])
        dfs2(E[i].y,E[i].y);
    tail[x]=ti;
}

void build(int &x,int l,int r){
    x=++nodecnt;
    if(l==r) sum[x]=a[ID[l]];
    else{
        int mid=(l+r)>>1;
        build(ls[x],l,mid);
        build(rs[x],mid+1,r);
        sum[x]=sum[ls[x]]+sum[rs[x]];
    }
}

void pushdown(int x,int l,int r){
    if(add[x]){
        int mid=(l+r)>>1;
        add[ls[x]]+=add[x];sum[ls[x]]+=(ll)(mid-l+1)*add[x];
        add[rs[x]]+=add[x];sum[rs[x]]+=(ll)(r-mid)*add[x];
        add[x]=0;
    }
}

void make(int x,int l,int r,int L,int R,ll k){
    if(l>R || r<L) return;
    if(l>=L && r<=r){
        add[x]+=k;sum[x]+=(r-l+1)*k;
    }else{
        int mid=(l+r)>>1;
        pushdown(x,l,r);
        make(ls[x],l,mid,L,R,k);
        make(rs[x],mid+1,r,L,R,k);
        sum[x]=sum[ls[x]]+sum[rs[x]];
    }
}

ll cal(int x,int l,int r,int L,int R){
    if(l>R || r<L) return 0;
    if(l>=L && r<=R) return sum[x];
    else{
        int mid=(l+r)>>1;
        pushdown(x,l,r);
        ll res=cal(ls[x],l,mid,L,R)+cal(rs[x],mid+1,r,L,R);
        sum[x]=sum[ls[x]]+sum[rs[x]];
        return res;
    }
}

void query(int x){
    ll res=0;
    while(top[x]!=1){
        res+=cal(rt,1,n,dfn[top[x]],dfn[x]);
        x=fa[top[x]];
    }
    res+=cal(rt,1,n,1,dfn[x]);
    cout<<res<<endl;
}

void solve(){
    int opt,x;ll y;
    scanf("%d%d",&opt,&x);
    switch(opt){
        case 1:scanf("%lld",&y),make(rt,1,n,dfn[x],dfn[x],y);break;
        case 2:scanf("%lld",&y);make(rt,1,n,dfn[x],tail[x],y);break;
        case 3:query(x);
    }
}

int main(){
    freopen("bzoj4034.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(int i=1;i<n;i++){
        int x,y;scanf("%d%d",&x,&y);
        add_edge(x,y);add_edge(y,x);
    }
    dfs1(1,1);
    dfs2(1,1);
    build(rt,1,n);
    while(m--)
        solve();
    return 0;
}
