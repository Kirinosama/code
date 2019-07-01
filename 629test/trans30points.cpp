#include <bits/stdc++.h>
using namespace std;

#define maxn 1000010
#define maxm 2000010

struct edge{
	int x,y,p,q;
}e[maxm];

int n,m,s,t;
int last[maxn],ne[maxm],edge_cnt;
int pre[maxn],dis[maxn];

void add_edge(int x,int y,int p,int q){
	e[++edge_cnt]=(edge){x,y,p,q};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

int find(int beg,int p,int q){
/*	if(!beg) return 0;
	if(beg<p) return beg;
	int k=beg/(p+q)*(p+q);
	if(k+p-q-1>=beg) return beg;
	else return k+p+q;
*/
	if(beg%(p+q)<p) return beg;
	return (beg/(p+q)+1)*(p+q);

}

int main(){
	//freopen("1.in","r",stdin);
	cin>>n>>m>>s>>t;
	for(int i=1;i<=m;i++){
		int x,y,p,q;
		scanf("%d%d%d%d",&x,&y,&p,&q);
		add_edge(x,y,p,q);add_edge(y,x,p,q);
	}
	memset(dis,0x3f,sizeof(dis));dis[s]=0;
	queue<int>q;q.push(s);
	while(!q.empty()){
		int cur=q.front();q.pop();
		for(int i=last[cur];i;i=ne[i]){
			int to=e[i].y,st=find(dis[cur],e[i].p,e[i].q);
			if(dis[to]>st+1){
				dis[to]=st+1;
				pre[to]=cur;
				q.push(to);
			}
		}
	}
	cout<<dis[t]<<endl;	
	return 0;
}

