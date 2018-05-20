#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 410
#define MAXM 160010

struct edge{
	int x,y,z;
}E[MAXM];

struct point{
	int x,y;
	int dis(const point &a)const{
		return (x-a.x)*(x-a.x)+(y-a.y)*(y-a.y);
	}
}p[MAXN];

int n,edge_cnt,c[MAXN],fa[MAXN],maxdis[MAXN];

bool cmp1(const edge &a,const edge &b){
	return a.z<b.z;
}

int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
	
void kruskal(){
	int cnt=0;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=edge_cnt && cnt<n-1;i++){
		if(find(E[i].x)!=find(E[i].y)){
			fa[find(E[i].x)]=find(E[i].y);
			printf("%d %d\n",E[i].x,E[i].y);
		}
	}
}

int main(){
	//freopen("T3.in","r",stdin);
	while(1){
		cin>>n;if(!n)break;
		edge_cnt=0;
		for(int i=1;i<=n;i++)scanf("%d%d",&p[i].x,&p[i].y);
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				E[++edge_cnt]=(edge){i,j,p[i].dis(p[j])};
		sort(E+1,E+edge_cnt+1,cmp1);
		kruskal();
	}
	return 0;
}
