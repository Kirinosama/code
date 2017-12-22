#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

 #define rep(i,a,b) for (int i=a; i<=b; i++)
 #define read(x) scanf("%d", &x)
 const int INF=0x3f3f3f3f;

 char st[4][50+5];
 int same, len[4];

 int check(int x, int y) {
    int ret=1;
    if (len[x]>len[y]) swap(x, y);
    while (ret+same<=len[x] && st[x][ret+same]==st[y][ret+same]) ret++;
    return ret-1;
 }

int main()
{
    freopen("bzoj1789.in","r",stdin);
    freopen("out2","w",stdout);
    int ml=INF;
    rep(i,1,3) read(len[i]), ml=min(ml, len[i]), scanf("%s", st[i]+1);
    rep(i,1,ml) 
           if (!((st[1][i]==st[2][i]) && (st[1][i]==st[3][i]))) break; else same=i;
    int d=max(max(check(1, 2), check(1, 3)), check(2, 3));
    int ans=len[1]+len[2]+len[3]-d-3*same;
    printf("%d", ans);
}
