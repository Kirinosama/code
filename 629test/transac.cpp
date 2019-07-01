#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000010
#define MAXM 2000010

struct edge{
	int x,y,p,q;
}E[MAXM];

int n,m,s,t;
int last[MAXN],ne[MAXM],edge_cnt;
int pre[MAXN],dis[MAXN];

void add_edge(int x,int y,int p,int q){
	E[++edge_cnt]=(edge){x,y,p,q};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

int find(int beg,int p,int q){
	if(!beg) return 0;
	if(beg<p) return beg;
	int k=beg/(p+q)*(p+q);
	if(k+p-q-1>=beg) return beg;
	else return k+p+q;
}

int main(){
	freopen("1.in","r",stdin);
	cin>>n>>m>>s>>t;
	for(int i=1;i<=m;i++){
		int x,y,p,q;
		scanf("%d%d%d%d",&x,&y,&p,&q);
		add_edge(x,y,p,q);add_edge(y,x,p,q);
	}
	memset(dis,0x3f,sizeof(dis));dis[s]=0;
	queue<int>Q;Q.push(s);
	while(!Q.empty()){
		int cur=Q.front();Q.pop();
		for(int i=last[cur];i;i=ne[i]){
			int to=E[i].y,st=find(dis[cur],E[i].p,E[i].q);
			if(dis[to]>st+1){
				Q1.push(ii(to,st+1));
			}
		}
	}
	cout<<dis[t]<<endl;	
	vector<int>v;v.push_back(t);
	for(int i=t;i!=s;i=pre[i])v.push_back(pre[i]);
	for(int i=(int)v.size()-1;i>=0;i--)printf("%d ",v[i]);
	return 0;
}

