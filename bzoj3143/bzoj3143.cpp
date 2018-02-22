#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 510
#define MAXM 500010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y;
	double val;
}E[MAXM];

int last[MAXN],ne[MAXM],edge_cnt;
int n,m,d[MAXN];
double a[MAXN][MAXN],f[MAXN],ans;

inline int read(){
	int x=0,w=0;char ch;
	while(ch<'0' || ch>'9') w|=(ch=='-'),ch=getchar();
	while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return w?-x:x;
}

bool cmp(const edge &a,const edge &b){
	return a.val>b.val;
}

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y,0.0};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void swap_line(int x,int y){
	for(int i=1;i<=n+1;i++)swap(a[x][i],a[y][i]);
}

int main(){
    freopen("bzoj3143.in","r",stdin);
   	n=read(),m=read();
    for(int i=1;i<=m;i++){
    	int x=read(),y=read();
    	add_edge(x,y),add_edge(y,x);
 		d[x]++,d[y]++;
    }
    a[n][n]=1.0;a[n][n+1]=1.0;a[1][n+1]=1.0;
    for(int i=1;i<n;i++){
    	a[i][i]=1.0;
    	for(int j=last[i];j;j=ne[j]){
    		int y=E[j].y;a[i][y]=-1.0/(double)d[i];
    	}
    }
    for(int i=1;i<=n;i++){
    	if(!a[i][i]){
    		for(int j=i+1;j<=n;j++)if(a[j][i]){
    			swap_line(i,j);break;
    		}
    	}
    	for(int j=i+1;j<=n;j++){
    		double mul=a[j][i]/a[i][i];
    		for(int k=i;k<=n+1;k++) a[j][k]-=a[i][k]*mul;
    	}
    }
    for(int i=n;i>=1;i--){
    	f[i]=a[i][n+1]/a[i][i];
    	for(int j=i-1;j>=1;j--)a[j][n+1]-=a[j][i]*f[i];
    }
	for(int i=1;i<=edge_cnt;i+=2){
		E[i].val=f[E[i].x]/(double)d[E[i].x]+f[E[i].y]/(double)d[E[i].y];
	}
	sort(E+1,E+edge_cnt+1,cmp);
	for(int i=1;i<=m;i++){
		printf("%d %d %.3f\n",E[i].x,E[i].y,E[i].val);
	}
	for(int i=1;i<=m;i++) ans+=(double)i*E[i].val;
	printf("%.3f",ans);
    return 0;
}