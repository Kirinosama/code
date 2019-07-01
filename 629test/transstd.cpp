#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
using namespace std;
int n,m,s,t;
typedef pair<int, int> ii;
#define fi first
#define se second
priority_queue<ii, vector<ii>, greater<ii> > q;
#define maxn 100011
#define maxm 2000010
int nxt[maxn];
int f[maxn], cnt;
struct edges{
    int to, p, q, nxt;
}edge[maxm];
int l;
void addedge(int x,int y,int p,int q){
    edge[++l] = (edges){y, p, q, nxt[x]}; nxt[x] = l;
    edge[++l] = (edges){x, p, q, nxt[y]}; nxt[y] = l;
}
bool b[maxn];
int dis[maxn];
int w[maxn];
#define inf 0x7fffffff
int d(int x,int y, int z){ 
    if (x % (y + z) < y)
        return 1;
    return (x / (y+z) + 1) * (y+z) - x + 1;
}
int main(){
//	freopen("6.in","r",stdin);
//	freopen("6.out","w",stdout);
    scanf("%d %d",&n,&m);
    scanf("%d %d",&s,&t);
    for (int i=1;i<=m;i++) {
        int x,y,p,q;
        scanf("%d%d%d%d", &x, &y, &p, &q);
        addedge(x,y,p,q);
    }
    q.push(ii(0, s));
    for (int i=1;i<=n;i++) dis[i] = inf;
    dis[s] = 0;
    while (!q.empty()) {
        int u = q.top().se;
        q.pop();
        if (b[u]) continue;
        b[u] = 1;
        for (int i=nxt[u]; i; i=edge[i].nxt){
            if (dis[edge[i].to] > dis[u] + d(dis[u], edge[i].p, edge[i].q)){
                dis[edge[i].to] = dis[u] + d(dis[u], edge[i].p, edge[i].q);
                w[edge[i].to] = u;
                q.push(ii(dis[edge[i].to], edge[i].to));
            }
            if (dis[edge[i].to] == dis[u] + d(dis[u], edge[i].p, edge[i].q))
                w[edge[i].to] = min(w[edge[i].to], u);
        }
    }
    printf("%d\n",dis[t]);
    int tmp = t;
    while (tmp != s) {
        f[++cnt] = tmp;
        tmp = w[tmp];
    }
    f[++cnt] = s;
    for (int i = cnt; i; i--) printf("%d ", f[i]);
    return 0;
}

