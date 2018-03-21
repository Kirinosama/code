#include <cstdio>  
#include <algorithm>  
  
using namespace std;  
  
typedef long long LL;  
  
const int maxn = 50005, inf = 0x3f3f3f3f;  
  
int n, head[maxn], cnt, pre[maxn], depth[maxn], son[maxn], bro[maxn];  
LL sum[maxn], res[maxn], ans;  
  
struct _edge {  
    int v, next;  
} g[maxn << 1];  
  
inline int iread() {  
    int f = 1, x = 0; char ch = getchar();  
    for(; ch < '0' || ch > '9'; ch = getchar()) f = ch == '-' ? -1 : 1;  
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';  
    return f * x;  
}  
  
inline void add(int u, int v) {  
    g[cnt] = (_edge){v, head[u]};  
    head[u] = cnt++;  
}  
  
inline void dfs(int x) {  
    for(int i = head[x]; ~i; i = g[i].next) if(g[i].v ^ pre[x]) {  
        depth[g[i].v] = depth[x] + 1;  
        pre[g[i].v] = x;  
        dfs(g[i].v);  
        sum[x] += sum[g[i].v];  
        res[x] += res[g[i].v] + sum[g[i].v];  
        if(!son[x] || sum[g[i].v] > sum[son[x]]) bro[x] = son[x], son[x] = g[i].v;  
        else if(!bro[x] || sum[g[i].v] > sum[bro[x]]) bro[x] = g[i].v;  
    }  
}  
  
int cut;  
  
inline void center(LL &ret, int root, int x, LL k) {  
    ret = min(ret, k);  
    int v = son[x];  
    if(v == cut || sum[bro[x]] > sum[son[x]]) v = bro[x];  
    if(!v) return;  
    center(ret, root, v, k + sum[root] - 2 * sum[v]);  
}  
  
inline void solve(int x) {  
    for(int i = head[x]; ~i; i = g[i].next) if(g[i].v ^ pre[x]) {  
        cut = g[i].v;  
        LL gx = inf, gy = inf;  
        for(int j = x; j; j = pre[j]) sum[j] -= sum[cut];  
        center(gx, 1, 1, res[1] - res[cut] - depth[cut] * sum[cut]);  
        center(gy, cut, cut, res[cut]);  
        ans = min(ans, gx + gy);  
        for(int j = x; j; j = pre[j]) sum[j] += sum[cut];  
        solve(g[i].v);  
    }  
}  
  
int main() {  
    n = iread();  
    for(int i = 1; i <= n; i++) head[i] = -1; cnt = 0;  
  
    for(int i = 1; i < n; i++) {  
        int u = iread(), v = iread();  
        add(u, v); add(v, u);  
    }  
    for(int i = 1; i <= n; i++) sum[i] = iread();  
  
    ans = inf;  
    dfs(1);  
    solve(1);  
    printf("%lld\n", ans);  
    return 0;  
}  
