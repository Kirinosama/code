#include<iostream>

#include<cstdio>

#define maxn 100009

using namespace std;

int a[maxn],b[maxn],suma[maxn],sumb[maxn];

int dp[2000][2000];

void dfs(int k,int state,int *a,int s,int *ans)

{

    if(k==a[0]+1)return ;

    ans[state<<(a[0]-k)]=s;

    dfs(k+1,state*2+1,a,s+a[k+1],ans);

    dfs(k+1,state*2,a,s,ans);

}

int main()
{

    scanf("%d",&a[0]);

    for(int i=1;i<=a[0];i++)scanf("%d",&a[i]);

    scanf("%d",&b[0]);

    for(int i=1;i<=b[0];i++)scanf("%d",&b[i]);

    dfs(0,0,a,0,suma);

    dfs(0,0,b,0,sumb);

    for(int i=1;i<=(1<<a[0])-1;i++)

        for(int j=1;j<=(1<<b[0])-1;j++)

        {

            for(int k=1;k<=a[0];k++)

            {

                int u=1<<(k-1);

                if((i&u)>0)dp[i][j]=max(dp[i][j],dp[i-u][j]);

            }

            for(int k=1;k<=b[0];k++)

            {

                int u=1<<(k-1);

                if((j&u)>0)dp[i][j]=max(dp[i][j],dp[i][j-u]);

            }

            if(suma[i]==sumb[j])dp[i][j]++;

        }

    printf("%d\n",a[0]+b[0]-2*dp[(1<<(a[0]))-1][(1<<(b[0]))-1]);

    return 0;

}