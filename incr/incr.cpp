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

int a[MAXN],b[MAXN],n;
int add[MAXN*4],Min[MAXN*4],ls[MAXN*4],rs[MAXN*4],rt;
int ti;

void premake(){
    for(int i=1;i<=n;i++)b[i]=a[i];
    sort(b+1,b+1+n);
    for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+n+1,a[i])-b;
}

void build(int &x,int l,int r){
    x=++ti;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(ls[x],l,mid);
    build(rs[x],mid+1,r);
}

void pushdown(int x){
    if(ls[x]){
        add[ls[x]]+=add[x];
        Min[ls[x]]+=add[x];
    }
    if(rs[x]){
        add[rs[x]]+=add[x];
        Min[rs[x]]+=add[x];
    }
    add[x]=0;
}

void maintain(int x){
    Min[x]=min(Min[ls[x]],Min[rs[x]]);
}

int query(int x,int l,int r,int L,int R){
    if(l>R || r<L) return INF;
    if(l>=L && r<=R) return Min[x];
    else{
        int mid=(l+r)>>1;
        pushdown(x);
        int res=min(query(ls[x],l,mid,L,R),query(rs[x],mid+1,r,L,R));
        maintain(x);
        return res;
    }
}

void make(int x,int l,int r,int pos,int k){
    if(l==r) Min[x]=k;
    else{
        int mid=(l+r)>>1;
        pushdown(x);
        if(pos<=mid)make(ls[x],l,mid,pos,k);
        else make(rs[x],mid+1,r,pos,k);
        maintain(x);
    }
}

void Add(int x,int l,int r,int L,int R,int k){
    if(l>R || r<L) return;
    if(l>=L && r<=R){
        add[x]+=k,Min[x]+=k;
    }else{
        int mid=(l+r)>>1;
        pushdown(x);
        Add(ls[x],l,mid,L,R,k);
        Add(rs[x],mid+1,r,L,R,k);
        maintain(x);
    }
}

int main(){
    freopen("incr.in","r",stdin);
    freopen("incr.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        a[i]+=n-i;
    }
    premake();
    build(rt,0,n);
    for(int i=1;i<=n;i++){
        int now=query(rt,0,n,0,a[i]);
        make(rt,0,n,a[i],now);
        if(a[i]-1>=0) Add(rt,0,n,0,a[i]-1,1);
        if(a[i]+1<=n) Add(rt,0,n,a[i]+1,n,1);
    }
    printf("%d",query(rt,0,n,0,n));
    return 0;
}
