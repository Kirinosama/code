#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <vector>
#include <queue>
#include <map>
#include <set>
#ifdef WIN32   
#define OT "%I64d"
#else
#define OT "%lld"
#endif
using namespace std;
typedef long long LL;
const int MAXN = 100011;
int n,m,ecnt,ans;
int first[MAXN],next[MAXN*2],to[MAXN*2],val[MAXN];
int top[MAXN],size[MAXN],deep[MAXN],son[MAXN],id[MAXN],pre[MAXN],father[MAXN];
char ch[12];
int ql,qr;

struct node{
    int l,r,lazy;
    int lc,rc;//左右端点的颜色
    int sum;
}a[MAXN*4];

inline int getint()
{
       int w=0,q=0;
       char c=getchar();
       while((c<'0' || c>'9') && c!='-') c=getchar();
       if (c=='-')  q=1, c=getchar();
       while (c>='0' && c<='9') w=w*10+c-'0', c=getchar();
       return q ? -w : w;
}

inline void dfs1(int x,int fa){
    size[x]=1;
    for(int i=first[x];i;i=next[i]) {
    int v=to[i];
    if(v==fa)continue;
    deep[v]=deep[x]+1; father[v]=x;
    dfs1(v,x);
    size[x]+=size[v];if(size[v]>size[son[x]]) son[x]=v;
    }
}

inline void dfs2(int x,int fa){
    id[x]=++ecnt;pre[ecnt]=x;
    if(son[x]) top[son[x]]=top[x],dfs2(son[x],x);
    for(int i=first[x];i;i=next[i]) {
    int v=to[i];
    if(v==fa || v==son[x]) continue;
    top[v]=v; dfs2(v,x);
    }
}

inline void build(int root,int l,int r){
    a[root].l=l; a[root].r=r; a[root].lazy=-1;
    if(l==r) {  a[root].sum=1; a[root].lc=a[root].rc=val[pre[l]]; return ; }
    int mid=(l+r)/2; int lc=root*2,rc=lc+1;
    build(lc,l,mid); build(rc,mid+1,r);
    a[root].sum=a[lc].sum+a[rc].sum; a[root].lc=a[lc].lc; a[root].rc=a[rc].rc;
    if(!(a[lc].rc^a[rc].lc)) a[root].sum--;
} 

inline int lca(int x,int y){
    int f1=top[x],f2=top[y];
    while(f1!=f2) {
    if(deep[f1]<deep[f2]) swap(f1,f2),swap(x,y);
    x=father[f1]; f1=top[x];
    }
    if(deep[x]<deep[y]) swap(x,y);
    return y;
}

inline void pushdown(int root){
    int lin=a[root].lazy; a[root].lazy=-1;
    if(lin==-1 || a[root].l==a[root].r) return ;
    int lc=root*2,rc=lc+1;
    a[lc].lazy=a[rc].lazy=lin;
    a[root].lc=a[root].rc=a[lc].lc=a[lc].rc=a[rc].lc=a[rc].rc=lin;
    a[root].sum=a[lc].sum=a[rc].sum=1;
}

inline void update(int root){
    int lc=root*2,rc=lc+1;
    a[root].sum=a[lc].sum+a[rc].sum;   
    if(!(a[lc].rc^a[rc].lc)) a[root].sum--;
    a[root].lc=a[lc].lc; a[root].rc=a[rc].rc;
}

inline void query(int root,int l,int r){
    if(ql>qr) return ;
    pushdown(root);
    if(ql<=l && r<=qr) {
    ans+=a[root].sum;
    return ;
    }
    int mid=(l+r)/2; int lc=root*2,rc=lc+1;
    if(qr<=mid) query(lc,l,mid); 
    else if(ql>mid) query(rc,mid+1,r); 
    else{
    query(lc,l,mid); query(rc,mid+1,r);
    if(a[lc].rc==a[rc].lc) ans--;
    }
}

inline void change(int root,int l,int r,int z){
    if(ql>qr) return ;
    pushdown(root);
    if(ql<=l && r<=qr) {
    a[root].lazy=z; a[root].lc=a[root].rc=a[root].lazy; a[root].sum=1; return ;
    }
    int mid=(l+r)/2; int lc=root*2,rc=lc+1;
    if(ql<=mid) change(lc,l,mid,z); if(qr>mid) change(rc,mid+1,r,z);
    update(root);
}

inline int getcol(int root,int x){
    pushdown(root);
    if(a[root].l==a[root].r) return a[root].lc;
    int mid=(a[root].l+a[root].r)/2; int lc=root*2,rc=lc+1;
    if(x<=mid) return getcol(lc,x); else return getcol(rc,x);
}

inline void ask_change(int x,int f,int z){
    while(top[x]!=top[f]) {
    ql=id[top[x]]; qr=id[x];
    change(1,1,n,z);
    x=father[top[x]];
    }
    ql=id[f],qr=id[x],change(1,1,n,z);
}

inline void ask_sum(int x,int f){
    while(top[x]!=top[f]) {
    ql=id[top[x]]; qr=id[x];
    query(1,1,n);
    if(getcol(1,id[top[x]])==getcol(1,id[father[top[x]]])) ans--;
    x=father[top[x]];
    }
    ql=id[f],qr=id[x],query(1,1,n);
}

inline void work(){
    n=getint(); m=getint();
    for(int i=1;i<=n;i++) val[i]=getint();
    int x,y;
    for(int i=1;i<n;i++) {
    x=getint(); y=getint();
    next[++ecnt]=first[x]; first[x]=ecnt; to[ecnt]=y;
    next[++ecnt]=first[y]; first[y]=ecnt; to[ecnt]=x;
    }
    deep[1]=1; dfs1(1,0); ecnt=0; top[1]=1; dfs2(1,0);
    build(1,1,n); int z,grand;
    while(m--) {
    scanf("%s",ch);
    if(ch[0]=='Q') {
        x=getint(); y=getint();
        grand=lca(x,y); ans=0;
        ask_sum(x,grand); ask_sum(y,grand);
        printf("%d\n",ans-1);
    }
    else{
        x=getint(); y=getint(); z=getint();
        grand=lca(x,y); 
        ask_change(x,grand,z); ask_change(y,grand,z);
    }
    }
}

int main()
{
  work();
  return 0;
}