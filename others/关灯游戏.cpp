#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int n,m,dis[2000];
int q[2000],a[110][30];

int work(int mask,int x){//mask二进制串 x开关的编号 
	int ans=0;
	for(int i=n;i>=1;i--){
		int now=(mask>>(i-1))&1;
		if(now==0 && a[x][i]==-1) now=1;
		else if(now==1 && a[x][i]==1) now=0;
		ans=ans*2+now;
	}
	return ans;//新的2进制串 
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	int head=1,tail=1;q[1]=(1<<n)-1;
	memset(dis,0x3f,sizeof(dis));
	dis[(1<<n)-1]=0;
	while(head<=tail){
		int cur=q[head++];
		if(cur==0)break; 
		for(int i=1;i<=m;i++){
			int res=work(cur,i);
			if(dis[res]==0x3f3f3f3f){
				q[++tail]=res;
				dis[res]=dis[cur]+1;
			}
		}
	}
	if(dis[0]==0x3f3f3f3f) cout<<-1;
	else cout<<dis[0];
	return 0;
}
