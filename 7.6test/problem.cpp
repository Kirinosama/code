#include <bits/stdc++.h>
using namespace std;

int n,m,k,T;
int go[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
int Max[110][110];

struct cong{
	int x,y,d,f,flag;
	void in(){scanf("%d%d%d%d",&x,&y,&d,&f);flag=0;}
	void mv(){
		int tx=x+go[d][0];
		int ty=y+go[d][1];
		if(tx>n || tx<1 || ty>m || ty<1) d^=1;
		else x=tx,y=ty;
		Max[x][y]=max(Max[x][y],f);
	}
}c[1010];

int main(){
	freopen("input","r",stdin);
	freopen("output","w",stdout);
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++)c[i].in();
	cin>>T;
	while(T--){
		memset(Max,0,sizeof(Max));
		for(int i=1;i<=k;i++)if(!c[i].flag)
			c[i].mv();
		for(int i=1;i<=k;i++)if(!c[i].flag)
			if(c[i].f!=Max[c[i].x][c[i].y])
				c[i].flag=1;
	}
	for(int i=1;i<=k;i++)printf("%d %d\n",c[i].x,c[i].y);
	return 0;
}
