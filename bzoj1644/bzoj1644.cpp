#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,sx,sy,ex,ey,book[110][110][4];
int go[4][2]={{0,1},{0,-1},{-1,0},{1,0}};
char a[110][110];

bool judge(int x,int y){
	if(x<1 || x>n || y<1 || y>n) return false;
	return a[x][y]!='x';
}

struct data{
	int x,y,func,w;
};

queue <data> Q; 

int main(){
    freopen("bzoj1644.in","r",stdin);
    scanf("%d\n",&n);
    for(int i=1;i<=n;i++){
    	for(int j=1;j<=n;j++){
    		scanf("%c",&a[i][j]);
    		if(a[i][j]=='A') sx=i,sy=j;
    		if(a[i][j]=='B') ex=i,ey=j;
    	}
    	scanf("\n");
    }
    for(int i=0;i<4;i++)
    	for(int j=1;j<=n;j++){
    		int tx=sx+go[i][0]*j,ty=sy+go[i][1]*j;
    		if(!judge(tx,ty))
    			break;
    		Q.push((data){tx,ty,i,0});
    		book[tx][ty][i]=1;
    	}
    while(!Q.empty()){
    	data cur=Q.front();Q.pop();
    	if(cur.x==ex && cur.y==ey){
    		printf("%d",cur.w);
    		break;
    	}
    	for(int i=0;i<4;i++){
    		if(i==cur.func) continue;
    		for(int j=1;j<=n;j++){
    			int tx=cur.x+go[i][0]*j,ty=cur.y+go[i][1]*j;
    			if(!judge(tx,ty)) break;
    			if(book[tx][ty][i]) continue;
    			book[tx][ty][i]=1;
    			Q.push((data){tx,ty,i,cur.w+1});
    		}
   		}
    }
    return 0;
}