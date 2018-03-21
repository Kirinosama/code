#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 100010
#define MAXM 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y,z;
}E[MAXM];

int last[MAXN],ne[MAXM],t[MAXN],cnt;
int n,m,edge_cnt,in[MAXN],out[MAXN];
double f[MAXN];

void topo_sort(){
	queue <int> Q;
	for(int i=1;i<=n;i++)if(!in[i])
		Q.push(i);
	while(!Q.empty()){
		int tp=Q.front();Q.pop();
		t[++cnt]=tp;
		for(int i=last[tp];i;i=ne[i]){
			in[E[i].y]--;
			if(in[E[i].y]==0)Q.push(E[i].y);
		}
	}
}

void solve(int x){
	if(!out[x]) f[x]=0;
	else{
		double mul=1.0/(double)out[x];
		for(int i=last[x];i;i=ne[i]){
			int y=E[i].y;
			f[x]+=mul*((double)E[i].z+f[y]);
		}
	}
}

int main(){
    freopen("bzoj3036.in","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
    	static int x,y,z;
    	scanf("%d%d%d",&x,&y,&z);
    	E[++edge_cnt]=(edge){x,y,z};in[y]++,out[x]++;
    	ne[edge_cnt]=last[x];
    	last[x]=edge_cnt;
    }
    topo_sort();
    for(int i=n;i>=1;i--)solve(t[i]);
    printf("%.2f",f[1]);
    return 0;
}