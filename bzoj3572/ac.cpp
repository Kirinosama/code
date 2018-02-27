#include <cstdio>
#include <algorithm>
#include <map>
#define mp(x,y) std::make_pair(x,y)
const int N = 300000 + 9;
int f[N][20],n,m,ec,son[N],lnk[N * 2],nxt[N * 2],dfn[N],sz[N],d[N],Time;
inline bool cmp(const int lhs,const int rhs){return dfn[lhs] < dfn[rhs];}
inline void addedge(const int x,const int y)
{
    nxt[++ec] = son[x];
    lnk[son[x] = ec] = y;
}
void dfs(int u)
{
    dfn[u] = ++Time;
    sz[u] = 1;
    for (int v,i = son[u]; i; i = nxt[i])
        if ((v = lnk[i]) != f[u][0]) {
            f[v][0] = u;
            for (int j = 0; (f[v][j + 1] = f[f[v][j]][j]); ++j);
            d[v] = d[u] + 1;
            dfs(v);
            sz[u] += sz[v];
        }
}
int find(int u,int dep)
{
    if (d[u] < dep)
        puts("^ ^");
    for (int i = 19; i >= 0; --i)
        if (d[f[u][i]] >= dep) u = f[u][i];
    return u;
}
int LCA(int u,int v)
{
    if (d[u] < d[v]) std::swap(u,v);
    for (int i = 19; i >= 0; --i)
        if (d[f[u][i]] >= d[v]) u = f[u][i];
    if (u == v) return u;
    for (int i = 19; i >= 0; --i)
        if (f[u][i] != f[v][i]) u = f[u][i],v = f[v][i];
    return f[u][0];
}
void solve()
{
    static int h[N],mem[N],st[N],father[N],t[N],val[N],ans[N],w[N];
    static std::pair<int,int> g[N];
    int m,tot = 0;
    scanf("%d",&m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d",h + i);
        mem[i] = h[i];
        t[++tot] = h[i];
        g[h[i]] = mp(0,h[i]);
        ans[h[i]] = 0;
    }
    std::sort(h + 1,h + 1 + m,cmp);
    int top = 0;
    for (int i = 1; i <= m; ++i)
        if (!top) father[st[++top] = h[i]] = 0;
        else {
            int p = h[i],lca = LCA(h[i],st[top]);
            for (; d[st[top]] > d[lca]; --top)
                if (d[st[top - 1]] <= d[lca])
                    father[st[top]] = lca;
            if (st[top] != lca) {
                t[++tot] = lca;
                g[lca] = mp(0x3f3f3f3f,0);
                father[lca] = st[top];
                st[++top] = lca;
            }
            father[p] = lca;
            st[++top] = p;
        }
    std::sort(t + 1,t + 1 + tot,cmp);
    for (int i = 1; i <= tot; ++i) {
        int p = t[i];
        val[p] = sz[p];
        if (i > 1)
            w[p] = d[p] - d[father[p]];
    }
    for (int i = tot; i > 1; --i) {
        int p = t[i],fa = father[p];
        g[fa] = std::min(mp(g[p].first + w[p],g[p].second),g[fa]);
    }
    for (int i = 2; i <= tot; ++i) {
        int p = t[i],fa = father[p];
        g[p] = std::min(mp(g[fa].first + w[p],g[fa].second),g[p]);
    }
    for (int i = 1; i <= tot; ++i) {
        int p = t[i],fa = father[p];
        if (i == 1)
            ans[g[p].second] += n - sz[p];
        else {
            int x = find(p,d[fa] + 1),sum = sz[x] - sz[p];
            val[fa] -= sz[x];
            if (g[fa].second == g[p].second) ans[g[p].second] += sum;
            else {
                int mid = d[p] - ((g[fa].first + g[p].first + w[p]) / 2 - g[p].first);
                if ((g[fa].first + g[p].first + w[p]) % 2 == 0 && g[p].second > g[fa].second) ++mid;
                int y = sz[find(p,mid)] - sz[p];
                ans[g[p].second] += y;
                ans[g[fa].second] += sum - y;
            }
        }
    }
    // printf("Test: ");
    // for (int i = 1; i <= tot; ++i) printf("(%d, %d) ",t[i],val[t[i]]);puts("");
    for (int i = 1; i <= tot; ++i)
        ans[g[t[i]].second] += val[t[i]];
    for (int i = 1; i <= m; ++i) printf("%d ",ans[mem[i]]); puts("");
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("bzoj3572.in","r",stdin);
    freopen("out2","w",stdout);
    #endif
    scanf("%d",&n);
    for (int x,y,i = 1; i < n; ++i) {
        scanf("%d%d",&x,&y);
        addedge(x,y);addedge(y,x);
    }
    int q;
    scanf("%d",&q);
    dfs(d[1] = 1);
    while (q--) solve();
}