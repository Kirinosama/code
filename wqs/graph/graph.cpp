#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010
#define MAXM 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y,z;
}E[MAXM];

int last[MAXN],ne[MAXM],edge_cnt;
int n,m,a[MAXN],fa[MAXN];

void add(int x,int y,int z){
	E[++edge_cnt]=(edge){x,y,z};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}

void merge(int x,int y){
	fa[find(x)]=find(y);
}

double solve(int mask){
	int ch[MAXN]={0},cnt=0,from=0,ans=0;
	for(int i=1;i<=n;i++){
		if(mask&1) ans+=a[i],ch[i]=1,fa[i]=i,cnt++;
		mask>>=1;
	}
	if(cnt<2) return 0.00;
	int sum=0;
	for(int i=1;i<=edge_cnt;i+=2)if(ch[E[i].x] && ch[E[i].y])
		if(find(E[i].x)!=find(E[i].y))
			merge(E[i].x,E[i].y);
	for(int i=1;i<=n;i++)if(ch[i]){
		if(!from) from=find(i);
		if(find(i)!=from) return 0.00;
	}
	for(int i=1;i<=n;i++)if(ch[i])
		for(int j=last[i];j;j=ne[j])if(ch[E[j].y])
			sum+=E[j].z;
	return (double)ans*2.0/(double)sum;
}

int main(){
    freopen("graph.in","r",stdin);
    freopen("graph.out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),fa[i]=i;
    for(int i=1;i<=m;i++){
    	int x,y,z;
    	scanf("%d %d %d",&x,&y,&z);
    	add(x,y,z);add(y,x,z);
    }
    double ans=0.00;
    for(int i=0;i<(1<<n);i++)
    	ans=max(ans,solve(i));
    printf("%.2lf",ans);
    return 0;
}