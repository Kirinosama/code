#include <bits/stdc++.h>
using namespace std;
#define N 1100
int T,n;
int a[N],l[N][N],r[N][N];
int main()
{
    ///freopen("tt.in","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        if(n==1){puts("1");continue;}
        for(int i=1;i<=n;i++)
            l[i][i]=r[i][i]=a[i];
        for(int i=1;i<=n;i++)
            for(int j=1;j+i<=n;j++)
            {
                int x=l[j][j+i-1],y=r[j][j+i-1],z=a[j+i];
                if(y==z)l[j][j+i]=0;
                else if(x>z&&y>z)l[j][j+i]=z;
                else if(x<=z&&y>z)l[j][j+i]=z+1;
                else if(x>z&&y<z)l[j][j+i]=z-1;
                else l[j][j+i]=z;

                x=r[j+1][j+i],y=l[j+1][j+i],z=a[j];
                if(y==z)r[j][j+i]=0;
                else if(x>z&&y>z)r[j][j+i]=z;
                else if(x<=z&&y>z)r[j][j+i]=z+1;
                else if(x>z&&y<z)r[j][j+i]=z-1;
                else r[j][j+i]=z;
            }
        puts(l[2][n]==a[1] ? "0":"1");
    }
    return 0;
}