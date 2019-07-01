#include <bits/stdc++.h>
using namespace std;

#define MAXN 100010
#define MAXM 200010

int n,k,s,ans,book[MAXN];
int edge_cnt,last[MAXN],ne[MAXM];

struct edge{
	int x,y;
}E[MAXM];

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

void dfs(int x){
	if(book[x]) return;
	book[x]=1,ans++;
	for(int i=last[x];i;i=ne[i])if(!book[E[i].y])
		dfs(E[i].y);
}

int main(){
	//freopen("input","r",stdin);
	cin>>n>>k>>s;
	for(int i=1;i<n;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		if(z>=k) add_edge(x,y),add_edge(y,x);
	}
	dfs(s);cout<<ans-1;
	return 0;
}
