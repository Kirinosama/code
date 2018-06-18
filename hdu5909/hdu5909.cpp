#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1010
#define MAXM 2010
typedef long long ll;
const ll MOD=1000000007;
const ll inv=500000004;

int T,n,m;
ll f[MAXN][1050],ans[1050];
int a[MAXN];
int last[MAXN],ne[MAXM],edge_cnt;

struct edge{
	int x,y;
	edge(){}
	edge(int x_,int y_){x=x_,y=y_;};
}E[MAXM];

void add_edge(int x,int y){
	E[++edge_cnt]=edge(x,y);
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void fwt(ll *A,int size,bool flag){
	for(int step=2;step<=size;step<<=1){
		int gap=step>>1;
		for(int i=0;i<size;i+=step){
			for(int j=i;j<i+gap;j++){
				int t0=A[j],t1=A[j+gap];
				if(flag)A[j]=(t0+t1)%MOD,A[j+gap]=(t0-t1+MOD)%MOD;
				else A[j]=((t0+t1)*inv)%MOD,A[j+gap]=((t0-t1+MOD)*inv)%MOD;
			}
		}
	}
}

void dfs(int x,int fa){
	memset(f[x],0,sizeof(f[x]));
	f[x][a[x]]=1;
	fwt(f[x],m,true);
	for(int i=last[x];i;i=ne[i]){
		int y=E[i].y;
		if(y==fa) continue;
		dfs(y,x);
		f[y][0]++;
		fwt(f[y],m,true);
		for(int j=0;j<m;j++)
			f[x][j]=(f[x][j]*f[y][j])%MOD;
	}
	fwt(f[x],m,false);
	for(int i=0;i<m;i++)ans[i]=(ans[i]+f[x][i])%MOD;
}

int main(){
	freopen("input","r",stdin);
	freopen("output","w",stdout);
	cin>>T;
	while(T--){
		cin>>n>>m;edge_cnt=0;
		memset(last,0,sizeof(last));
		memset(ans,0,sizeof(ans));
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=1;i<n;i++){
			int x,y;scanf("%d%d",&x,&y);
			add_edge(x,y);add_edge(y,x);
		}
		dfs(1,1);
		for(int i=0;i<m;i++)printf("%lld ",ans[i]);
		cout<<endl;
	}
	return 0;
}
