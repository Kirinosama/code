#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 30010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,a[MAXN];
int fa[MAXN],ch[MAXN][2],sum[MAXN],rev[MAXN];

int wh(int x){
    return ch[fa[x]][1]==x;
}

bool isroot(int x){
    if(!fa[x]) return true;
    return ch[fa[x]][0]!=x && ch[fa[x]][1]!=x;
}

void pushdown(int x){
    if(rev[x]){
        swap(ch[x][0],ch[x][1]);
        rev[ch[x][0]]^=1;
        rev[ch[x][1]]^=1;
        rev[x]=0;
    }
}

void pushup(int x){
    if(fa[x]) pushup(fa[x]);
    pushdown(x);
}

void maintain(int x){
    sum[x]=sum[ch[x][0]]+sum[ch[x][1]]+a[x];
}

void rot(int x){
    int f=fa[x],g=fa[f],c=wh(x);
    ch[f][c]=ch[x][!c];
    if(ch[f][c])fa[ch[f][c]]=f;
    fa[x]=g;
    if(g)ch[g][wh(f)]=x;
    fa[f]=x;ch[x][!c]=f;
    maintain(f);maintain(x);
}

void splay(int x){
    pushup(x);
    for(;!isroot(x);rot(x)){
        if(!isroot(fa[x]) && !isroot(fa[fa[x]]))
            rot(wh(x)==wh(fa[x])?fa[x]:x);
    }
}

void access(int x){
    for(int p=0;x;p=x,x=fa[x]){
        splay(x);ch[x][1]=p;maintain(x);
    }
}

void makeroot(int x){
    access(x);rev[x]^=1;
}

void solve(){
    char opt[10];int x,y;
    scanf("%s %d %d",opt,&x,&y);
}

int main(){
    freopen("bzoj1180.in","r",stdin);
    cin>>n;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    cin>>m;
    while(m--)solve();
    return 0;
}
