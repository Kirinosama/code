#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 110
#define MAXM 110

int a[MAXN][MAXM],sum[MAXN];
int n,m,k,ans1,ans2;

struct node{
	int bg,len;
	bool operator < (node a)const{
		if(len==a.len) return bg<a.bg;
		else return len>a.len;
	}
}v[MAXN];

void solve(int col){
	int len=0;int bg=0;int cnt=0;
	memset(sum,0,sizeof(sum));
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1];
		if(a[i][col]) sum[i]++;
	}
	for(int i=1;i<=n;i++){
		if(a[i][col]==1){
			int ed=min(i+k-1,n);
			v[++cnt]=(node){i,sum[ed]-sum[i-1]};
		}
	}
	sort(v+1,v+1+cnt);
	if(cnt){
		ans1+=v[1].len;
		ans2+=sum[v[1].bg-1];
	}
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d %d",&n,&m,&k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<=m;i++) solve(i);
	cout<<ans1<<' '<<ans2;
	return 0;
}