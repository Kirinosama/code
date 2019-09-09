#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int n,m,dis[2000];
int q[2000],a[110][30];

int work(int mask,int x){//mask二进制串 x开关的编号 
	int ans=0;
	for(int i=n;i>=1;i--){ //处理从低到高第i位 
		int now=(mask>>(i-1))&1;//now=0或1 表示第i位的值 
		if(now==0 && a[x][i]==-1) now=1;  
		else if(now==1 && a[x][i]==1) now=0;
		ans=ans*2+now; //更新后的now是按下开关之后 第i位的状况 将其加入新的ans 
	}
	return ans;//新的2进制串 
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	int head=1,tail=1;q[1]=(1<<n)-1; //初始状态为1111111111 即10进制下2^n-1 
	memset(dis,0x3f,sizeof(dis)); //初始状态到每个状态的步数设置为无穷大 
	dis[(1<<n)-1]=0;//到自身设置为0 
	while(head<=tail){
		int cur=q[head++];//这次从cur状态走向其他的点 cur是10进制数 2进制下表示灯的亮暗情况 
		if(cur==0)break; //走到了终点 那么break 
		for(int i=1;i<=m;i++){
			int res=work(cur,i);//i是这次尝试的开关编号 res即现状态按下i开关后的新状态 
			if(dis[res]==0x3f3f3f3f){//如果新状态从未到达过则更新并加入队列 
				q[++tail]=res;
				dis[res]=dis[cur]+1;
			}
		}
	}
	if(dis[0]==0x3f3f3f3f) cout<<-1;//如果不能走到0即全灭状态 则输出-1 
	else cout<<dis[0];
	return 0;
}
