#include <bits/stdc++.h>
using namespace std;
struct edge
{
    int v, w, nxt;
}e[30005];
int r, c, fst[805], h[25][25], level[805], q[805], etot = 1;
char s[25];

void addedge(int u, int v, int w)
{
    e[++etot] = (edge){v, w, fst[u]}, fst[u] = etot;
    e[++etot] = (edge){u, 0, fst[v]}, fst[v] = etot;
}

int BFS()
{
    int front = 0, back, u;
    memset(level, 0, sizeof(level));
    level[2 * r * c + 1] = 1, q[back = 1] = 2 * r * c + 1;
    while(front != back)
    {
        u = q[++front];
        for(int i = fst[u]; i; i = e[i].nxt)
            if(e[i].w && !level[e[i].v])
            {
                level[e[i].v] = level[u] + 1;
                q[++back] = e[i].v;
            }
    }
    return level[2 * r * c + 2];
}

int Dinic(int u, int lim)
{
    int tmp = lim;
    if(u == 2 * r * c + 2) return lim;
    for(int i = fst[u]; i; i = e[i].nxt)
        if(e[i].w && level[e[i].v] == level[u] + 1)
        {
            int flow = Dinic(e[i].v, min(tmp, e[i].w));
            e[i].w -= flow, e[i ^ 1].w += flow;
            if(!(tmp -= flow)) break;
        }
    if(tmp == lim) level[u] = 0;
    return lim - tmp;
}

int main()
{
    int d, ans = 0;
    scanf("%d%d%d", &r, &c, &d);
    for(int i = 0; i < r; ++i)
    {
        scanf("%s", s + 1);
        for(int j = 1; j <= c; ++j)
        {
            h[i + 1][j] = s[j] - 48;
            addedge(i * c + j, (r + i) * c + j, h[i + 1][j]);
        }
    }
    for(int i = 0; i < r; ++i)
    {
        scanf("%s", s + 1);
        for(int j = 1; j <= c; ++j)
            if(s[j] == 'L')
                ++ans, addedge(2 * r * c + 1, i * c + j, 1);
    }
    for(int i = 0; i < r; ++i)
        for(int j = 1; j <= c; ++j)
            if(h[i + 1][j] && (i < d || i >= r - d || j <= d || j > c - d))
                addedge((r + i) * c + j, 2 * r * c + 2, 400);
    for(int i = d; i < r - d; ++i)
        for(int j = d + 1; j <= c - d; ++j)
            if(h[i + 1][j])
                for(int k = -d; k <= d; ++k)
                    for(int l = -d; l <= d; ++l)
                        if(h[i + k + 1][j + l] && k * k + l * l <= d * d)
                            addedge((r + i) * c + j, (i + k) * c + j + l, 400);
    while(BFS())
        ans -= Dinic(2 * r * c + 1, 400);
    printf("%d\n", ans);
    return 0;
}