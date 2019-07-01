#include <bits/stdc++.h>
using namespace std;

struct ob{
	int x,y,z;
	void in(){scanf("%d%d%d",&x,&y,&z);}
	bool operator < (const ob &p)const{return z>p.z;}
}c[260];

int go[4][2]={{0,1},{0,-1},{-1,0},{1,0}};
int n,m,k,ans;
bool flag[1010][1010],book[1010][1010];

bool judge(int x,int y){
	for(int i=1;i<=k;i++)
		if(abs(x-c[i].x)+abs(y-c[i].y)+1<=c[i].z)
			return true;
	return false;
}

int bfs(int x,int y){
	int cur=0,tx,ty;
	if(book[x][y] || flag[x][y]) return 0;
	book[x][y]=true;
	for(int i=0;i<4;i++){
		tx=x+go[i][0];
		ty=y+go[i][1];
		if(tx<1 || tx>n || ty<1 || ty>m) continue;
		cur+=bfs(tx,ty);
	}
	return 1+cur;
}

int main(){
	freopen("input","r",stdin);
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++)c[i].in();
	sort(c+1,c+k+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			flag[i][j]=judge(i,j);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)if((!book[i][j]) && (!flag[i][j]))
			ans=max(ans,bfs(i,j));
	cout<<ans;
	return 0;
}
