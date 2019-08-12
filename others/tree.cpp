#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

struct edge{
	int to,w;
}E[100010];

int pre[100010],last[100010],cnt,n;

void add_edge(int x,int y,int z){
	cnt++;
	E[cnt].to=y;
	E[cnt].w=z;
	pre[cnt]=last[x];
	last[x]=cnt;
}

int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int x,y,z; //边的两个端点和边的权值
		scanf("%d%d%d",&x,&y,&z);
		add_edge(x,y,z);
		add_edge(y,x,z);
		
	}
	return 0;
}
