#include <cstdio>  
#include <cstdlib>  
#include <cstring>  
#include <cmath>  
#include <ctime>  
#include <algorithm>  
#include <iostream>  
#include <fstream>  
#include <vector>  
#include <queue>  
#include <deque>  
#include <map>  
#include <set>  
#include <string>  
#define make make_pair  
#define fi first  
#define se second  
  
using namespace std;  
  
typedef long long ll;  
typedef unsigned long long ull;  
typedef pair<int,int> pii;  
  
const int maxn = 100010;  
const int maxm = 1010;  
const int maxs = 26;  
const int inf = 0x3c3c3c3c;  
const int P = 1000000007;  
const double error = 1e-9;  
  
inline int read()  
{  
    int x = 0, f = 1;  
    char ch = getchar();  
    while (ch <= 47 || ch >= 58)  
        f = (ch == 45 ? -1 : 1), ch = getchar();  
    while (ch >= 48 && ch <= 57)  
        x = x * 10 + ch - 48, ch = getchar();  
    return x * f;  
}  
  
struct edge
{  
    int v, w, next;  
} e1[maxn], e2[maxn];  
  
struct node  
{  
    int f, dis, hope;  
};  
  
bool operator < (node a, node b)  
{  
    return a.dis > b.dis || a.dis == b.dis && a.hope < b.hope;  
}  
  
int n, m, cnt1, cnt2, top, head1[maxn], head2[maxn],   
    dis[maxn], u[maxn], v[maxn], vis[maxn], q[maxn],   
    w1[maxn], w2[maxn], ans[maxn], ans1[maxn], ans2[maxn];  
  
void insert(int u, int v, int w)  
{  
    e1[cnt1] = (edge) {v, w, head1[u]}, head1[u] = cnt1++;  
    e2[cnt2] = (edge) {u, w, head2[v]}, head2[v] = cnt2++;  
}  
  
void spfa()  
{  
    memset(dis, 0x3c, sizeof dis);  
    memset(vis, 0, sizeof vis);  
  
    int a = 0, b = 1;  
    dis[n] = 0, q[0] = n;  
  
    while (a != b) {  
        int u = q[a++];  
        vis[u] = 0, a %= maxn;  
  
        for (int i = head2[u]; i != -1; i = e2[i].next) {  
            int v = e2[i].v;  
  
            if (dis[v] > dis[u] + e2[i].w) {  
                dis[v] = dis[u] + e2[i].w;  
                if (!vis[v])  
                    vis[v] = 1, q[b++] = v, b %= maxn;  
            }  
        }  
    }  
      
    if (dis[1] == inf)  
        return;  
      
    priority_queue<node> q;  
  
    q.push((node) {1, 0, dis[1]});  
  
    while (!q.empty() && top != 20) {  
        node u = q.top(); q.pop();  
  
        if (u.f == n)  
            ans[++top] = u.dis;  
          
        for (int i = head1[u.f]; i != -1; i = e1[i].next) {           
            int v = e1[i].v, tmp = u.dis + e1[i].w;  
            q.push((node) {v, tmp, tmp + dis[v]});  
        }  
    }  
}  
  
int main()  
{  
    n = read(), m = read();  
  
    for (int i = 1; i <= m; i++) {  
        u[i] = read(), v[i] = read();  
        w1[i] = read(), w2[i] = read();  
    }  
  
    cnt1 = cnt2 = top =0;  
    memset(head1, -1, sizeof head1);  
    memset(head2, -1, sizeof head2);  
  
    for (int i = 1; i <= m; i++)  
        insert(u[i], v[i], w1[i]);  
  
    spfa();  
  
    for (int i = 1; i <= top; i++)  
        ans1[i] = ans[i];  
  
    cnt1 = cnt2 = top =0;  
    memset(head1, -1, sizeof head1);  
    memset(head2, -1, sizeof head2);  
  
    for (int i = 1; i <= m; i++)  
        insert(u[i], v[i], w2[i]);  
  
    spfa();  
  
    for (int i = 1; i <= top; i++)  
        ans2[i] = ans[i];  
  
    int res = inf;  
  
    for (int i = 1; i <= 20; i++)  
        for (int j = 1; j <= 20; j++)  
            if (ans1[i] == ans2[j] && ans1[i])  
                res = min(res, ans1[i]);  
  
    if (res == inf)  
        printf("IMPOSSIBLE");  
    else  
        printf("%d\n", res);  
          
    return 0;  
}  