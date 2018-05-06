#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 2010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
    int x,y,z;
    bool operator < (const edge &a)const{
        return z<a.z;
    }
}E[MAXN*MAXN];

int n,edge_cnt,father[MAXN];

int find(int x){
    return father[x]==x?x:father[x]=find(father[x]);
}

void kruskal(){
    sort(E+1,E+edge_cnt+1);
    for(int i=1;i<=n+1;i++)father[i]=i;
    int cnt=0;ll ans=0;
    for(int i=1;i<=edge_cnt;i++){
        if(find(E[i].x)!=find(E[i].y))
            father[find(E[i].x)]=find(E[i].y),cnt++,ans+=E[i].z;
        if(cnt==n) break;
    }
    cout<<ans;
}

int main(){
    freopen("bzoj3714.in","r",stdin);
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++){
            int x;scanf("%d",&x);
            E[++edge_cnt]=(edge){i,j+1,x};
        }
    kruskal();
    return 0;
}
