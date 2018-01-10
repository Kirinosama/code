#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 510
#define eps 1e-9
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct point{
	double x,y;
}a[MAXN],b[MAXN];

int n,m,dis[MAXN][MAXN],ans;
double x,y,z;

bool isonleft(point &a,point &b,point &c){
	double mul=(b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
	if(mul>0) return true;
	else if(mul>-eps && (c.x-a.x)*(c.x-b.x)+(c.y-a.y)*(c.y-b.y)<eps) return true;
	return false;
}

int main(){
    freopen("bzoj1027.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    	scanf("%lf %lf %lf",&x,&y,&z);
    	a[i]=(point){x,y};
    }
    for(int i=1;i<=m;i++){
    	scanf("%lf %lf %lf",&x,&y,&z);
    	b[i]=(point){x,y};
    }
    if(m==1){
    	for(int i=1;i<=n;i++)
    		if(a[i].x==b[1].x && a[i].y==b[1].y)
    			return printf("1"),0;
    	printf("-1");return 0;
    }
    memset(dis,0x3f,sizeof(dis));
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=n;j++){
    		if(i==j) continue;
    		bool flag=true;
    		for(int k=1;k<=m;k++)
    			if(!isonleft(a[i],a[j],b[k]))
    				flag=false;
    		if(flag) dis[i][j]=1;
    	}
    ans=INF;
    for(int k=1;k<=n;k++)
    	for(int i=1;i<=n;i++){
    		if(dis[i][k]==INF) continue;
    		for(int j=1;j<=n;j++)
    			dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
    	}
    for(int i=1;i<=n;i++)
    	ans=min(ans,dis[i][i]);
    printf("%d",ans==INF?-1:ans);
    return 0;
}