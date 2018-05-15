#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010
#define MAXM 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
    int x,y;
}E[MAXM];

int last[MAXN],ne[MAXM],edge_cnt;
int n,m,vis[MAXN];

void add_edge(int x,int y){
    E[++edge_cnt]=(edge){x,y};
    ne[edge_cnt]=last[x];
    last[x]=edge_cnt;
}

void dfs(int x,int k){
    if(vis[x]) return;
    vis[x]=k;
    for(int i=last[x];i;i=ne[i])
        dfs(E[i].y,k);
}

int main(){
    freopen("graph.in","r",stdin);
    freopen("graph.out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int x,y;scanf("%d%d",&y,&x);
        add_edge(x,y);
    }
    for(int i=n;i>=1;i--)dfs(i,i);
    for(int i=1;i<=n;i++)printf("%d ",vis[i]);
    return 0;
}
