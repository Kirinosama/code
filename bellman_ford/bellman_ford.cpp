#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010
#define MAXM 100010

struct edge{
	int x,y,z;
}E[MAXM];

int n,m,dis[MAXN];

void bellman_ford(){
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0;bool flag;
	for(int i=1;i<n;i++){
		flag=false;
		for(int j=1;j<=m;j++){
			int u=E[j].x,v=E[j].y;
			if(dis[v]>dis[u]+E[j].z){
				dis[v]=dis[u]+E[j].z;
				flag=true;
			}
		}
		if(!flag) break;
	}
	flag=false;
	for(int j=1;j<=m;j++){
		int u=E[j].x,v=E[j].y;
		if(dis[v]>dis[u]+E[j].z){
			dis[v]=dis[u]+E[j].z;
			flag=true;
		}
	}
	if(flag) printf("有负环");
	else printf("%d",dis[n]);
}

int main()
{
    freopen("bellman_ford.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
    	scanf("%d %d %d",&E[i].x,&E[i].y,&E[i].z);
    }
    bellman_ford();
    return 0;
}