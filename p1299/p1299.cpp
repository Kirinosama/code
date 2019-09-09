#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

struct Q
{
	int x,y;
}que[5000000];

int n;
int xs,ys,xe,ye;
int a[2005][2005];
int book[2005][2005],bo[2005][2005];
int head,tail;
int dir[16][2]={{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};
void bfs(int x,int y)
{
	while(head!=tail)
	{
		if(a[que[head].x][que[head].y+1]==1 && book[que[head].x][que[head].y+1]==0)
		{
			book[que[head].x][que[head].y+1]=1;
			que[tail].x=que[head].x;
			que[tail++].y=que[head].y+1;
		}
		if(a[que[head].x][que[head].y-1]==1 && book[que[head].x][que[head].y-1]==0)
		{
			book[que[head].x][que[head].y-1]=1;
			que[tail].x=que[head].x;
			que[tail++].y=que[head].y-1;
		}
		if(a[que[head].x+1][que[head].y]==1 && book[que[head].x+1][que[head].y]==0)
		{
			book[que[head].x+1][que[head].y]=1;
			que[tail].x=que[head].x+1;
			que[tail++].y=que[head].y;
		}
		if(a[que[head].x-1][que[head].y]==1 && book[que[head].x-1][que[head].y]==0)
		{
			book[que[head].x-1][que[head].y]=1;
			que[tail].x=que[head].x-1;
			que[tail++].y=que[head].y;
		}
		head++;
	}
}

int main()
{
	cin >> n;
	for(int i=1;i<=n;i++)
	{
		cin >> xs >> ys >> xe >> ye;
		if(xs<=xe && ys<=ye) 
		{
			for(int j=xs+1001;j<=xe+1001;j++)
			{
				for(int k=ys+1001;k<=ye+1001;k++)
				{
					a[j][k]=1;
				}
			}
		}
		else if(xs<=xe && ys>ye) 
		{
			for(int j=xs+1001;j<=xe+1001;j++)
			{
				for(int k=ye+1001;k<=ys+1001;k++)
				{
					a[j][k]=1;
				}
			}
		}
		else if(xs>xe && ys<=ye) 
		{
			for(int j=xe+1001;j<=xs+1001;j++)
			{
				for(int k=ys+1001;k<=ye+1001;k++)
				{
					a[j][k]=1;
				}
			}
		}
		else if(xs>xe && ys>ye) 
		{
			for(int j=xe+1001;j<=xs+1001;j++)
			{
				for(int k=ye+1001;k<=ys+1001;k++)
				{
					a[j][k]=1;
				}
			}
		}
	}
	for(int i=1;i<=2001;i++)
	{
		for(int j=1;j<=2001;j++)
		{
			if(a[i][j+1]==0 && a[i][j-1]==0 && a[i][j]==1)
				a[i][j]=0;
			if(a[i+1][j]==0 && a[i-1][j]==0 && a[i][j]==1)
				a[i][j]=0;
		}
	}

	int an=0;
	for(int i=1;i<=2001;i++)
	{
		for(int j=1;j<=2001;j++)
		{
			if(a[i][j]==1)
			{
				for(int k=0;k<=15;k++)
				{
					if(a[i+dir[k][0]][j+dir[k][1]])
						an++;
					else
						an=0;
					if(an==3)
						break;
				}
			}
			if(an>=3)
			{
				if(a[i+1][j+1]==0 && a[i-1][j-1]==0 && a[i+1][j-1]==1 && a[i-1][j+1]==1)
					bo[i][j]=1;
				else if(a[i+1][j-1]==0 && a[i-1][j+1]==0 && a[i+1][j+1]==1 && a[i-1][j-1]==1)
					bo[i][j]=1;
			}
			else
			{
				a[i][j]=0;
			}
			an=0;
		}
	}
	
	for(int i=1;i<=2001;i++)
	{
		for(int j=1;j<=2001;j++)
		{
			if(bo[i][j]==1)
				a[i][j]=0;
		}
	}

	int ans=0;
	for(int i=1;i<=2001;i++)
	{
		for(int j=1;j<=2001;j++)
		{
			if(a[i][j]==1 && book[i][j]==0)
			{
				book[i][j]=1;
				head=1;
				tail=2;
				ans++;
				que[head].x=i;
				que[head].y=j;
				bfs(i,j);
			}
		}
	}
	cout << ans;
	return 0;
}
