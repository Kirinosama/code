#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <ctime>
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
#define PB push_back
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define calm (l+r)>>1
const int INF=1e9+7;

const int maxn=30010;
struct EE{
    int next,to;
    EE(){}
    EE(int to,int next):to(to),next(next){}
}edge[maxn*2];
int n,Ecnt,tot,head[maxn],val[maxn];
int top[maxn],fa[maxn],rev[maxn],id[maxn],num[maxn],son[maxn],deep[maxn];

inline void addedge(int a,int b){
    edge[Ecnt]=EE(b,head[a]);
    head[a]=Ecnt++;
}
void dfs1(int s,int pre,int d){
    deep[s]=d;fa[s]=pre;num[s]=1;son[s]=0;
    for(int i=head[s];~i;i=edge[i].next){
        int t=edge[i].to;
        if(t==pre)continue;
        dfs1(t,s,d+1);num[s]+=num[t];
        if(son[s]==0||num[t]>num[son[s]]){
            son[s]=t;
        }
    }
}
void dfs2(int s,int rt){
    top[s]=rt;id[s]=++tot;rev[id[s]]=s;
    if(son[s]==0)return;
    dfs2(son[s],rt);
    for(int i=head[s];~i;i=edge[i].next){
        int t=edge[i].to;
        if(t==fa[s]||t==son[s])continue;
        dfs2(t,t);
    }
}
//SegmentTree
struct node{
    int MAX,sum;
}tree[maxn<<2];
inline void pushup(int rt){
    tree[rt].sum=tree[rt<<1].sum+tree[rt<<1|1].sum;
    tree[rt].MAX=max(tree[rt<<1].MAX,tree[rt<<1|1].MAX);
}
void build(int l,int r,int rt){
    if(l==r){
        tree[rt].MAX=tree[rt].sum=val[rev[l]];
        return;
    }
    int m=calm;
    build(lson);build(rson);
    pushup(rt);
}
void update(int x,int v,int l,int r,int rt){
    if(l==r){
        tree[rt].MAX=tree[rt].sum=v;
        return;
    }
    int m=calm;
    if(x<=m)update(x,v,lson);
    if(x>m)update(x,v,rson);
    pushup(rt);
}
int querymax(int L,int R,int l,int r,int rt){
    if(L<=l&&r<=R){
        return tree[rt].MAX;
    }
    int m=calm,ans=-INF;
    if(L<=m)ans=max(ans,querymax(L,R,lson));
    if(R>m)ans=max(ans,querymax(L,R,rson));
    return ans;
}
int querysum(int L,int R,int l,int r,int rt){
    if(L<=l&&r<=R){
        return tree[rt].sum;
    }
    int m=calm,ans=0;
    if(L<=m)ans+=querysum(L,R,lson);
    if(R>m)ans+=querysum(L,R,rson);
    return ans;
}

int findmax(int x,int y){
    int f1=top[x],f2=top[y],ans=-INF;
    while(f1!=f2){
        if(deep[f1]<deep[f2]){
            swap(f1,f2);swap(x,y);
        }
        ans=max(ans,querymax(id[f1],id[x],1,n,1));
        x=fa[f1];
        f1=top[x];
    }
    if(deep[x]>deep[y]){
        ans=max(ans,querymax(id[y],id[x],1,n,1));
    }
    else{
        ans=max(ans,querymax(id[x],id[y],1,n,1));
    }
    return ans;
}
int findsum(int x,int y){
    int f1=top[x],f2=top[y],ans=0;
    while(f1!=f2){
        if(deep[f1]<deep[f2]){
            swap(f1,f2);swap(x,y);
        }
        ans+=querysum(id[f1],id[x],1,n,1);
        x=fa[f1];f1=top[x];
    }
    if(deep[x]>deep[y]){
        ans+=querysum(id[y],id[x],1,n,1);
    }
    else{
        ans+=querysum(id[x],id[y],1,n,1);
    }
    return ans;
}

int main(){
    scanf("%d",&n);
    memset(head,-1,sizeof head);Ecnt=0;
    for(int i=1;i<n;i++){
        int a,b;scanf("%d%d",&a,&b);
        addedge(a,b);addedge(b,a);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&val[i]);
    }
    tot=0;
    dfs1(1,0,1);dfs2(1,1);
    build(1,n,1);
    char op[10];int q,a,b;
    scanf("%d",&q);
    while(q--){
        scanf("%s%d%d",op,&a,&b);
        if(op[0]=='C'){
            update(id[a],b,1,n,1);
            val[a]=b;
        }
        else if(op[1]=='M'){
            printf("%d\n",findmax(a,b));
        }
        else{
            printf("%d\n",findsum(a,b));
        }
    }
    return 0;
}