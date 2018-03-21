#include <set>
#include <cstdio>
#define N 10010
using namespace std;
set<int> s;
int m , a[N] , head[N] , to[N << 1] , len[N << 1] , ne[N << 1] , cnt , si[N] , mx[N] , sum , root , deep[N] , vis[N] , d[N] , tot;
bool ans[N];
void add(int x , int y , int z)
{
    to[++cnt] = y , len[cnt] = z , ne[cnt] = head[x] , head[x] = cnt;
}
void getroot(int x , int fa)
{
    int i;
    si[x] = 1 , mx[x] = 0;
    for(i = head[x] ; i ; i = ne[i])
        if(!vis[to[i]] && to[i] != fa)
            getroot(to[i] , x) , si[x] += si[to[i]] , mx[x] = max(mx[x] , si[to[i]]);
    mx[x] = max(mx[x] , sum - si[x]);
    if(mx[x] < mx[root]) root = x;
}
void dfs(int x , int fa)
{
    int i;
    si[x] = 1 , d[++tot] = deep[x];
    for(i = head[x] ; i ; i = ne[i])
        if(!vis[to[i]] && to[i] != fa)
            deep[to[i]] = deep[x] + len[i] , dfs(to[i] , x) , si[x] += si[to[i]];
}
void solve(int x)
{
    int i , j , k;
    vis[x] = 1 , s.clear() , s.insert(0);
    for(i = head[x] ; i ; i = ne[i])
    {
        if(!vis[to[i]])
        {
            tot = 0 , deep[to[i]] = len[i] , dfs(to[i] , 0);
            for(j = 1 ; j <= tot ; j ++ )
                for(k = 1 ; k <= m ; k ++ )
                    if(s.find(a[k] - d[j]) != s.end())
                        ans[k] = 1;
            for(j = 1 ; j <= tot ; j ++ ) s.insert(d[j]);
        }
    }
    for(i = head[x] ; i ; i = ne[i])
        if(!vis[to[i]])
            sum = si[to[i]] , root = 0 , getroot(to[i] , 0) , solve(root);
}
int main()
{
    int n , i , x , y , z;
    scanf("%d%d" , &n , &m);
    for(i = 1 ; i < n ; i ++ ) scanf("%d%d%d" , &x , &y , &z) , add(x , y , z) , add(y , x , z);
    for(i = 1 ; i <= m ; i ++ )
    {
        scanf("%d" , &a[i]);
        if(!a[i]) ans[i] = 1;
    }
    mx[0] = 1 << 30 , sum = n , getroot(1 , 0) , solve(root);
    for(i = 1 ; i <= m ; i ++ ) printf("%s\n" , ans[i] ? "Yes" : "No");
    return 0;
}