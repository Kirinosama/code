#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1010

struct point{
	int x,y,v;
}p[MAXN];

int n,m,sum[MAXN],w[MAXN][MAXN];
int f[2][MAXN][MAXN];

bool cmp(const point &a,const point &b){
	if(a.x==b.x) return a.y<b.y;
	return a.x<b.x;
}

void solve(){
	int ans=0;
	memset(f,0xef,sizeof(f));
	for(int i=1;i<=n;i++){
		ans+=p[i].y;
		f[0][i][i]=f[1][i][i]=-1*abs(m-p[i].x)*sum[n];
	}
	for(int i=1;i<=n-1;i++)
		for(int s=1;s<=n-i;s++){
			int t=s+i;
			f[0][s][t]=max(f[0][s][t],f[0][s+1][t]-(p[s+1].x-p[s].x)*w[s+1][t]);
			f[0][s][t]=max(f[0][s][t],f[1][s+1][t]-(p[t].x-p[s].x)*w[s+1][t]);
			f[1][s][t]=max(f[1][s][t],f[0][s][t-1]-(p[t].x-p[s].x)*w[s][t-1]);
			f[1][s][t]=max(f[1][s][t],f[1][s][t-1]-(p[t].x-p[t-1].x)*w[s][t-1]);
		}
	printf("%.3f",0.001*double(max(f[0][1][n],f[1][1][n])+ans));
}

int main(){
	freopen("input","r",stdin);
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&p[i].x);
	for(int i=1;i<=n;i++)
		scanf("%d",&p[i].y);
	for(int i=1;i<=n;i++)
		scanf("%d",&p[i].v);
	sort(p+1,p+1+n,cmp);
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+p[i].v;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			w[i][j]=sum[n]-(sum[j]-sum[i-1]);
	solve();
}