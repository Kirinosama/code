#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define MAXN 1000007
struct Edge{ int to,next; }e[MAXN<<1];
struct Seg_Tree{ int l,r,lc,rc,sum,flag; }tre[MAXN<<2];
inline void read(int &x){
    x=0; int f=1; char c=getchar();
    while(c>'9'||c<'0'){ if(c=='-') f=-1; c=getchar(); }
    while(c>='0'&&c<='9'){ x=x*10+c-'0'; c=getchar(); } x*=f;
}
int head[MAXN],n,m,tot,visx,num,son[MAXN];
int dep[MAXN],top[MAXN],siz[MAXN],fa[MAXN],pos[MAXN],col[MAXN],sum[MAXN];

inline void Add_Edge(int u,int v){
    e[++tot].to=v,e[tot].next=head[u],head[u]=tot;
}

void DFS1(int u,int from,int deepth){
    siz[u]=1,fa[u]=from,dep[u]=deepth;
    for(int i=head[u];i;i=e[i].next){
        int v=e[i].to;
        if(v==from) continue;
        DFS1(v,u,deepth+1);
        siz[u]+=siz[v];
        if(!son[u]||siz[son[u]]<siz[v]) son[u]=v;
    }
}

void DFS2(int u,int Top){
    top[u]=Top,pos[u]= ++visx,sum[visx]=col[u];
    if(son[u]) DFS2(son[u],Top);
    for(int i=head[u];i;i=e[i].next){
        int v=e[i].to;
        if(v==fa[u]||v==son[u]) continue;
        DFS2(v,v);
    }
}

inline void UpDate(int u){
    tre[u].sum=tre[u<<1].sum+tre[u<<1|1].sum-(tre[u<<1].rc==tre[u<<1|1].lc);
    tre[u].lc=tre[u<<1].lc,tre[u].rc=tre[u<<1|1].rc;
}

inline void Push_Down(int u){
    if(tre[u].l==tre[u].r)  return ;
    tre[u<<1].sum=tre[u<<1|1].sum=1;
    tre[u<<1|1].lc=tre[u<<1|1].rc=tre[u<<1].lc=tre[u<<1].rc=tre[u].flag;
    tre[u<<1|1].flag=tre[u<<1].flag=tre[u].flag;
    tre[u].flag=0;
}

void Build(int u,int l,int r){
    tre[u].l=l,tre[u].r=r;
    if(l==r){
        tre[u].sum=1;
        tre[u].lc=tre[u].rc=sum[++num];
        return ;
    }
    int Mid=(l+r)>>1;
    Build(u<<1,l,Mid);
    Build(u<<1|1,Mid+1,r);
    UpDate(u);
}

int query(int u,int l,int r){
    if(tre[u].l==l&&tre[u].r==r) return tre[u].sum;
    int Mid=(tre[u].l+tre[u].r)>>1;
    if(tre[u].flag) Push_Down(u);
    UpDate(u);
    if(r<=Mid) return query(u<<1,l,r);
    else if(l>Mid) return query(u<<1|1,l,r);
    else{
        int lans=query(u<<1,l,Mid);
        int rans=query(u<<1|1,Mid+1,r);
        if(tre[u<<1].rc==tre[u<<1|1].lc) --lans;
        return lans+rans;
    }
}

int query_color(int u,int p){
    if(tre[u].l==tre[u].r&&tre[u].l==p) return tre[u].lc;
    if(tre[u].flag) Push_Down(u);
    UpDate(u);
    int Mid=(tre[u].l+tre[u].r)>>1;
    if(p<=Mid) return query_color(u<<1,p);
    else return query_color(u<<1|1,p);
}

int Ans_query(int u,int v){
    int ret=0;
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        ret+=query(1,pos[top[u]],pos[u]);
        if(query_color(1,pos[top[u]])==query_color(1,pos[fa[top[u]]])) --ret;
        u=fa[top[u]];
    }
    ret+=query(1,min(pos[u],pos[v]),max(pos[u],pos[v]));
    return ret;
}

void Modify(int u,int l,int r,int c){
    if(l==tre[u].l&&tre[u].r==r){
        tre[u].sum=1;
        tre[u].lc=tre[u].rc=tre[u].flag=c;
        return ;
    }
    if(tre[u].flag) Push_Down(u);
    int Mid=(tre[u].l+tre[u].r)>>1;
    if(r<=Mid) Modify(u<<1,l,r,c);
    else if(l>Mid) Modify(u<<1|1,l,r,c);
    else Modify(u<<1,l,Mid,c),Modify(u<<1|1,Mid+1,r,c);
    UpDate(u);
}

void Ans_Change(int u,int v,int c){
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        Modify(1,pos[top[u]],pos[u],c);
        u=fa[top[u]];
    }
    Modify(1,min(pos[u],pos[v]),max(pos[u],pos[v]),c);
}

int main(){
    //freopen("p2486.in","r",stdin);
    read(n),read(m);
    register int i; int u,v,w;
    for( i=1; i<=n; ++i) read(col[i]);
    for( i=1; i<n; ++i){
        read(u),read(v);
        Add_Edge(u,v),Add_Edge(v,u);
    }
    DFS1(1,0,1);
    DFS2(1,1);
    Build(1,1,n);
    char s[2];
    for(int i=1;i<=m;++i){
        scanf("%s",s);
        if(s[0]=='Q'){
            read(u),read(v);
            printf("%d\n",Ans_query(u,v));
        }
        else {
            read(u),read(v),read(w);
            Ans_Change(u,v,w);
        }
    }
    return 0;
}