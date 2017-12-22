#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,k,dis[310][310];

int main(){
    freopen("bzoj1641.in","r",stdin);
    scanf("%d %d %d",&n,&m,&k);
    memset(dis,0x3f,sizeof(dis));
    for(int i=1;i<=m;i++){
    	static int x,y,z;
    	scanf("%d %d %d",&x,&y,&z);
    	dis[x][y]=min(dis[x][y],z);
    }
    for(int p=1;p<=n;p++)
    	for(int i=1;i<=n;i++)
    		for(int j=1;j<=n;j++)
    			dis[i][j]=min(dis[i][j],max(dis[i][p],dis[p][j]));
    for(int i=1;i<=k;i++){
    	static int x,y,z;
    	scanf("%d %d",&x,&y);
    	printf("%d\n",dis[x][y]==0x3f3f3f3f?-1:dis[x][y]);
    }
    return 0;
}