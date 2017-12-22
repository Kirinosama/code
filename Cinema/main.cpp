#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cmath>

#define P std::pair<int,int>
#define MAXN 2010

P null (-1,-1);
const int INF=INT_MAX;
int n,m,k;
P ld[MAXN][MAXN];
P rd[MAXN][MAXN];
int M[MAXN][MAXN];

bool operator < (const P &a,const P &b)
{
	if(a.first==b.first)
		return a.second<b.second;
	return a.first<b.first;
}

P ld_find(int x,int y,int posx,int posy,int dist)
{
	if(y<1 || x>n)
		return null;
	if(x<1)
		return ld_find(1,x+y-1,posx,posy,dist);
	if(y>m)
		return ld_find(x+y-m,m,posx,posy,dist);
	if(M[x][y]==0)
		return P(x,y);
	else if(ld[x][y]==null)
		return null;
	else if(abs(x-posx)+abs(y-posy)!=dist)
		return ld[x][y];
	else
		return ld[x][y]=ld_find(ld[x][y].first,ld[x][y].second,posx,posy,dist);
}

P rd_find(int x,int y,int posx,int posy,int dist)
{
	if(y>m || x>n)
		return null;
	if(x<1)
		return rd_find(1,y+(1-x),posx,posy,dist);
	if(y<1)
		return rd_find(x+1-y,1,posx,posy,dist);
	if(M[x][y]==0)
		return P(x,y);
	else if(rd[x][y]==null)
		return null;
	else if(abs(x-posx)+abs(y-posy)!=dist)
		return rd[x][y];
	else
		return rd[x][y]=rd_find(rd[x][y].first,rd[x][y].second,posx,posy,dist);
}

bool judge(int x,int y,int dist)
{
	P res(INF,INF);
	P pos[5];
	pos[1]=ld_find(x-dist,y,x,y,dist);
	pos[2]=rd_find(x-dist,y,x,y,dist);
	for(int i=1;i<=2;i++)
	{
		if(pos[i]==null)
			continue;
		if(abs(pos[i].first-x)+abs(pos[i].second-y)!=dist)
			continue;
		if(pos[i]<res)
			res=pos[i];
		if(res!=null && res!=P(INF,INF))
		{
			printf("%d %d\n",res.first,res.second);
			M[res.first][res.second]=1;
			return true;
		}
	}
	pos[3]=rd_find(x,y-dist,x,y,dist);
	pos[4]=ld_find(x,y+dist,x,y,dist);
	for(int i=3;i<=4;i++)
	{
		if(pos[i]==null)
			continue;
		if(abs(pos[i].first-x)+abs(pos[i].second-y)!=dist)
			continue;
		if(pos[i]<res)
			res=pos[i];
	}
	if(res==null)
		return false;
	if(abs(res.first-x)+abs(res.second-y)!=dist)
		return false;
	printf("%d %d\n",res.first,res.second);
	M[res.first][res.second]=1;
	return true;
}

void solve()
{
	int x,y;
	scanf("%d %d",&x,&y);
	if(!M[x][y])
	{
		printf("%d %d\n",x,y);
		M[x][y]=1;
		return;
	}
	for(int i=1;i<=n;i++)
	{
		if(judge(x,y,i))
			return;
	}
}

int main()
{
	freopen("input","r",stdin);	
	//freopen("output","w",stdout);	
	scanf("%d %d %d",&n,&m,&k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			rd[i][j]=P(i+1,j+1);
			ld[i][j]=P(i+1,j-1);
		}
	while(k--)
		solve();
}