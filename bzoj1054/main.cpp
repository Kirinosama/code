#include <cstdlib>
#include <cstdio>
#include <queue>
#include <iostream>
using namespace std;

struct Map
{
	char p[5][5];
	int t;
};

queue <Map> Q;

int ok,end;
bool book[2400000];
char a[5][5],b[5][5];
int go[4][2]={{0,-1},{0,1},{-1,0},{1,0}};

int HASH(char s[][])
{
	int res=0;
	int MOD=2333233;
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
			res=(res*11+(s[i][j]-'0'))%MOD;
	return res;
}

void solve(Map g)
{
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
		{
			if(g.p[i][j]=='0') continue;
			for(int k=0;k<=3;k++)
			{
				int ti=i+go[k][0];
				int tj=j+go[k][1];
				if(ti<1 || ti>4 || tj<1 || tj>4)
					continue;
				swap(g.p[i][j],g.p[ti][tj]);
				if(!book[HASH(g.p)])
				{
					Q.push(g.p,g.t+1);
					book[HASH(g.p)]=true;
					if(HASH(g.p)==end)
					{
						printf("%d",g.t+1);
						ok=1;
						return;
					}
				}
			} 
		}
	Q.pop_front();
}

void bfs()
{
	end=HASH(b);
	Q.push(Map{a,0});
	book[HASH(a)]=true;
	while(!Q.empty() && !ok)
		solve(Q.front());
}

int main()
{
	freopen("input","r",stdin);
	for(int i=1;i<=4;i++)
	{
		for(int j=1;j<=4;j++)
			scanf("%c",&a[i][j]);
		scanf("\n");
	}
	scanf("\n");
	for(int i=1;i<=4;i++)
	{
		for(int j=1;j<=4;j++)
			scanf("%c",&b[i][j]);
		scanf("\n");
	}
	bfs();
	return 0;
}