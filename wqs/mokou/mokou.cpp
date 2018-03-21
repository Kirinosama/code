#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 40010
#define MAXM 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y;
	double z;
	bool operator < (const edge &a)const{
		return z<a.z;
	}
}p[MAXM],E[MAXM*2];

int n,m,rt,fa[MAXN];
int ne[MAXM],last[MAXN],edge_cnt;
double tot,ans,size[MAXN];

int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}

void add_edge(int x,int y,double z){
	E[++edge_cnt]=(edge){x,y,z};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void kruskal(){
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)if(find(p[i].x)!=find(p[i].y)){
		add_edge(p[i].x,p[i].y,p[i].z);
		add_edge(p[i].y,p[i].x,p[i].z);
		tot+=p[i].z;
		fa[find(p[i].x)]=find(p[i].y);
	}
}

void dfs(int x,int f){
	double res=0;
	int part=(f>0);
	for(int i=last[x];i;i=ne[i])if(E[i].y!=f){
		dfs(E[i].y,x);size[x]+=size[E[i].y]+E[i].z;
		part++;
	}
	if(part<=1) return;
	double avg=tot/(double)part;
	for(int i=last[x];i;i=ne[i])if(E[i].y!=f){
		res+=(size[E[i].y]+E[i].z-avg)*(size[E[i].y]+E[i].z-avg);
	}
	if(f) res+=(tot-size[x]-avg)*(tot-size[x]-avg);
	if(res<ans) rt=x,ans=res;
}

int main(){
    freopen("mokou.in","r",stdin);
    freopen("mokou.out","w",stdout);
    cin>>n>>m;ans=INF;
    for(int i=1;i<=m;i++)scanf("%d%d%lf",&p[i].x,&p[i].y,&p[i].z);
    sort(p+1,p+m+1);
	kruskal();
	dfs(1,0);
	cout<<rt;
    return 0;
}