#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <utility>
 
using namespace std;
 
const int MaxN = 2000010;
 
typedef pair<int,int> PII;
 
struct Node{
    int v,c;
    Node *next;
}*g[MaxN],pool[MaxN*3],*tail=pool;
int n,m;
int size;
int S,T;
 
inline int mapping(int x,int y,int t){
    return (t-1)*size+(x-1)*m+y;
}
void make_edge(int u,int v,int c){
    Node *a=tail++;
    a->v=v;a->c=c;a->next=g[u];g[u]=a;
}
int dijkstra(){
    priority_queue< PII,vector<PII>,greater<PII> > q;
    static int dist[MaxN],flag[MaxN];
    memset(dist,0x7f,sizeof(dist));
    memset(flag,0,sizeof(flag));
    dist[S]=0;q.push(make_pair(0,S));
    while(!q.empty()){
        PII t=q.top();q.pop();
        if(flag[t.second]) continue;flag[t.second]=1;
        for(Node *p=g[t.second];p;p=p->next) if(dist[p->v]>dist[t.second]+p->c){
            dist[p->v]=dist[t.second]+p->c;
            q.push(make_pair(dist[p->v],p->v));
        }
    }
    return dist[T];
}
int main()
{
    scanf("%d%d",&n,&m);
    n--,m--;
    size=n*m;
    S=0,T=2*size+1;
    for(int i=1;i<=n+1;i++){
        for(int j=1;j<=m;j++){
            int t;scanf("%d",&t);
            if(i==1) make_edge(mapping(i,j,1),T,t);
            else if(i>n) make_edge(S,mapping(n,j,2),t);
            else {
                make_edge(mapping(i,j,1),mapping(i-1,j,2),t);
                make_edge(mapping(i-1,j,2),mapping(i,j,1),t);
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m+1;j++){
            int t;scanf("%d",&t);
            if(j==1) make_edge(S,mapping(i,j,2),t);
            else if(j>m) make_edge(mapping(i,m,1),T,t);
            else {
                make_edge(mapping(i,j-1,1),mapping(i,j,2),t);
                make_edge(mapping(i,j,2),mapping(i,j-1,1),t);
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int t;scanf("%d",&t);
            make_edge(mapping(i,j,1),mapping(i,j,2),t);
            make_edge(mapping(i,j,2),mapping(i,j,1),t);
        }
    }
//  for(int i=0;i<=size+1;i++)
//      for(Node *p=g[i];p;p=p->next)
//          printf("<%d,%d>:%d\n",i,p->v,p->c);
    printf("%d\n",dijkstra());
    return 0;
}
