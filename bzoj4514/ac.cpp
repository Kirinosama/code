#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;

typedef long long LL;
const int SZ = 1000010;
const LL INF = 100000000000000010;

int n;

int head[SZ],nxt[SZ];

struct edge{
    int f,t;
    LL d,c;
}l[SZ];

void build(int f,int t,LL d,LL c)
{
    static int tot = 1;
    l[++ tot].f = f; l[tot].t = t; l[tot].d = d; l[tot].c = c;
    nxt[tot] = head[f];
    head[f] = tot;
}

void insert(int f,int t,LL d,LL c)
{
    build(f,t,d,c); build(t,f,0,-c);
}

bool use[SZ];
LL dist[SZ];
int pre[SZ];
queue<int> q;

bool spfa(int s,int e)
{
    memset(dist,-128,sizeof(dist));
    dist[s] = 0;
    use[s] = 1;
    q.push(s);
    while(q.size())
    {
        int u = q.front(); q.pop();
        use[u] = 0;
        for(int i = head[u];i;i = nxt[i])
        {
            int v = l[i].t;
            if(l[i].d && dist[v] < dist[u] + l[i].c)
            {
                dist[v] = dist[u] + l[i].c;
                pre[v] = i;
                if(!use[v])
                {
                    use[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return dist[e] < -INF ? false : true;
}

LL cost = 0;

LL dfs(int s,int e)
{
    LL flow = INF;

    for(int i = pre[e];i;i = pre[l[i].f])
        flow = min(flow,l[i].d);

    if(cost + flow * dist[e] < 0) flow = -cost / dist[e];   
    cost += flow * dist[e];

    for(int i = pre[e];i;i = pre[l[i].f])
        l[i].d -= flow,l[i ^ 1].d += flow;
    return flow;
}

LL EK(int s,int e)
{
    LL ans = 0;
    while(spfa(s,e))
    {
        LL tmp = dfs(s,e);
        if(tmp == 0) break;
        ans += tmp;
    }
    return ans;
}

int a[SZ];
LL c[SZ],b[SZ];

bool jojo[SZ];

int zys(int n)
{
    int x = n;
    int ans = 0;
    for(int i = 2;i <= sqrt(x);i ++)
    {
        while(n % i == 0)
        {
            n /= i;
            ans ++;
        }
    }
    if(n != 1)
        ans ++;
    return ans;
}

bool ispri(int x)
{
    for(int i = 2;i <= sqrt(x);i ++)
        if(x % i == 0)
            return false;
    return true;
}

int main()
{
    freopen("bzoj4514.in","r",stdin);
    scanf("%d",&n);
    for(int i = 1;i <= n;i ++) scanf("%d",&a[i]);
    for(int i = 1;i <= n;i ++) scanf("%lld",&b[i]);
    for(int i = 1;i <= n;i ++) scanf("%lld",&c[i]);

    for(int i = 1;i <= n;i ++) jojo[i] = zys(a[i]) % 2;

    int s = n + 1,e = n + 2;

    for(int i = 1;i <= n;i ++)
    {
        if(jojo[i] == 1)
            insert(s,i,b[i],0);
        else
            insert(i,e,b[i],0);
    }

    for(int i = 1;i <= n;i ++)
    {
        for(int j = i + 1;j <= n;j ++)
        {
            if(jojo[i] ^ jojo[j])
            {
                if(a[i] % a[j] == 0 && ispri(a[i] / a[j]))
                {
                    if(jojo[i]) insert(i,j,INF,c[i] * c[j]);
                    else insert(j,i,INF,c[i] * c[j]);
                }
                if(a[j] % a[i] == 0 && ispri(a[j] / a[i]))
                {
                    if(jojo[i]) insert(i,j,INF,c[i] * c[j]);
                    else insert(j,i,INF,c[i] * c[j]);                   
                }
            }
        }
    }

    printf("%lld",EK(s,e));

    return 0;
}
/*
3
2 4 8
2 200 7
-1 -2 1

*/
