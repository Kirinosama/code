#include <bits/stdc++.h>
using namespace std;
int x[155],p[155],f[21],a,b,n,d;
int dp[155][155],minn[455][155],ml[155][155];
bool tag[155];
int main (){
	freopen ("point.in","r",stdin);
	freopen ("point.out","w",stdout);
	int i,j,k,d,ans=1000000000;
	scanf ("%d%d%d%d",&n,&d,&a,&b);
	for (i=1;i<=n;i++)
	{scanf ("%d",&x[i]);x[i]+=d;}
	sort(x+1,x+n+1);
	n=unique(x+1,x+n+1)-x-1;
	if (n<=20)
	{for (i=0;i<(1<<n);i++)
	{for (j=1;j<=n;j++)
	{if (i&(1<<(j-1))) {p[j]=x[j]-d;}
	else {p[j]=x[j]+d;}
	}
	sort(p+1,p+n+1);
	for (j=1;j<=n;j++) f[j]=1000000000;
	for (j=1;j<=n;j++)
	{for (k=1;k<=j;k++)
	{f[j]=min(f[j],f[k-1]+(p[j]-p[k])*b+a);}
	}
	if (f[n]<ans) ans=f[n];
	}
	printf ("%d\n",ans);
	return 0;
	}
	if (a<=b)
	{ans=n;
	for (i=1;i<=n;i++)
	{if (tag[i]) continue;
	for (j=i+1;j<=n;j++)
	{if (x[j]==x[i]+2*d)
	{tag[i]=tag[j]=1;ans--;break;}
	}
	}
	printf ("%d\n",ans*a);
	return 0;
	}
	for (i=0;i<=x[1]+d;i++)
	{for (j=1;j<=n;j++)
	{if (x[j]-d>=i) {minn[i][j]=x[j]-d;}
	else {minn[i][j]=x[j]+d;}
	}
	}
	for (i=1;i<=n;i++)
	{for (j=i+1;j<=n;j++)
	{ml[i][j]=1000000000;}
	}
	for (i=0;i<=x[1]+d;i++)
	{for (j=1;j<=n;j++)
	{int maxn=minn[i][j];
	for (k=j;k<=n;k++)
	{maxn=max(maxn,minn[i][k]);
	ml[j][k]=min(ml[j][k],maxn-i);
	}
	}
	}
	for (i=1;i<=n;i++)
	{for (j=i;j<=n;j++)
	{dp[i][j]=ml[i][j]*b+a;}
	}
	for (d=2;d<=n;d++)
	{for (i=1;i+d-1<=n;i++)
	{j=i+d-1;
	for (k=i;k<j;k++)
	{dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);}
	}
	}
	printf ("%d\n",dp[1][n]);
	return 0;
}
	
