#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 50010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,T,rt,k,ti,now;
int size,exist[100];
int L[MAXN*4][6],R[MAXN*4][6],ls[MAXN*4],rs[MAXN*4];

struct data{
    int num[6];
    int dis(const data &a)const{
        int res=0;
        for(int i=1;i<=m;i++)res+=(num[i]-a.num[i])*(num[i]-a.num[i]);
        return res;
    }
}a[MAXN],b,s[11],anss[11];

int min(int x,int y){
    if(x<y) return x;
    return y;
}

int max(int x,int y){
    if(x>y) return x;
    return y;
}

int abs(int x){
    return x>=0?x:-x;
}

void maintain(int x){
    for(int i=1;i<=m;i++)L[x][i]=min(L[ls[x]][i],L[rs[x]][i]);
    for(int i=1;i<=m;i++)R[x][i]=max(R[ls[x]][i],R[rs[x]][i]);
}

bool cmp(const data &x,const data &y){
    return x.num[now]<y.num[now];
}

void build(int &x,int l,int r,int d){
    now=d,x=++ti;
    if(l==r){
        for(int i=1;i<=m;i++)L[x][i]=R[x][i]=a[l].num[i];
        return;
    }else{
        int mid=(l+r)>>1;
        nth_element(a+l,a+mid,a+r+1,cmp);
        build(ls[x],l,mid,d==m?1:d+1);
        build(rs[x],mid+1,r,d==m?1:d+1);
        maintain(x);
    }
}

void pushdown(int x){
    if(x*2<=k && x*2+1<=k){
        if(s[x*2].dis(b)>s[x*2+1].dis(b) && s[x*2].dis(b)>s[x].dis(b))
            swap(s[x],s[x*2]),pushdown(x*2);
        if(s[x*2+1].dis(b)>s[x*2].dis(b) && s[x*2+1].dis(b)>s[x].dis(b))
            swap(s[x],s[x*2+1]),pushdown(x*2+1);
    }else if(x*2<=k){
        if(s[x*2].dis(b)>s[x].dis(b)) swap(s[x],s[x*2]),pushdown(x*2);
    }
}

void pushup(int x){
    if(!x) return;
    if(s[x].dis(b)>s[x>>1].dis(b)){
        swap(s[x],s[x>>1]);
        pushup(x>>1);
    }
}

void add(data x){
    if(size<k) s[++size]=x,pushup(size),exist[size]=1;
    else if(b.dis(x)<b.dis(s[1])){
        s[1]=x;pushdown(1);
    }
}

bool judge(int dist){
    if(size<k) return true;
    return dist<b.dis(s[1]);
}

bool ok(int x){
    if(size<k) return true;
    int res=0;
    for(int i=1;i<=m;i++){
        int Min=INF;
        if(L[x][i]<=b.num[i] && R[x][i]>=b.num[i]) Min=0;
        Min=min(Min,abs(L[x][i]-b.num[i]));
        Min=min(Min,abs(R[x][i]-b.num[i]));
        res+=Min*Min;
    }
    return res<b.dis(s[1]);
}

void del(int x){
    if(exist[x*2] && exist[x*2+1]){
        if(s[x*2+1].dis(b)>s[x*2].dis(b)) swap(s[x*2+1],s[x]),del(x*2+1);
        else swap(s[x*2],s[x]),del(x*2);
    }else if(exist[x*2]){
        swap(s[x*2],s[x]),del(x*2);
    }else if(exist[x*2+1]){
        swap(s[x*2+1],s[x]),del(x*2+1);
    }
}

void print(){
    printf("the closest %d points are:\n",k);
    for(int i=1;i<=k;i++){
        anss[i]=s[1];del(1);
    }
    for(int i=k;i>=1;i--){
        for(int j=1;j<=m;j++)printf("%d ",anss[i].num[j]);
        cout<<endl;
    }
}

void query(int x,int l,int r,int d){
    if(l==r){
        if(judge(b.dis(a[l]))) add(a[l]);
    }else{
        int mid=(l+r)>>1;
        if(ok(ls[x])) query(ls[x],l,mid,d==m?1:d+1);
        if(ok(rs[x])) query(rs[x],mid+1,r,d==m?1:d+1);
    }
}

int main(){
    freopen("bzoj3053.in","r",stdin);
    while(cin>>n>>m){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",&a[i].num[j]);
        for(int i=1;i<=m;i++)
            L[0][i]=INF,R[0][i]=-INF;
        rt=ti=0;build(rt,1,n,1);
        cin>>T;
        while(T--){
            for(int i=1;i<=m;i++)scanf("%d",&b.num[i]);
            scanf("%d",&k);size=0;
            memset(exist,0,sizeof(exist));
            query(rt,1,n,1);print();
        }
    }
    return 0;
}
