#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n,d,a,b,x[160],T;
int edge_cnt,last[160],ne[320];
int pre[160],vis[160],pos[160],f[160];

struct edge{
	int x,y;
}E[320];

void premake(){
	sort(x+1,x+n+1);
	int cnt=0;
	for(int i=1;i<=n;i++)if(x[i]!=x[cnt])
		x[++cnt]=x[i];
	n=cnt;
}

int find(int x){
	for(int i=last[x];i;i=ne[i]){
		if(vis[E[i].y])continue;
		vis[E[i].y]=1;
		if(!pre[E[i].y] || find(pre[E[i].y])){
			pre[E[i].y]=x;
			return 1;
		}
	}
	return 0;
}

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
	E[++edge_cnt]=(edge){y,x};
	ne[edge_cnt]=last[y];
	last[y]=edge_cnt;
}

void solve1(){
	int ans=n;edge_cnt=0;
	memset(pre,0,sizeof(pre));
	memset(last,0,sizeof(last));
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++)if(x[i]-d==x[j]+d)	
			add_edge(i,j);
	}
	int minus=0;
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof(vis));
		if(find(i)) minus++;
	}
	printf("%d\n",(ans-minus/2)*a);
}
 
int solve(int mask){
	for(int i=1;i<=n;i++,mask>>=1){
		int k=mask&1;
		if(!k) pos[i]=x[i]-d;
		else pos[i]=x[i]+d;
	}
	sort(pos+1,pos+n+1);
	int cnt=0;pos[0]=-0x3f3f3f3f;
	for(int i=1;i<=n;i++)if(pos[i]!=pos[cnt])
		pos[++cnt]=pos[i];
	memset(f,0x3f,sizeof(f));f[0]=0;
	for(int i=1;i<=cnt;i++)
		for(int j=0;j<i;j++){
			int l=pos[j+1],r=pos[i];
			f[i]=min(f[i],f[j]+a+b*(r-l));
		}
	return f[cnt];
} 

void solve2(){
	int ans=0x3f3f3f3f;
	for(int i=0;i<(1<<n);i++)
		ans=min(ans,solve(i));
	cout<<ans<<endl;
}

int main(){
	//freopen("point.in","r",stdin);
	cin>>T;
	while(T--){
		cin>>n>>d>>a>>b;
		for(int i=1;i<=n;i++)scanf("%d",&x[i]);
		premake();
		if(a<=b) solve1();
		else solve2();
	}
	return 0;
}
