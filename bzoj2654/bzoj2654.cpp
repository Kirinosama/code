#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
    int x,y,w,col;
    void in(){scanf("%d%d%d%d",&x,&y,&w,&col);x++,y++;}
    bool operator < (const edge &a)const{
        if(w==a.w) return col<a.col;
        return w<a.w;
    }
}E[100010];

int n,m,k,father[50010];
ll ans;

int find(int x){
    return father[x]==x?x:father[x]=find(father[x]);
}

bool judge(int x){
    for(int i=1;i<=m;i++)if(!E[i].col)
        E[i].w+=x;
    sort(E+1,E+m+1);ans=0;
    for(int i=1;i<=n;i++)father[i]=i;
    int now=0,cnt=0;
    for(int i=1;i<=m;i++){
        if(find(E[i].x)!=find(E[i].y)){
            now++;father[find(E[i].x)]=find(E[i].y),ans+=(ll)E[i].w;
            if(!E[i].col) cnt++;
        }
        if(now==n-1) break;
    }
    for(int i=1;i<=m;i++)if(!E[i].col)
        E[i].w-=x;
    return cnt>=k;
}

int main(){
    freopen("bzoj2654.in","r",stdin);
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++)E[i].in();
    int l=-5000000,r=5000000;ll res;
    while(l<=r){
        int mid=(l+r)>>1;
        if(judge(mid)) l=mid+1,res=ans-(ll)mid*(ll)k;
        else r=mid-1;
    }
    cout<<res;
    return 0;
}
