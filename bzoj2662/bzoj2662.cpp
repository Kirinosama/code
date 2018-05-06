#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

#define MAXM 3000010
#define MAXN 6010

struct edge{
    int x,y,z;
}E[MAXM],beg[MAXM];

int n,m,k;
int edge_cnt,last[MAXN],ne[MAXM];
int dis[MAXN];
bool instack[MAXN];

void add_edge(int x,int y,int z){
    E[++edge_cnt]=(edge){x,y,z};
    ne[edge_cnt]=last[x];
    last[x]=edge_cnt;
}

void premake(){
    for(int i=0;i<=k;i++){
        for(int j=1;j<=m;j++){
            add_edge(beg[j].x+i*n,beg[j].y+i*n,beg[j].z);
            add_edge(beg[j].y+i*n,beg[j].x+i*n,beg[j].z);
            if(i==k) continue;
            add_edge(beg[j].x+i*n,beg[j].y+i*n+n,beg[j].z/2);
            add_edge(beg[j].y+i*n,beg[j].x+i*n+n,beg[j].z/2);
        }
    }
}

void spfa(){
    queue<int>Q;Q.push(1);instack[1]=true;
    memset(dis,0x3f,sizeof(dis));dis[1]=0;
    while(!Q.empty()){
        int tp=Q.front();Q.pop();instack[tp]=false;
        for(int i=last[tp];i;i=ne[i]){
            int y=E[i].y;
            if(dis[y]>dis[tp]+E[i].z){
                dis[y]=dis[tp]+E[i].z;
                if(!instack[y])instack[y]=true,Q.push(y);
            }
        }
    }
    int ans=INF;
    for(int i=1;i<=k+1;i++)ans=min(ans,dis[i*n]);
    cout<<ans;
}

int main(){
    freopen("bzoj2662.in","r",stdin);
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        beg[i]=(edge){x,y,z};
    }
    premake();
    spfa();
    return 0;
}
