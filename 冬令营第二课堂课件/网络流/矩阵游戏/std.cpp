//By IzumiKonata
 
#include <bits/stdc++.h>
#define rep(i, l, r) for(int i = l; i <= r; ++i)
#define red(i, r, l) for(int i = r; i >= l; --i)
#define MEM(x, y) memset(x, y, sizeof(x))
#define cmax(x, y) ((x) = max(x, y))
#define cmin(x, y) ((x) = min(x, y))
#define X first
#define Y second
#ifdef _KONATA_
#   define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#   define debug(...)
#endif
 
using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned int UI;
typedef pair<int, int> PI;
 
const int INF = 0x7fffffff;
const LD eps = 1e-8;
const LL MOD = 1e9 + 7;
template<typename T>inline void read(T& a){
    a = 0; char c; bool f = 0;
    while (!isdigit(c = getchar())) if (c == '-') f = 1;
    do a = a * 10 + c - '0'; while (isdigit(c = getchar()));
    if (f) a = -a;
}
 
 
const int MAXN = 222;
struct edge{
    int to, next, f;
}E[MAXN * MAXN * 2];
int hd[MAXN * 2], cur[MAXN * 2], ne = 2;
void addedge(int x, int y, int f){
    E[ne] = edge{y, hd[x], f};
    hd[x] = ne++;
}
#define inv(x) ((x) ^ 1)
int dis[MAXN * 2], q[MAXN * 2];
bool bfs(int S, int T){
    memset(dis, -1, sizeof(dis));
    int l, r;
    for (dis[q[l = r = 1] = S] = 0; l <= r && dis[T] == -1; ++l)
        for (int i = hd[q[l]]; i; i = E[i].next)
            if (E[i].f && dis[E[i].to] == -1)
                dis[E[i].to] = dis[q[l]] + 1, q[++r] = E[i].to;
    if (dis[T] == -1) return 0;
    rep(i, 1, T) cur[i] = hd[i];
    return 1;
}
int dfs(int x, int maxf, int T){
    if (x == T) return maxf;
    int r = 0;
    for (int &i = cur[x]; i; i = E[i].next)
        if (E[i].f && dis[E[i].to] == dis[x] + 1){
            int t = dfs(E[i].to, min(maxf, E[i].f), T);
            maxf -= t; E[i].f -= t;
            r += t; E[inv(i)].f += t;
            if (!maxf) break;
        }
    return r;
}
int dinic(int S, int T){
    int ret = 0;
    while(bfs(S, T)) ret += dfs(S, INF, T);
    return ret;
}
int N, M, S, T;
void solve(){
    read(N);
    S = 2 * N + 1; T = S + 1;
    rep(i, 1, T) hd[i] = 0; ne = 2;
    rep(i, 1, N) rep(j, 1, N){
        int x; read(x);
        if (x) addedge(i, N + j, 1), addedge(N + j, i, 0);
    }
    rep(i, 1, N)
        addedge(S, i, 1), addedge(i, S, 0),
        addedge(N + i, T, 1), addedge(T, N + i, 0);
    puts(dinic(S, T) == N ? "Yes" : "No");
}
int main(){
    int T; read(T); while(T--) solve(); 
    return 0;
}
