#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#define inf 10000000
#define ll long long
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int head=0,tail=1;
int n,m,ex,ey;
int x[10005],y[10005];
int xx[8]={1,1,-1,-1,2,2,-2,-2},yy[8]={2,-2,2,-2,1,-1,1,-1};
int a[55][55],add[55][55],dis[55][55];
ll f[55][35];
bool inq[55][55];
void bfs()
{
	while(head!=tail)
	{
		int nx=x[head],ny=y[head];head++;
		for(int k=0;k<8;k++)
		{
			int tx=nx+xx[k],ty=ny+yy[k];
			if(tx<1||ty<1||tx>n||ty>m||a[tx][ty]==2)continue;
			int ta=add[nx][ny]+(a[tx][ty]==0);
			if(ta<add[tx][ty])
			{
				add[tx][ty]=ta;
				dis[tx][ty]=dis[nx][ny]+1;
				f[tx][ty]=f[nx][ny];
				if(inq[tx][ty])continue;
				inq[tx][ty]=1;x[tail]=tx;y[tail]=ty;tail++;
			}
			else if(ta==add[tx][ty])
			{
				if(dis[nx][ny]+1<dis[tx][ty])
				{
					dis[tx][ty]=dis[nx][ny]+1;
					f[tx][ty]=f[nx][ny];
					if(inq[tx][ty])continue;
					inq[tx][ty]=1;x[tail]=tx;y[tail]=ty;tail++;
				}
				else if(dis[nx][ny]+1==dis[tx][ty])
				{
					f[tx][ty]+=f[nx][ny];
					if(inq[tx][ty])continue;
					inq[tx][ty]=1;x[tail]=tx;y[tail]=ty;tail++;
				}
			}
		}
		inq[nx][ny]=0;
	}
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			a[i][j]=read();
			add[i][j]=dis[i][j]=inf;
			if(a[i][j]==3)
			{
				inq[i][j]=1;
				x[0]=i;y[0]=j;add[i][j]=dis[i][j]=0;f[i][j]=1;
			}
			else if(a[i][j]==4)ex=i,ey=j;
		}
	bfs();
	if(add[ex][ey]==inf)puts("-1");
	else 
	{
		printf("%d\n%d\n%lld\n",add[ex][ey],dis[ex][ey],f[ex][ey]);
	}
	return 0;
}
