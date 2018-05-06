#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 200010
#define MAXM 4000010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
    int x,y,z;
}E[MAXM];

int dis[MAXN],instack[MAXN];
int last[MAXN],ne[MAXM],edge_cnt;
int n,m,s,t,k;

void add_edge(int x,int y,int z){
    E[++edge_cnt]=(edge){x,y,z};
    ne[edge_cnt]=last[x];
    last[x]=edge_cnt;
}

void spfa(){
    int ans=INF;instack[s]=1;
    memset(dis,0x3f,sizeof(dis));dis[s]=0;
    queue<int>Q;Q.push(s);
    while(!Q.empty()){
        int tp=Q.front();Q.pop();instack[tp]=0;
        for(int i=last[tp];i;i=ne[i]){
            int y=E[i].y;
            if(dis[y]>dis[tp]+E[i].z){
                dis[y]=dis[tp]+E[i].z;
                if(!instack[y])instack[y]=1,Q.push(y);
            }
        }
    }
    for(int i=0;i<=k;i++)ans=min(ans,dis[i*n+t]);
    printf("%d",ans);
}

int main(){
    freopen("bzoj2763.in","r",stdin);
    cin>>n>>m>>k>>s>>t;
    for(int i=1;i<=m;i++){
        int x,y,z;scanf("%d%d%d",&x,&y,&z);
        for(int j=0;j<=k;j++)add_edge(x+j*n,y+j*n,z),add_edge(y+j*n,x+j*n,z);
        for(int j=0;j<k;j++)add_edge(x+j*n,y+j*n+n,0),add_edge(y+j*n,x+j*n+n,0);
    }
    spfa();
    return 0;
}
