/*Time 2014 08 31 , 19:26

*/
#include <bits/stdc++.h>
#define in freopen("solve_in.txt", "r", stdin);
#define bug(x) printf("Line %d : >>>>>>>\n", (x));

using namespace std;
typedef long long LL;
const int maxn = 50000 + 100;
LL x1[maxn][2], x2[maxn][2], ans[maxn];
int cnt;

struct Node
{
    int l, r, type;
    LL c;
    int id;
} q[maxn];
int rk[maxn], t1[maxn], t2[maxn];
int n, m;
LL query(LL a[][2], int x)
{
    LL res = 0;
    for(; x > 0; x -= (x&(-x)))
    {
        if(a[x][0] == cnt) res += a[x][1];
    }
    return res;
}
LL query(int l, int r)
{
    return query(x1, l)*(r-l+1)+ (r+1)*(query(x1, r)-query(x1, l)) - (query(x2, r)-query(x2, l));
}
void add(LL a[][2], int x, LL c)
{
    for(; x <= n; x += ((-x)&x))
    {
        if(a[x][0] == cnt) a[x][1] += c;
        else a[x][0] = cnt, a[x][1] = c;
    }
}
void add(int l, int r, int c)
{
    add(x1, l, c);
    add(x2, l, (LL)l*c);
    add(x1, r+1, -c);
    add(x2, r+1, (LL)(r+1)*(-c));
}
void solve(int ll, int rr, int l, int r)
{
    if(l > r) return;
    if(ll == rr)
    {
        for(int i = l; i <= r; i++)
            if(q[rk[i]].type == 2)
            {
                ans[rk[i]] = ll;
            }
        return;
    }
    int m1 = (ll+rr)>>1, m2 = (l+r)>>1;
    cnt++;
    t1[0] = t2[0] = 0;
    for(int i = l; i <= r; i++)
    {
        if(q[rk[i]].type == 1)
        {
            if(q[rk[i]].c <= m1)
            {
                add(q[rk[i]].l, q[rk[i]].r, 1);
                t1[++t1[0]] = rk[i];
            }
            else
            {
                t2[++t2[0]] = rk[i];
            }
        }
        else
        {
            LL xx = query(q[rk[i]].l, q[rk[i]].r);
            if(xx < (LL)q[rk[i]].c)
            {
                q[rk[i]].c -= xx;
                t2[++t2[0]] = rk[i];
            }
            else
            {
                t1[++t1[0]] = rk[i];
            }
        }
    }
    m2 = l+t1[0]-1;

    for(int i = l; i <= r; i++)
    {
        if(i <= m2)
        {
            rk[i] = t1[i-l+1];
        }
        else
        {
            rk[i] = t2[i-m2];
        }
    }
    solve(ll, m1, l, m2);
    solve(m1+1, rr, m2+1, r);
}
int main()
{

    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++)
    {
        rk[i] = i;
        scanf("%d%d%d%lld", &q[i].type, &q[i].l, &q[i].r, &q[i].c);
        if(q[i].type == 1) q[i].c = (LL)n-q[i].c+1;
        q[i].id = i;
    }
    solve(1, 2*n+1, 1, m);
    for(int i = 1; i <= m; i++)
    {
        if(q[i].type == 2)
        {
           printf("%d\n", n-ans[i]+1);
        }
    }
    return 0;
}